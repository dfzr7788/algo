from pathlib import Path
import re,subprocess
root=Path('G:/algo/算法')
# Complete the sorting-family ratings, without re-running the rating writer.
rows=[('插入排序',2,5),('归并排序',5,9),('普通快速排序',5,7),('堆排序',5,6)]
p=root/'基础算法与思想/04-排序.md';s=p.read_text(encoding='utf-8')
marker='| 计数排序 | 3/10 | 6/10 |'
s=s.replace(marker,marker+'\n'+''.join(f'| {name} | {d}/10 | {v}/10 |\n' for name,d,v in rows).rstrip())
p.write_text(s,encoding='utf-8')
p=root/'基础算法与思想/00-基础算法与思想.md';s=p.read_text(encoding='utf-8')
marker='| 计数排序 | 3/10 | 6/10 | [[04-排序]] |'
s=s.replace(marker,marker+'\n'+''.join(f'| {name} | {d}/10 | {v}/10 | [[04-排序]] |\n' for name,d,v in rows).rstrip())
p.write_text(s,encoding='utf-8')
# Make the permutation fragment array-based too.
p=root/'基础算法与思想/02-枚举与暴力.md';s=p.read_text(encoding='utf-8')
s=s.replace('// a 是可比较元素的 vector；从排序后的最小排列开始。','// a 是可比较元素的数组，n 为有效长度；从最小排列开始。')
s=s.replace('sort(a.begin(), a.end());','sort(a, a + n);').replace('next_permutation(a.begin(), a.end())','next_permutation(a, a + n)')
p.write_text(s,encoding='utf-8')
formatter=r'C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/Llvm/bin/clang-format.exe'
style='{BasedOnStyle: LLVM, IndentWidth: 4, ContinuationIndentWidth: 4, AlignAfterOpenBracket: DontAlign, TabWidth: 4, UseTab: Never, BreakBeforeBraces: Allman, AllowShortFunctionsOnASingleLine: None, AllowShortBlocksOnASingleLine: Never, AllowShortIfStatementsOnASingleLine: Never, AllowShortLoopsOnASingleLine: false, AllowShortLambdasOnASingleLine: None, ColumnLimit: 110}'
def tokens(code):
    return re.findall(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|//[^\n]*|/\*.*?\*/|\w+|[^\s]',code,re.S)
for module in ['基础算法与思想','经典算法']:
    for p in (root/module).glob('*.md'):
        s=p.read_text(encoding='utf-8')
        def update(m):
            result=subprocess.run([formatter,'--style='+style],input=m.group(1),text=True,encoding='utf-8',capture_output=True)
            assert result.returncode==0,(p,result.stderr)
            assert tokens(m.group(1))==tokens(result.stdout),(p,'non-format change')
            return '```cpp\n'+result.stdout.rstrip()+'\n```'
        s=re.sub(r'^\s*```cpp\n(.*?)^\s*```\s*$',update,s,flags=re.M|re.S)
        p.write_text(s,encoding='utf-8')
print('Updated remaining ratings and checked token-preserving final indentation.')
