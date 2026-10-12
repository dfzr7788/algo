from pathlib import Path
import re
root=Path('G:/algo/算法/基础算法与思想')
replacements={
'02-枚举与暴力.md':{0:r'''#include <bits/stdc++.h>
using namespace std;
long long a[25];
int main() {
    int n; cin >> n; long long total = 0;
    for (int i = 0; i < n; i++) { cin >> a[i]; total += a[i]; }
    long long best = total;
    for (unsigned mask = 0; mask < (1u << n); mask++) {
        long long sum = 0;
        for (int i = 0; i < n; i++) if (mask & (1u << i)) sum += a[i];
        best = min(best, llabs(sum - (total - sum)));
    }
    cout << best << '\n';
}
'''},
'03-模拟与实现.md':{0:r'''#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int a[N], next_value[N];
int main() {
    int n, t; cin >> n >> t;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int step = 0; step < t; step++) {
        for (int i = 0; i < n; i++) next_value[i] = a[i] ^ a[(i + n - 1) % n];
        for (int i = 0; i < n; i++) a[i] = next_value[i];
    }
    for (int i = 0; i < n; i++) { if (i > 0) cout << ' '; cout << a[i]; }
    cout << '\n';
}
'''},
'04-排序.md':{0:r'''// a 为 long long 数组，n 为元素个数；片段使用 <algorithm>、<functional>、<utility>。
sort(a, a + n);
sort(a, a + n, greater<long long>());
// items 的 first 对应 x，second 对应 y；不封装自定义类。
pair<long long, long long> items[200005];
sort(items, items + n, [](const pair<long long, long long> &a, const pair<long long, long long> &b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second > b.second;
});
''',1:r'''#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
long long a[N];
int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n);
    int count = unique(a, a + n) - a;
    cout << count << '\n';
}
'''},
'05-双指针与滑动窗口.md':{0:r'''#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
pair<long long, int> a[N];
int main() {
    int n; long long target; cin >> n >> target;
    for (int i = 0; i < n; i++) { cin >> a[i].first; a[i].second = i + 1; }
    sort(a, a + n);
    int l = 0, r = n - 1;
    while (l < r) {
        long long sum = a[l].first + a[r].first;
        if (sum == target) { cout << a[l].second << ' ' << a[r].second << '\n'; return 0; }
        if (sum < target) l++; else r--;
    }
    cout << "IMPOSSIBLE\n";
}
''',1:r'''#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
long long a[N];
int main() {
    int n; cin >> n; for (int i = 0; i < n; i++) cin >> a[i];
    unordered_map<long long, int> freq;
    int l = 0, best = 0;
    for (int r = 0; r < n; r++) { freq[a[r]]++; while (freq[a[r]] > 1) freq[a[l++]]--; best = max(best, r - l + 1); }
    cout << best << '\n';
}
'''},
'06-递归与分治.md':{0:r'''#include <bits/stdc++.h>
using namespace std;
const int N = 500005;
long long a[N], temporary[N];
long long solve(int l, int r) {
    if (r - l <= 1) return 0;
    int mid = l + (r - l) / 2;
    long long answer = solve(l, mid) + solve(mid, r);
    int i = l, j = mid, k = l;
    while (i < mid && j < r) {
        if (a[i] <= a[j]) temporary[k++] = a[i++];
        else { answer += mid - i; temporary[k++] = a[j++]; }
    }
    while (i < mid) temporary[k++] = a[i++];
    while (j < r) temporary[k++] = a[j++];
    for (int p = l; p < r; p++) a[p] = temporary[p];
    return answer;
}
int main() { int n; cin >> n; for (int i = 0; i < n; i++) cin >> a[i]; cout << solve(0, n) << '\n'; }
'''},
'08-搜索.md':{2:r'''#include <bits/stdc++.h>
using namespace std;
int n, path_value[15], depth;
bool used[15];
void dfs() {
    if (depth == n) { for (int i = 0; i < n; i++) cout << path_value[i] << (i + 1 == n ? '\n' : ' '); return; }
    for (int x = 1; x <= n; x++) {
        if (used[x]) continue;
        used[x] = true; path_value[depth++] = x; dfs(); depth--; used[x] = false;
    }
}
int main() { cin >> n; dfs(); }
''',3:r'''#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
char grid[N][N];
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> grid[i];
    int answer = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        if (grid[i][j] != '.') continue;
        answer++; stack<pair<int, int>> st; st.push({i, j}); grid[i][j] = '#';
        while (!st.empty()) {
            int x = st.top().first, y = st.top().second; st.pop();
            for (int d = 0; d < 4; d++) {
                int u = x + dx[d], v = y + dy[d];
                if (u < 0 || u >= n || v < 0 || v >= m || grid[u][v] != '.') continue;
                grid[u][v] = '#'; st.push({u, v});
            }
        }
    }
    cout << answer << '\n';
}
''',4:r'''#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
char grid[N][N];
int dist[N][N], from_direction[N][N];
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
string direction = "DURL";
int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> grid[i];
    pair<int, int> start = {-1, -1}, target = {-1, -1};
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        dist[i][j] = -1; from_direction[i][j] = -1;
        if (grid[i][j] == 'A') start = {i, j}; if (grid[i][j] == 'B') target = {i, j};
    }
    if (start.first < 0 || target.first < 0) { cout << "IMPOSSIBLE\n"; return 0; }
    queue<pair<int, int>> q; q.push(start); dist[start.first][start.second] = 0;
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second; q.pop();
        for (int d = 0; d < 4; d++) {
            int u = x + dx[d], v = y + dy[d];
            if (u < 0 || u >= n || v < 0 || v >= m || grid[u][v] == '#' || dist[u][v] != -1) continue;
            dist[u][v] = dist[x][y] + 1; from_direction[u][v] = d; q.push({u, v});
        }
    }
    int x = target.first, y = target.second;
    if (dist[x][y] == -1) { cout << "IMPOSSIBLE\n"; return 0; }
    string path;
    while (make_pair(x, y) != start) { int d = from_direction[x][y]; path += direction[d]; x -= dx[d]; y -= dy[d]; }
    reverse(path.begin(), path.end()); cout << dist[target.first][target.second] << '\n' << path << '\n';
}
'''},
'10-构造算法.md':{0:r'''#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    if (n == 2 || n == 3) { cout << "NO SOLUTION\n"; return 0; }
    bool first = true;
    for (int parity : {0, 1}) for (int x = parity == 0 ? 2 : 1; x <= n; x += 2) {
        if (!first) cout << ' '; cout << x; first = false;
    }
    cout << '\n';
}
''',2:r'''#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int a[N], pos[N], op_left[N], op_right[N], operation_count;
int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) { cin >> a[i]; pos[a[i]] = i; }
    for (int i = 0; i < n; i++) {
        if (a[i] == i + 1) continue;
        int j = pos[i + 1], other = a[i]; swap(a[i], a[j]); pos[i + 1] = i; pos[other] = j;
        op_left[operation_count] = i + 1; op_right[operation_count] = j + 1; operation_count++;
    }
    cout << operation_count << '\n';
    for (int i = 0; i < operation_count; i++) cout << op_left[i] << ' ' << op_right[i] << '\n';
}
'''},
'11-倍增思想.md':{0:r'''#include <bits/stdc++.h>
using namespace std;
const int N = 200005, LOG = 60;
int up[LOG][N];
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;
    for (int v = 0; v < n; v++) { cin >> up[0][v]; up[0][v]--; }
    for (int b = 1; b < LOG; b++) for (int v = 0; v < n; v++) up[b][v] = up[b - 1][up[b - 1][v]];
    while (q--) { int x; unsigned long long k; cin >> x >> k; x--; for (int b = 0; b < LOG; b++) if ((k >> b) & 1ULL) x = up[b][x]; cout << x + 1 << '\n'; }
}
'''},
'13-贡献法与计数思想.md':{1:r'''#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int a[N], count_value[N];
int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) { cin >> a[i]; count_value[a[i]]++; }
    long long total = 0;
    for (int i = 1; i <= n; i++) { long long count = count_value[i]; total += count * (count - 1) / 2; }
    for (int i = 0; i < n; i++) cout << total - (count_value[a[i]] - 1) << '\n';
}
'''},
'14-预处理与离线思想.md':{0:r'''#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
long long a[N];
pair<long long, int> queries[N];
int answer[N];
int main() {
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < q; i++) { cin >> queries[i].first; queries[i].second = i; }
    sort(a, a + n); sort(queries, queries + q);
    int p = 0;
    for (int i = 0; i < q; i++) { long long x = queries[i].first; int id = queries[i].second; while (p < n && a[p] <= x) p++; answer[id] = p; }
    for (int i = 0; i < q; i++) cout << answer[i] << '\n';
}
'''}
}
for filename,changes in replacements.items():
    p=root/filename;s=p.read_text(encoding='utf-8')
    blocks=re.findall(r'^[ \t]*```cpp\n(.*?)^[ \t]*```[ \t]*$',s,re.S|re.M)
    for i,code in changes.items():
        assert i < len(blocks),(filename,i,len(blocks));blocks[i]=code
    iterator=iter(blocks);s=re.sub(r'^[ \t]*```cpp\n.*?^[ \t]*```[ \t]*$',lambda m:'```cpp\n'+next(iterator).rstrip()+'\n```',s,flags=re.S|re.M)
    p.write_text(s,encoding='utf-8')
