from pathlib import Path
import re,json,subprocess
root=Path('G:/algo/算法');tmp=Path('G:/algo/module_code_check');tmp.mkdir(exist_ok=True)
records=[]
for module in ['基础算法与思想','经典算法']:
    for p in (root/module).glob('*.md'):
        text=p.read_text(encoding='utf-8-sig')
        # Include indented code fences; the full programs are unindented.
        blocks=re.findall(r'^[ \t]*```(?:cpp|C\+\+)\n(.*?)^[ \t]*```[ \t]*$',text,re.S|re.M)
        for i,code in enumerate(blocks):
            records.append({'module':module,'file':p.name,'index':i,'code':code,'complete':'int main(' in code})
Path('G:/algo/module_code_before.json').write_text(json.dumps(records,ensure_ascii=False),encoding='utf-8')
count=0
for record in records:
    if not record['complete']:continue
    src=tmp/f'before_{count}.cpp';exe=src.with_suffix('.exe');src.write_text(record['code'],encoding='utf-8')
    result=subprocess.run(['D:/cpp/bin/g++.exe','-std=c++17','-O2',str(src),'-o',str(exe)],capture_output=True,text=True)
    assert result.returncode==0,(record['file'],result.stderr)
    record['exe']=str(exe);count+=1
Path('G:/algo/module_code_before.json').write_text(json.dumps(records,ensure_ascii=False),encoding='utf-8')
print('Saved and compiled baseline programs:',count,flush=True)
