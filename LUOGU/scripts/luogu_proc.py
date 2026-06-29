#!/usr/bin/env python3
"""Helper for processing LUOGU *_data.txt intermediates per LUOGU_TJ skill spec.

Subcommands:
  list-need            : print PIDs needing generation (no .cpp anywhere)
  list-solved          : print PIDs whose _data.txt can be deleted (cpp in level dir)
  summary <pid...>     : concise problem summary from _data.txt
  finalize <pid> [dir] : compile 七级/<pid>.cpp, rename md with cleaned title,
                         move into <dir> (default 七级), delete _data.txt
  cleanup-solved       : delete _data.txt for all solved&placed pids
"""
import os, re, sys, glob, subprocess, shutil

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LEVEL_DIRS = {"四级","五级","六级","七级","NOIP_省选","USACO","其他","其他比赛"}

def pid_of(path): return os.path.basename(path)[:-len("_data.txt")]

def all_data(): return glob.glob(os.path.join(ROOT,"**/*_data.txt"), recursive=True)

def cpp_index():
    idx={}
    for p in glob.glob(os.path.join(ROOT,"**/*.cpp"), recursive=True):
        m=re.match(r'((?:P|B)\d+)', os.path.basename(p))
        if m: idx.setdefault(m.group(1),[]).append(p)
    return idx

def find_data(pid):
    for d in all_data():
        if pid_of(d)==pid: return d
    return None

def parse(pid):
    p=find_data(pid)
    if not p: return None
    t=open(p,encoding="utf-8").read()
    secs={}
    for key in ["PID","Name","Difficulty"]:
        m=re.search(r'^=== %s: (.*) ===$'%re.escape(key), t, re.M)
        secs[key]=m.group(1).strip() if m else ""
    for key in ["Background","Description","Input","Output","Hint","Samples","Limits"]:
        m=re.search(r'^=== %s ===\n(.*?)(?=^=== |\Z)'%re.escape(key), t, re.M|re.S)
        secs[key]=m.group(1).strip() if m else ""
    secs["_path"]=p
    secs["_raw"]=t
    return secs

def clean_title(name):
    c=re.sub(r'[^\w\u4e00-\u9fff\-]', '_', name)
    c=re.sub(r'_+','_',c).strip('_')
    return c

def cmd_list_need():
    cpp=cpp_index()
    for d in sorted(all_data()):
        pid=pid_of(d)
        if pid not in cpp:
            s=parse(pid) or {}
            print(f"{pid}\t{s.get('Difficulty','?')}\t{s.get('Name','')}")

def cmd_list_solved():
    cpp=cpp_index()
    for d in sorted(all_data()):
        pid=pid_of(d)
        paths=cpp.get(pid,[])
        if paths and any(os.path.relpath(pp,ROOT).split("/")[0] in LEVEL_DIRS for pp in paths):
            print(pid, os.path.relpath(d,ROOT))

def cmd_summary(pids):
    for pid in pids:
        s=parse(pid)
        if not s: print(f"### {pid}: NOT FOUND"); continue
        print("="*70)
        print(f"PID: {pid}  | 难度: {s.get('Difficulty','?')}  | {s.get('Name','')}")
        print(f"data: {os.path.relpath(s['_path'],ROOT)}")
        print("-"*70)
        if s.get("Background"): print("[背景]\n"+s["Background"]+"\n")
        print("[题目描述]\n"+s.get("Description","")+"\n")
        print("[输入]\n"+s.get("Input","")+"\n")
        print("[输出]\n"+s.get("Output","")+"\n")
        if s.get("Hint"): print("[提示]\n"+s.get("Hint","")+"\n")
        print("[样例]\n"+s.get("Samples","")+"\n")
        if s.get("Limits"): print("[数据范围]\n"+s.get("Limits","")+"\n")