# Eliminate record structs from branch-and-bound; density sorting uses IDs and a simple comparator.
p=root/'12-搜索剪枝与折半搜索.md';s=p.read_text(encoding='utf-8')
blocks=re.findall(r'```cpp\n(.*?)```',s,re.S)
blocks[0]=blocks[0].replace('vector<string> board(8);','string board[8];')
blocks[2]=r'''#include <bits/stdc++.h>
using namespace std;
long long weight[30], value[30], best;
int order_id[30], n;
long long upper(int i, long long cap) {
    long long result = 0;
    for (; i < n; i++) {
        int id = order_id[i];
        if (weight[id] <= cap) { cap -= weight[id]; result += value[id]; }
        else { result += (value[id] * cap + weight[id] - 1) / weight[id]; break; }
    }
    return result;
}
void dfs(int i, long long cap, long long current) {
    best = max(best, current);
    if (i == n || current + upper(i, cap) <= best) return;
    int id = order_id[i];
    if (weight[id] <= cap) dfs(i + 1, cap - weight[id], current + value[id]);
    dfs(i + 1, cap, current);
}
int main() {
    long long W; cin >> n >> W;
    for (int i = 0; i < n; i++) { cin >> weight[i] >> value[i]; order_id[i] = i; }
    sort(order_id, order_id + n, [](int x, int y) { return value[x] * weight[y] > value[y] * weight[x]; });
    dfs(0, W, 0); cout << best << '\n';
}
'''
it=iter(blocks);s=re.sub(r'```cpp\n.*?```',lambda m:'```cpp\n'+next(it).rstrip()+'\n```',s,flags=re.S);p.write_text(s,encoding='utf-8')
print('Converted foundation array examples and removed custom record structs.')
