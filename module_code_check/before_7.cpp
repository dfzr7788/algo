#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> path;
vector<bool> used;
void dfs() {
    if ((int)path.size() == n) {
        for (int i = 0; i < n; ++i) cout << path[i] << (i+1==n ? '\n' : ' ');
        return;
    }
    for (int x = 1; x <= n; ++x) if (!used[x]) {
        used[x] = true; path.push_back(x);
        dfs();
        path.pop_back(); used[x] = false;
    }
}
int main() { cin >> n; used.assign(n+1, false); dfs(); }
