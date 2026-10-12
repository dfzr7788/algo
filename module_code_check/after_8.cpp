#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
char grid[N][N];
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> grid[i];
    int answer = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] != '.')
                continue;
            answer++;
            stack<pair<int, int>> st;
            st.push({i, j});
            grid[i][j] = '#';
            while (!st.empty())
            {
                int x = st.top().first, y = st.top().second;
                st.pop();
                for (int d = 0; d < 4; d++)
                {
                    int u = x + dx[d], v = y + dy[d];
                    if (u < 0 || u >= n || v < 0 || v >= m || grid[u][v] != '.')
                        continue;
                    grid[u][v] = '#';
                    st.push({u, v});
                }
            }
        }
    cout << answer << '\n';
}
