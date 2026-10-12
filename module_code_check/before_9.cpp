#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m; cin >> n >> m;
    vector<string> g(n);
    for (auto &s : g) cin >> s;
    pair<int,int> start{-1,-1}, target{-1,-1};
    for (int i=0; i<n; ++i) for (int j=0; j<m; ++j) {
        if (g[i][j]=='A') start={i,j};
        if (g[i][j]=='B') target={i,j};
    }
    if (start.first<0 || target.first<0) { cout<<"IMPOSSIBLE\n"; return 0; }
    vector<vector<int>> dist(n, vector<int>(m,-1)), from=dist;
    const int dx[4]={1,-1,0,0}, dy[4]={0,0,1,-1};
    const string move="DURL";
    queue<pair<int,int>> q;
    q.push(start); dist[start.first][start.second]=0;
    while (!q.empty()) {
        auto [x,y]=q.front(); q.pop();
        for (int d=0; d<4; ++d) {
            int u=x+dx[d], v=y+dy[d];
            if (u<0 || u>=n || v<0 || v>=m || g[u][v]=='#' || dist[u][v]!=-1) continue;
            dist[u][v]=dist[x][y]+1; from[u][v]=d; q.push({u,v});
        }
    }
    auto [x,y]=target;
    if (dist[x][y]==-1) { cout<<"IMPOSSIBLE\n"; return 0; }
    string path;
    while (make_pair(x,y)!=start) {
        int d=from[x][y]; path+=move[d]; x-=dx[d]; y-=dy[d];
    }
    reverse(path.begin(),path.end());
    cout<<dist[target.first][target.second]<<'\n'<<path<<'\n';
}
