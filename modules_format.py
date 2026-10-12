from pathlib import Path
import re,subprocess
formatter=r'C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/Llvm/bin/clang-format.exe'
style='{BasedOnStyle: LLVM, IndentWidth: 4, TabWidth: 4, UseTab: Never, BreakBeforeBraces: Allman, AllowShortFunctionsOnASingleLine: None, AllowShortBlocksOnASingleLine: Never, AllowShortIfStatementsOnASingleLine: Never, AllowShortLoopsOnASingleLine: false, AllowShortLambdasOnASingleLine: None, ColumnLimit: 110}'
count=0
for module in ['基础算法与思想','经典算法']:
    for p in (Path('G:/algo/算法')/module).glob('*.md'):
        text=p.read_text(encoding='utf-8-sig')
        def format_block(m):
            global count
            result=subprocess.run([formatter,'--style='+style],input=m.group(1),text=True,encoding='utf-8',capture_output=True)
            assert result.returncode==0,(p,result.stderr)
            count+=1
            return '```cpp\n'+result.stdout.rstrip()+'\n```'
        text=re.sub(r'^[ \t]*```(?:cpp|C\+\+)\n(.*?)^[ \t]*```[ \t]*$',format_block,text,flags=re.S|re.M)
        p.write_text(text,encoding='utf-8')
print('Formatted C++ blocks:',count)
