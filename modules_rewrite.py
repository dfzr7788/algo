from pathlib import Path
import re
root=Path('G:/algo/算法')
new={}
new['经典算法/01-前缀和.md']=[r'''#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
long long pre[N];
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) { long long x; cin >> x; pre[i] = pre[i - 1] + x; }
    int q; cin >> q;
    while (q--) { int l, r; cin >> l >> r; cout << pre[r] - pre[l - 1] << '\n'; }
}
''',r'''#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
long long s[N][N];
int main() {
    int n, m, q; cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        long long x; cin >> x; s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + x;
    }
    while (q--) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        cout << s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1] << '\n';
    }
}
''']
new['经典算法/02-差分.md']=[r'''#include <bits/stdc++.h>
using namespace std;
const int N = 5000005;
long long d[N];
void range_add(int l, int r, long long value) { d[l] += value; d[r + 1] -= value; }
int main() {
    int n, q; cin >> n >> q;
    long long previous = 0;
    for (int i = 1; i <= n; i++) { long long x; cin >> x; d[i] = x - previous; previous = x; }
    while (q--) { int l, r; long long value; cin >> l >> r >> value; range_add(l, r, value); }
    long long current = 0;
    for (int i = 1; i <= n; i++) { current += d[i]; if (i > 1) cout << ' '; cout << current; }
    cout << '\n';
}
''',r'''#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
long long d[N][N];
void rectangle_add(int x1, int y1, int x2, int y2) {
    d[x1][y1]++; d[x2 + 1][y1]--; d[x1][y2 + 1]--; d[x2 + 1][y2 + 1]++;
}
int main() {
    int n, q; cin >> n >> q;
    while (q--) { int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2; rectangle_add(x1, y1, x2, y2); }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            d[i][j] += d[i - 1][j] + d[i][j - 1] - d[i - 1][j - 1];
            if (j > 1) cout << ' '; cout << d[i][j];
        }
        cout << '\n';
    }
}
''']
new['经典算法/03-离散化.md']=[r'''#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
long long a[N], values[N];
int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) { cin >> a[i]; values[i] = a[i]; }
    sort(values, values + n);
    int count = unique(values, values + n) - values;
    for (int i = 0; i < n; i++) cout << lower_bound(values, values + count, a[i]) - values << '\n';
}
''']
new['经典算法/04-区间合并.md']=[r'''#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
pair<long long, long long> intervals[N];
int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> intervals[i].first >> intervals[i].second;
    sort(intervals, intervals + n);
    long long total = 0, l = 0, r = 0;
    bool active = false;
    for (int i = 0; i < n; i++) {
        long long x = intervals[i].first, y = intervals[i].second;
        if (!active) { l = x; r = y; active = true; }
        else if (x <= r) r = max(r, y);
        else { total += r - l; l = x; r = y; }
    }
    if (active) total += r - l;
    cout << total << '\n';
}
''']
new['经典算法/07-ST表与静态区间查询.md']=[r'''#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
const int LOG = 18;
long long st[LOG][N];
int lg[N];
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;
    for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
    for (int i = 0; i < n; i++) cin >> st[0][i];
    for (int k = 1; k <= lg[n]; k++) for (int i = 0; i + (1 << k) <= n; i++)
        st[k][i] = max(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    while (q--) { int l, r; cin >> l >> r; l--; r--; int k = lg[r - l + 1]; cout << max(st[k][l], st[k][r - (1 << k) + 1]) << '\n'; }
}
''']
new['经典算法/08-分块入门.md']=[r'''#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
long long raw[N], tag[N], block_sum[N];
int n, block_size;
void range_add(int l, int r, long long value) {
    for (int i = l; i <= r;) {
        int b = i / block_size, end = min(n, (b + 1) * block_size);
        if (i == b * block_size && end - 1 <= r) { tag[b] += value; block_sum[b] += value * (end - i); i = end; }
        else { raw[i] += value; block_sum[b] += value; i++; }
    }
}
long long range_sum(int l, int r) {
    long long answer = 0;
    for (int i = l; i <= r;) {
        int b = i / block_size, end = min(n, (b + 1) * block_size);
        if (i == b * block_size && end - 1 <= r) { answer += block_sum[b]; i = end; }
        else { answer += raw[i] + tag[b]; i++; }
    }
    return answer;
}
int main() {
    int q; cin >> n >> q; block_size = max(1, (int)sqrt(n));
    for (int i = 0; i < n; i++) { cin >> raw[i]; block_sum[i / block_size] += raw[i]; }
    while (q--) {
        int type, l, r; cin >> type >> l >> r; l--; r--;
        if (type == 1) { long long value; cin >> value; range_add(l, r, value); }
        else cout << range_sum(l, r) << '\n';
    }
}
''']
new['经典算法/09-从暴力到优化的完整题解.md']=[r'''#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
long long a[N], times[N], delta[N], value[N];
int left_end[N], right_end[N];
int main() {
    int n, m, k; cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> left_end[i] >> right_end[i] >> value[i];
    while (k--) { int x, y; cin >> x >> y; times[x]++; times[y + 1]--; }
    for (int i = 1; i <= m; i++) { times[i] += times[i - 1]; long long change = times[i] * value[i]; delta[left_end[i]] += change; delta[right_end[i] + 1] -= change; }
    for (int i = 1; i <= n; i++) { delta[i] += delta[i - 1]; if (i > 1) cout << ' '; cout << a[i] + delta[i]; }
    cout << '\n';
}
''',r'''#include <bits/stdc++.h>
using namespace std;
const int N = 125;
long long a[N][N], col[N];
int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> a[i][j];
    long long best = LLONG_MIN;
    for (int top = 0; top < n; top++) {
        fill(col, col + n, 0);
        for (int bottom = top; bottom < n; bottom++) {
            for (int j = 0; j < n; j++) col[j] += a[bottom][j];
            long long ending = col[0]; best = max(best, ending);
            for (int j = 1; j < n; j++) { ending = max(col[j], ending + col[j]); best = max(best, ending); }
        }
    }
    cout << best << '\n';
}
''']
# Replace main-program lambdas by ordinary functions and static arrays.
new['基础算法与思想/10-构造算法.md']=[None,r'''#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;
int group_a[N], group_b[N], count_a, count_b;
void print_group(int group[], int count) {
    cout << count << '\n';
    for (int i = 0; i < count; i++) cout << group[i] << ' ';
    cout << '\n';
}
int main() {
    int n; cin >> n;
    if (n % 4 != 0 && n % 4 != 3) { cout << "NO\n"; return 0; }
    int start = 1;
    if (n % 4 == 3) { group_a[count_a++] = 1; group_a[count_a++] = 2; group_b[count_b++] = 3; start = 4; }
    for (int x = start; x <= n; x += 4) { group_a[count_a++] = x; group_a[count_a++] = x + 3; group_b[count_b++] = x + 1; group_b[count_b++] = x + 2; }
    cout << "YES\n"; print_group(group_a, count_a); print_group(group_b, count_b);
}
''',None]
new['基础算法与思想/16-三分与单峰优化.md']=[r'''#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
long double a[N];
int n;
long double evaluate(long double x) {
    long double result = 0;
    for (int i = 0; i < n; i++) { long double difference = x - a[i]; result += difference * difference; }
    return result;
}
int main() {
    cin >> n; for (int i = 0; i < n; i++) cin >> a[i];
    long double l = *min_element(a, a + n), r = *max_element(a, a + n);
    for (int it = 0; it < 150; it++) {
        long double m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        long double v1 = evaluate(m1), v2 = evaluate(m2);
        if (v1 > v2) l = m1;
        else if (v1 < v2) r = m2;
        else { l = m1; r = m2; }
    }
    long double x = (l + r) / 2;
    cout << fixed << setprecision(10) << x << ' ' << evaluate(x) << '\n';
}
''']
for relative,blocks in new.items():
    p=root/relative;text=p.read_text(encoding='utf-8-sig')
    found=re.findall(r'^[ \t]*```(?:cpp|C\+\+)\n(.*?)^[ \t]*```[ \t]*$',text,re.S|re.M)
    assert len(found)==len(blocks),(relative,len(found),len(blocks))
    iterator=iter(zip(found,blocks))
    def replace(m):
        old,code=next(iterator)
        return '```cpp\n'+(code if code is not None else old).rstrip()+'\n```'
    text=re.sub(r'^[ \t]*```(?:cpp|C\+\+)\n.*?^[ \t]*```[ \t]*$',replace,text,flags=re.S|re.M)
    p.write_text(text,encoding='utf-8')
