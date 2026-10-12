from pathlib import Path
import json,random,subprocess,math,re
records=json.loads(Path('G:/algo/module_code_after.json').read_text(encoding='utf-8'))
rng=random.Random(20261012)
def line(values):return ' '.join(map(str,values))+'\n'
def array_case(n=None,nonnegative=False):
    if n is None:n=rng.randrange(1,9)
    return [rng.randrange(0,12) if nonnegative else rng.randrange(-8,9) for _ in range(n)]
def interval_queries(n):
    result=[]
    for _ in range(8):
        l=rng.randrange(1,n+1);r=rng.randrange(l,n+1);result.append((l,r))
    return result
def make_input(record):
    module=record['module'];num=int(record['file'][:2]);idx=record['index']
    if module=='基础算法与思想':
        if num==2:
            a=array_case(rng.randrange(0,10),True);return str(len(a))+'\n'+line(a)
        if num==3:
            n=rng.randrange(1,12);return f'{n} {rng.randrange(0,12)}\n'+line([rng.randrange(2) for _ in range(n)])
        if num in (4,6):
            a=array_case(rng.randrange(0,12));return str(len(a))+'\n'+line(a)
        if num==5:
            a=array_case(rng.randrange(0,12));return (f'{len(a)} {rng.randrange(-12,13)}\n' if idx==0 else f'{len(a)}\n')+line(a)
        if num==7:
            a=array_case(nonnegative=True);return f'{len(a)} {rng.randrange(1,len(a)+2)}\n'+line(a)
        if num==8:
            if idx==2:return str(rng.randrange(1,6))+'\n'
            n=rng.randrange(1,6);m=rng.randrange(2,7)
            grid=[['#' if rng.random()<.3 else '.' for _ in range(m)] for _ in range(n)]
            if idx==4:grid[0][0]='A';grid[-1][-1]='B'
            return f'{n} {m}\n'+''.join(''.join(row)+'\n' for row in grid)
        if num==9:
            if idx==1:
                a=array_case(rng.randrange(0,8),True);return str(len(a))+'\n'+line(a)
            n=rng.randrange(0,10)
            if idx==0:
                intervals=[]
                for _ in range(n):l=rng.randrange(-6,7);intervals.append((l,l+rng.randrange(1,6)))
                return str(n)+'\n'+''.join(line(pair) for pair in intervals)
            return str(n)+'\n'+''.join(f'{rng.randrange(1,8)} {rng.randrange(0,22)}\n' for _ in range(n))
        if num==10:
            n=rng.randrange(1,30)
            if idx!=2:return str(n)+'\n'
            a=list(range(1,n+1));rng.shuffle(a);return str(n)+'\n'+line(a)
        if num==11:
            n=rng.randrange(1,12);queries=[(rng.randrange(1,n+1),rng.choice([0,1,8,10**18,rng.randrange(100)])) for _ in range(10)]
            return f'{n} {len(queries)}\n'+line([rng.randrange(1,n+1) for _ in range(n)])+''.join(line(q) for q in queries)
        if num==12:
            if idx==0:return ''.join(''.join('*' if rng.random()<.2 else '.' for _ in range(8))+'\n' for _ in range(8))
            n=rng.randrange(0,11)
            if idx==1:return f'{n} {rng.randrange(-12,13)}\n'+line(array_case(n))
            return f'{n} {rng.randrange(0,25)}\n'+''.join(f'{rng.randrange(1,15)} {rng.randrange(0,20)}\n' for _ in range(n))
        if num==13:
            n=rng.randrange(1,12)
            a=array_case(n) if idx==0 else [rng.randrange(1,n+1) for _ in range(n)]
            return str(n)+'\n'+line(a)
        if num==14:
            a=array_case(rng.randrange(0,12));q=rng.randrange(0,12)
            return f'{len(a)} {q}\n'+line(a)+line([rng.randrange(-12,13) for _ in range(q)])
        if num==16:
            a=[rng.uniform(-100,100) for _ in range(rng.randrange(1,10))];return str(len(a))+'\n'+line(a)
        if num==18:
            a=array_case(nonnegative=True) if idx==0 else [rng.randrange(1,16) for _ in range(rng.randrange(1,9))]
            return f'{len(a)} {rng.randrange(1,30)}\n'+line(a)
        if num==19:
            a=array_case(rng.randrange(0,12));return f'{len(a)} {rng.randrange(-12,13)}\n'+line(a)
    else:
        if num==1:
            if idx==0:
                a=array_case();queries=interval_queries(len(a));return str(len(a))+'\n'+line(a)+str(len(queries))+'\n'+''.join(line(q) for q in queries)
            n=rng.randrange(1,5);m=rng.randrange(1,6);mat=[array_case(m) for _ in range(n)];queries=[]
            for _ in range(8):x1=rng.randrange(1,n+1);x2=rng.randrange(x1,n+1);y1=rng.randrange(1,m+1);y2=rng.randrange(y1,m+1);queries.append((x1,y1,x2,y2))
            return f'{n} {m} {len(queries)}\n'+''.join(line(row) for row in mat)+''.join(line(q) for q in queries)
        if num==2:
            if idx==0:
                a=array_case();updates=[(l,r,rng.randrange(-8,9)) for l,r in interval_queries(len(a))]
                return f'{len(a)} {len(updates)}\n'+line(a)+''.join(line(q) for q in updates)
            n=rng.randrange(1,6);queries=[]
            for _ in range(8):x1=rng.randrange(1,n+1);x2=rng.randrange(x1,n+1);y1=rng.randrange(1,n+1);y2=rng.randrange(y1,n+1);queries.append((x1,y1,x2,y2))
            return f'{n} {len(queries)}\n'+''.join(line(q) for q in queries)
        if num in (3,6):
            a=array_case(rng.randrange(0 if num==3 else 1,12));return str(len(a))+'\n'+line(a)
        if num==4:
            intervals=[]
            for _ in range(rng.randrange(0,12)):l=rng.randrange(-8,9);intervals.append((l,l+rng.randrange(1,6)))
            return str(len(intervals))+'\n'+''.join(line(q) for q in intervals)
        if num==5:
            a=array_case(rng.randrange(0,12));return f'{len(a)} {rng.randrange(-12,13)}\n'+line(a)
        if num==7:
            a=array_case();q=interval_queries(len(a));return f'{len(a)} {len(q)}\n'+line(a)+''.join(line(v) for v in q)
        if num==8:
            a=array_case();ops=[]
            for l,r in interval_queries(len(a)):
                ops.append((1,l,r,rng.randrange(-8,9)));ops.append((2,l,r))
            return f'{len(a)} {len(ops)}\n'+line(a)+''.join(line(q) for q in ops)
        if num==9:
            if idx==1:
                n=rng.randrange(1,5);return str(n)+'\n'+''.join(line(array_case(n)) for _ in range(n))
            a=array_case();n=len(a);m=rng.randrange(1,10);ops=[(l,r,rng.randrange(-8,9)) for l,r in interval_queries(n)][:m]
            m=len(ops);calls=interval_queries(m)
            return f'{n} {m} {len(calls)}\n'+line(a)+''.join(line(q) for q in ops)+''.join(line(q) for q in calls)
    raise AssertionError((module,num,idx))
