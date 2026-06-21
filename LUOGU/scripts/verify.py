# -*- coding: utf-8 -*-
"""编译并运行 {pid}.cpp，对照 _data.txt 中的样例验证。用法: MDGEN_DIR=七级/难度4 python3 scripts/verify.py P11969 P12234 ..."""
import os, re, subprocess, sys, tempfile

DIR = os.environ.get('MDGEN_DIR', '.')

def parse_samples(pid):
    path = os.path.join(DIR, f'{pid}_data.txt')
    raw = open(path, encoding='utf-8').read()
    m = re.search(r'=== Samples ===\n(.*?)(?:=== Limits ===|\Z)', raw, re.DOTALL)
    block = m.group(1) if m else ''
    samples = []
    for sm in re.finditer(r'--- Sample \d+ ---\s*\nInput:\n(.*?)\nOutput:\n(.*?)(?=\n--- Sample|\Z)', block, re.DOTALL):
        inp = sm.group(1).strip('\n')
        out = sm.group(2).strip('\n')
        samples.append((inp, out))
    return samples

def norm(s, is_float=False):
    s = s.strip()
    if is_float:
        try:
            return f'{float(s):.6f}'
        except: return s
    return '\n'.join(ln.strip() for ln in s.splitlines() if ln.strip())

def main():
    pids = sys.argv[1:]
    for pid in pids:
        cpp = os.path.join(DIR, f'{pid}.cpp')
        exe = os.path.join(tempfile.gettempdir(), pid)
        r = subprocess.run(['g++','-std=c++17','-O2','-o',exe,cpp],
                           capture_output=True, text=True)
        if r.returncode != 0:
            print(f'{pid}: COMPILE FAIL\n{r.stderr[:300]}')
            continue
        samples = parse_samples(pid)
        if not samples:
            print(f'{pid}: no samples'); continue
        allok = True
        for i,(inp,exp) in enumerate(samples,1):
            r = subprocess.run([exe], input=inp, capture_output=True, text=True, timeout=10)
            got = r.stdout.strip('\n')
            # try float compare
            ok = norm(got)==norm(exp)
            if not ok:
                try:
                    ok = abs(float(got)-float(exp))<1e-3
                except: pass
            tag = 'OK' if ok else 'FAIL'
            if not ok: allok=False
            print(f'{pid} sample{i}: {tag}  exp=[{exp[:40]}] got=[{got[:40]}]')
        print(f'{pid}: {"ALL OK" if allok else "HAS FAIL"}')
        print('-'*40)

if __name__=='__main__':
    main()
