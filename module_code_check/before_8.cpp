#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m; cin >> n >> m;
    vector<string> g(n);
    for (auto &s : g) cin >> s;
    const int dx[4] = {1,-1,0,0}, dy[4] = {0,0,1,-1};
    int count = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        if (g[i][j] != '.') continue;
        ++count;
        stack<pair<int,int>> st;
        st.push({i,j}); g[i][j] = '#';
        while (!st.empty()) {
            auto [x,y] = st.top(); st.pop();
            for (int d = 0; d < 4; ++d) {
                int u = x+dx[d], v = y+dy[d];
                if (u<0 || u>=n || v<0 || v>=m || g[u][v]!='.') continue;
                g[u][v] = '#'; st.push({u,v});
            }
        }
    }
    cout << count << '\n';
}