def compile_cpp(cpppath):
    out="/tmp/luogu_test_"+os.path.basename(cpppath).replace(".cpp","")
    r=subprocess.run(["g++","-std=c++11","-O2","-Wall","-Wextra","-o",out,cpppath],
                     capture_output=True,text=True)
    return r.returncode==0, r.stderr.strip()

def cmd_finalize(pid, target="七级"):
    """严格依据：.cpp 与 .md 都存在且编译通过，才删除 _data.txt。"""
    s=parse(pid)
    if not s: print(f"[{pid}] no _data.txt found"); return False
    datapath=s["_path"]
    title=clean_title(s.get("Name",""))
    tdir=os.path.join(ROOT,target); os.makedirs(tdir,exist_ok=True)
    src_cpp=os.path.join(ROOT,f"{pid}.cpp")
    src_md=os.path.join(ROOT,f"{pid}.md")
    cpp_cand = src_cpp if os.path.exists(src_cpp) else os.path.join(tdir,f"{pid}.cpp")
    md_cand  = src_md if os.path.exists(src_md) else os.path.join(tdir,f"{pid}.md")
    if not os.path.exists(cpp_cand):
        for q in glob.glob(os.path.join(ROOT,"**",f"{pid}.cpp"),recursive=True):
            cpp_cand=q; break
    if not os.path.exists(md_cand):
        for q in glob.glob(os.path.join(ROOT,"**",f"{pid}*.md"),recursive=True):
            md_cand=q; break
    has_cpp=os.path.exists(cpp_cand)
    has_md=os.path.exists(md_cand)
    ok,err=compile_cpp(cpp_cand) if has_cpp else (False,"no cpp")
    strict_ok = has_cpp and has_md and ok
    # move/normalize outputs regardless (best effort)
    dst_cpp=os.path.join(tdir,f"{pid}.cpp")
    if has_cpp and os.path.abspath(cpp_cand)!=os.path.abspath(dst_cpp):
        shutil.move(cpp_cand,dst_cpp); cpp_cand=dst_cpp
    dst_md=os.path.join(tdir,f"{pid}_{title}.md")
    if has_md and os.path.abspath(md_cand)!=os.path.abspath(dst_md):
        shutil.move(md_cand,dst_md); md_cand=dst_md
    # 严格删除：只有三项全满足才删中间文件
    if strict_ok and os.path.exists(datapath):
        os.remove(datapath)
    else:
        reason=[]
        if not has_cpp: reason.append("no-cpp")
        if not has_md: reason.append("no-md")
        if has_cpp and not ok: reason.append("compile-fail")
        print(f"[{pid}] KEEP _data.txt (未达严格依据: {', '.join(reason)})")
        if err: print("     ",err.splitlines()[-1] if err else "")
        return False
    # clean stray root copies
    for stray in [src_cpp, src_md]:
        if os.path.exists(stray): os.remove(stray)
    print(f"[{pid}] title='{title}' compile=OK md=OK -> {target}/  (deleted {os.path.basename(datapath)})")
    return True

def cmd_cleanup_solved():
    cpp=cpp_index()
    n=0; fails=[]
    for d in sorted(all_data()):
        pid=pid_of(d)
        paths=cpp.get(pid,[])
        if paths and any(os.path.relpath(pp,ROOT).split("/")[0] in LEVEL_DIRS for pp in paths):
            os.remove(d); n+=1
    print(f"deleted {n} solved _data.txt intermediates")

if __name__=="__main__":
    args=sys.argv[1:]
    if not args: print(__doc__); sys.exit(0)
    c=args[0]
    if c=="list-need": cmd_list_need()
    elif c=="list-solved": cmd_list_solved()
    elif c=="summary": cmd_summary(args[1:])
    elif c=="finalize":
        target=args[2] if len(args)>2 else "七级"
        cmd_finalize(args[1], target)
    elif c=="cleanup-solved": cmd_cleanup_solved()
    else: print("unknown:",c); sys.exit(1)