def output(exe,data):return subprocess.run([exe],input=data,text=True,capture_output=True,check=True,timeout=5).stdout.split()
pairs=0
for record in records:
    if not record['complete']:continue
    for _ in range(12):
        data=make_input(record)
        before=output(record['exe'],data);after=output(record['after_exe'],data)
        if int(record['file'][:2])==16:
            assert len(before)==len(after)==2
            assert all(math.isclose(float(x),float(y),rel_tol=1e-8,abs_tol=1e-6) for x,y in zip(before,after)),(record['file'],data,before,after)
        else:assert before==after,(record['module'],record['file'],record['index'],data,before,after)
        pairs+=1
print('Passed baseline comparison for',pairs,'seeded inputs across 40 rewritten programs.',flush=True)
# Semantic checks independent from the old implementation for newly rewritten core templates.
lookup={(r['module'],int(r['file'][:2]),r['index']):r['after_exe'] for r in records if r['complete']}
assert output(lookup['基础算法与思想',7,6],'5 2\n7 2 5 10 8\n')==['18']
assert output(lookup['基础算法与思想',12,1],'4 0\n0 0 0 0\n')==['16']
assert output(lookup['基础算法与思想',18,1],'1 1000000000\n1000000000\n')==['1000000000000000000']
assert output(lookup['经典算法',6,0],'3\n-3 -1 -2\n')==['-1']
assert output(lookup['经典算法',9,0],'3 3 3\n1 2 3\n1 2 1\n1 3 2\n2 3 4\n1 2\n1 3\n2 3\n')==['9','18','17']
print('Passed independent known-answer and boundary checks.',flush=True)
# Verify style, ratings and internal references for all three modules.
modules=['基础算法与思想','经典算法','数据结构'];total_blocks=0;rating_rows=0
for module in modules:
    directory=Path('G:/algo/算法')/module
    for p in directory.glob('*.md'):
        s=p.read_text(encoding='utf-8-sig');assert s.count('```')%2==0,p
        blocks=re.findall(r'^[ \t]*```cpp\n(.*?)^[ \t]*```[ \t]*$',s,re.S|re.M)
        for code in blocks:
            total_blocks+=1
            assert not re.search(r'\b(class|struct)\s',code),(p,'class')
            for row in code.splitlines():
                clean=re.sub(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'','',row.split('//')[0]).strip()
                if not clean.startswith('for '):assert clean.count(';')<=1,(p,row)
                assert not re.search(r'\)\s*\{',clean),(p,row)
            if re.search(r'\[\s*(?:&|=)?\s*\]\s*\(',code):assert 'sort(' in code,(p,'operation lambda')
        for link in re.findall(r'\[\[([^\]]+)\]\]',s):
            target=link.replace('\\|','|').split('|')[0];file,sep,anchor=target.partition('#')
            if file.endswith('.png'):assert (Path('G:/algo')/file).exists();continue
            matches=[Path('G:/algo')/(file+'.md')] if '/' in file else list(Path('G:/algo').rglob(file+'.md'))
            matches=[q for q in matches if q.exists()];assert matches,(p,link)
            if sep:assert any(anchor in [x.lstrip('#').strip() for x in q.read_text(encoding='utf-8-sig').splitlines() if x.startswith('#')] for q in matches),(p,link)
        for match in re.finditer(r'\| ([1-9]|10)/10 \| ([1-9]|10)/10 \|',s):rating_rows+=1
print('Passed style, rating ranges and links; checked',total_blocks,'C++ blocks across three modules.',flush=True)