# The binary-search document has snippets plus a final complete program.
p=root/'基础算法与思想/07-二分.md';text=p.read_text(encoding='utf-8')
code=r'''#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
long long a[N];
int n, k;
bool check(long long limit) {
    int parts = 1; long long current = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > limit) return false;
        if (current > limit - a[i]) { parts++; current = a[i]; }
        else current += a[i];
    }
    return parts <= k;
}
int main() {
    cin >> n >> k; long long lo = 0, hi = 0;
    for (int i = 0; i < n; i++) { cin >> a[i]; lo = max(lo, a[i]); hi += a[i]; }
    while (lo < hi) { long long mid = lo + (hi - lo) / 2; if (check(mid)) hi = mid; else lo = mid + 1; }
    cout << lo << '\n';
}
'''
text=re.sub(r'```cpp\n(#include.*?int main\(.*?\n.*?)```',lambda m:'```cpp\n'+code+'```',text,flags=re.S)
p.write_text(text,encoding='utf-8')
p=root/'基础算法与思想/18-从暴力到优化的完整题解.md';text=p.read_text(encoding='utf-8')
blocks=re.findall(r'```cpp\n(.*?)```',text,re.S)
code=r'''#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
long long a[N], goal;
int n;
bool check(long long time) {
    long long made = 0;
    for (int i = 0; i < n; i++) { long long add = time / a[i]; if (add >= goal - made) return true; made += add; }
    return false;
}
int main() {
    cin >> n >> goal; for (int i = 0; i < n; i++) cin >> a[i];
    long long lo = 0, hi = *min_element(a, a + n) * goal;
    while (lo < hi) { long long mid = lo + (hi - lo) / 2; if (check(mid)) hi = mid; else lo = mid + 1; }
    cout << lo << '\n';
}
'''
blocks[1]=code;it=iter(blocks);text=re.sub(r'```cpp\n.*?```',lambda m:'```cpp\n'+next(it).rstrip()+'\n```',text,flags=re.S);p.write_text(text,encoding='utf-8')
print('Converted classical array templates and algorithm-operation lambdas.')
