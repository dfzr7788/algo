#include <bits/stdc++.h>
using namespace std;
int n, path_value[15], depth;
bool used[15];
void dfs()
{
    if (depth == n)
    {
        for (int i = 0; i < n; i++)
            cout << path_value[i] << (i + 1 == n ? '\n' : ' ');
        return;
    }
    for (int x = 1; x <= n; x++)
    {
        if (used[x])
            continue;
        used[x] = true;
        path_value[depth++] = x;
        dfs();
        depth--;
        used[x] = false;
    }
}
int main()
{
    cin >> n;
    dfs();
}
