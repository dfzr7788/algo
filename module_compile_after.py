from pathlib import Path
import re,json,subprocess
records=json.loads(Path('G:/algo/module_code_before.json').read_text(encoding='utf-8'))
root=Path('G:/algo/算法');tmp=Path('G:/algo/module_code_check')
count=0
for record in records:
    if not record['complete']:continue
    text=(root/record['module']/record['file']).read_text(encoding='utf-8-sig')
    blocks=re.findall(r'^[ \t]*```(?:cpp|C\+\+)\n(.*?)^[ \t]*```[ \t]*$',text,re.S|re.M)
    code=blocks[record['index']]
    assert 'int main(' in code,(record['file'],record['index'])
    src=tmp/f'after_{count}.cpp';exe=src.with_suffix('.exe');src.write_text(code,encoding='utf-8')
    result=subprocess.run(['D:/cpp/bin/g++.exe','-std=c++17','-O2','-Wall','-Wextra',str(src),'-o',str(exe)],text=True,capture_output=True)
    assert result.returncode==0,(record['file'],result.stderr)
    record['after_exe']=str(exe);count+=1
Path('G:/algo/module_code_after.json').write_text(json.dumps(records,ensure_ascii=False),encoding='utf-8')
print('Compiled rewritten complete programs:',count,flush=True)
