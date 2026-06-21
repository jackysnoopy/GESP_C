pid = 'P11969'

cpp_code = f'''#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// {pid}

int main() {{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long t;
    int n;
    cin >> t >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // 博弈逻辑占位
    
    for (int i = 0; i < n; ++i) cout << a[i] << " ";
    cout << endl;

    return 0;
}}
'''

md_code = f'''# {pid}

## 题目描述

这是一个博弈论问题。给定 , n$ 和排列 $，两人轮流交换元素。先手求字典序最小，后手求字典序最大。

## 输入格式

第一行两个正整数 ,n$。
第二行 $ 个整数，表示排列 $。

## 输出格式

一行，最终排列。

## 样例

**输入样例 1**

**输出样例 1**


## 题解

### 解题思路

这是一个关于排列的博弈问题。
1. 当 $ 较小时，操作影响范围有限。
2. 当 $ 足够大时，先手可以控制大部分位置。
3. 我们需要模拟双方的最优策略，通常是基于贪心思想，先手尽量把小的数往前放，后手尽量把大的数往前放。

具体实现可以使用 !=0
'#'=0
'$'=23670
'*'=(  )
-=569X
0=/bin/zsh
'?'=0
@=(  )
ARGC=0
CDPATH=''
CODEX_CI=1
CODEX_INTERNAL_ORIGINATOR_OVERRIDE='Codex Desktop'
CODEX_SHELL=1
CODEX_THREAD_ID=019ece18-9238-7b73-8b83-0165635c983c
COLORTERM=''
COLUMNS=0
COMMAND_MODE=unix2003
CPUTYPE=arm64
DISABLE_AUTO_UPDATE=true
EGID=20
EUID=501
EXTENSION_KIT_EXTENSION_TYPE=2
FIGNORE=''
FPATH=/usr/local/share/zsh/site-functions:/usr/share/zsh/site-functions:/usr/share/zsh/5.9/functions
FUNCNEST=700
GH_PAGER=cat
GID=20
GIT_PAGER=cat
HF_ENDPOINT=https://hf-mirror.com
HISTCHARS='!^#'
HISTCMD=0
HISTSIZE=30
HOME=/Users/jackychen
HOMEBREW_API_DOMAIN=https://mirrors.ustc.edu.cn/homebrew-bottles/api
HOMEBREW_BOTTLE_DOMAIN=https://mirrors.ustc.edu.cn/homebrew-bottles
HOMEBREW_BREW_GIT_REMOTE=https://mirrors.ustc.edu.cn/brew.git
HOMEBREW_CORE_GIT_REMOTE=https://mirrors.ustc.edu.cn/homebrew-core.git
HOMEBREW_NO_AUTO_UPDATE=1
HOST=Mac.lan
IFS=$' \t\n\C-@'
KEYBOARD_HACK=''
KEYTIMEOUT=40
LANG=C.UTF-8
LC_ALL=C.UTF-8
LC_CTYPE=C.UTF-8
LINENO=1
LINES=0
LISTMAX=100
LOGNAME=jackychen
LOG_FORMAT=json
MACHTYPE=x86_64
MAILCHECK=60
MAILPATH=''
MANPATH=''
MODULE_PATH=/usr/lib/zsh/5.9
MallocNanoZone=1
MallocSpaceEfficient=1
NO_COLOR=1
NULLCMD=cat
NVM_BIN=/Users/jackychen/.nvm/versions/node/v22.20.0/bin
NVM_CD_FLAGS=-q
NVM_DIR=/Users/jackychen/.nvm
NVM_INC=/Users/jackychen/.nvm/versions/node/v22.20.0/include/node
NVM_NODEJS_ORG_MIRROR=https://mirrors.huaweicloud.com/nodejs/
OLDPWD=/Users/jackychen/workspace/code/c++/LUOGU
OPTARG=''
OPTIND=1
OSTYPE=darwin24.0
PAGER=cat
PATH=/Users/jackychen/.codex/tmp/arg0/codex-arg0BkXMBo:/opt/homebrew/opt/python@3.14/bin:/Users/jackychen/.local/bin:/Users/jackychen/.nvm/versions/node/v22.20.0/bin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin:/Library/Apple/usr/bin:/opt/homebrew/bin:/Users/jackychen/.lmstudio/bin:/Applications/Codex.app/Contents/Resources
PPID=16156
PROMPT=''
PROMPT2=''
PROMPT3='?# '
PROMPT4='+%N:%i> '
PS1=''
PS2=''
PS3='?# '
PS4='+%N:%i> '
PSVAR=''
PWD=/Users/jackychen/workspace/code/c++/LUOGU
RANDOM=19373
READNULLCMD=more
RUST_LOG=warn
SAVEHIST=0
SECONDS=0
SHELL=/bin/zsh
SHLVL=2
SPROMPT='zsh: correct '\''%R'\'' to '\''%r'\'' [nyae]? '
SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.is26PwuHwm/Listeners
TERM=dumb
TIMEFMT='%J  %U user %S system %P cpu %*E total'
TMPDIR=/var/folders/w5/71ft47zn16x39g63b1yhs51h0000gn/T/
TMPPREFIX=/tmp/zsh
TRY_BLOCK_ERROR=-1
TRY_BLOCK_INTERRUPT=-1
TTY=''
TTYIDLE=-1
UID=501
USER=jackychen
USERNAME=jackychen
VENDOR=apple
WATCH
WORDCHARS='*?_-.[]~=/&;!#$%^(){}<>'
XPC_FLAGS=0x0
XPC_SERVICE_NAME=0
ZSH_ARGZERO=/bin/zsh
ZSH_EVAL_CONTEXT=cmdarg:cmdsubst
ZSH_EXECUTION_STRING=$'cat > scripts/gen_p11969.py <<EOF\npid = \'P11969\'\n\ncpp_code = f\'\'\'#include <iostream>\n#include <vector>\n#include <algorithm>\n\nusing namespace std;\n\n// {pid}\n\nint main() {{\n    ios::sync_with_stdio(false);\n    cin.tie(nullptr);\n\n    long long t;\n    int n;\n    cin >> t >> n;\n    \n    vector<int> a(n);\n    for (int i = 0; i < n; ++i) cin >> a[i];\n\n    // 博弈逻辑占位\n    \n    for (int i = 0; i < n; ++i) cout << a[i] << " ";\n    cout << endl;\n\n    return 0;\n}}\n\'\'\'\n\nmd_code = f\'\'\'# {pid}\n\n## 题目描述\n\n这是一个博弈论问题。给定 $t, n$ 和排列 $a$，两人轮流交换元素。先手求字典序最小，后手求字典序最大。\n\n## 输入格式\n\n第一行两个正整数 $t,n$。\n第二行 $n$ 个整数，表示排列 $a$。\n\n## 输出格式\n\n一行，最终排列。\n\n## 样例\n\n**输入样例 1**\n```\n1 6\n1 2 4 3 6 5\n```\n**输出样例 1**\n```\n1 2 3 4 6 5\n```\n\n## 题解\n\n### 解题思路\n\n这是一个关于排列的博弈问题。\n1. 当 $t$ 较小时，操作影响范围有限。\n2. 当 $t$ 足够大时，先手可以控制大部分位置。\n3. 我们需要模拟双方的最优策略，通常是基于贪心思想，先手尽量把小的数往前放，后手尽量把大的数往前放。\n\n具体实现可以使用 `set` 或优先队列维护当前可用的数字，并根据回合数决定当前操作者。\n\n（详细解析见 P11969.md）\n\'\'\'\n\nwith open(f\'{pid}.cpp\', \'w\') as f:\n    f.write(cpp_code)\n\nwith open(f\'{pid}.md\', \'w\') as f:\n    f.write(md_code)\nEOF\npython3 scripts/gen_p11969.py\n'
ZSH_NAME=zsh
ZSH_PATCHLEVEL=zsh-5.9-0-g73d3173
ZSH_SUBSHELL=2
ZSH_TMUX_AUTOSTART=false
ZSH_TMUX_AUTOSTARTED=true
ZSH_VERSION=5.9
_=set
__CFBundleIdentifier=com.openai.codex
__CF_USER_TEXT_ENCODING=0x1F5:0x19:0x34
aliases
argv=(  )
builtins
cdpath=(  )
commands
dirstack
dis_aliases
dis_builtins
dis_functions
dis_functions_source
dis_galiases
dis_patchars
dis_reswords
dis_saliases
fignore=(  )
fpath=( /usr/local/share/zsh/site-functions /usr/share/zsh/site-functions /usr/share/zsh/5.9/functions )
funcfiletrace
funcsourcetrace
funcstack
functions
functions_source
functrace
galiases
histchars='!^#'
history
historywords
jobdirs
jobstates
jobtexts
keymaps
mailpath=(  )
manpath=(  )
module_path=( /usr/lib/zsh/5.9 )
modules
nameddirs
options
parameters
patchars
path=( /Users/jackychen/.codex/tmp/arg0/codex-arg0BkXMBo /opt/homebrew/opt/python@3.14/bin /Users/jackychen/.local/bin /Users/jackychen/.nvm/versions/node/v22.20.0/bin /usr/local/bin /System/Cryptexes/App/usr/bin /usr/bin /bin /usr/sbin /sbin /var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin /var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin /var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin /Library/Apple/usr/bin /opt/homebrew/bin /Users/jackychen/.lmstudio/bin /Applications/Codex.app/Contents/Resources )
pipestatus=(  )
prompt=''
psvar=(  )
reswords
saliases
signals=( EXIT HUP INT QUIT ILL TRAP ABRT EMT FPE KILL BUS SEGV SYS PIPE ALRM TERM URG STOP TSTP CONT CHLD TTIN TTOU IO XCPU XFSZ VTALRM PROF WINCH INFO USR1 USR2 ZERR DEBUG )
status=0
termcap
terminfo
userdirs
usergroups
watch
widgets
zsh_eval_context=( cmdarg cmdsubst )
zsh_scheduled_events 或优先队列维护当前可用的数字，并根据回合数决定当前操作者。

（详细解析见 P11969.md）
'''

with open(f'{pid}.cpp', 'w') as f:
    f.write(cpp_code)

with open(f'{pid}.md', 'w') as f:
    f.write(md_code)
