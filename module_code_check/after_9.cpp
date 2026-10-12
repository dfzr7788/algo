#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
char grid[N][N];
int dist[N][N], from_direction[N][N];
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
string direction = "DURL";
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> grid[i];
    pair<int, int> start = {-1, -1}, target = {-1, -1};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            dist[i][j] = -1;
            from_direction[i][j] = -1;
            if (grid[i][j] == 'A')
                start = {i, j};
            if (grid[i][j] == 'B')
                target = {i, j};
        }
    if (start.first < 0 || target.first < 0)
    {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    queue<pair<int, int>> q;
    q.push(start);
    dist[start.first][start.second] = 0;
    while (!q.empty())
    {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (int d = 0; d < 4; d++)
        {
            int u = x + dx[d], v = y + dy[d];
            if (u < 0 || u >= n || v < 0 || v >= m || grid[u][v] == '#' || dist[u][v] != -1)
                continue;
            dist[u][v] = dist[x][y] + 1;
            from_direction[u][v] = d;
            q.push({u, v});
        }
    }
    int x = target.first, y = target.second;
    if (dist[x][y] == -1)
    {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    string path;
    while (make_pair(x, y) != start)
    {
        int d = from_direction[x][y];
        path += direction[d];
        x -= dx[d];
        y -= dy[d];
    }
    reverse(path.begin(), path.end());
    cout << dist[target.first][target.second] << '\n' << path << '\n';
}
