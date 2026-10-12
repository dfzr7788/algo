#include <bits/stdc++.h>
using namespace std;
const int N = 200005, LOG = 60;
int up[LOG][N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    for (int v = 0; v < n; v++)
    {
        cin >> up[0][v];
        up[0][v]--;
    }
    for (int b = 1; b < LOG; b++)
        for (int v = 0; v < n; v++)
            up[b][v] = up[b - 1][up[b - 1][v]];
    while (q--)
    {
        int x;
        unsigned long long k;
        cin >> x >> k;
        x--;
        for (int b = 0; b < LOG; b++)
            if ((k >> b) & 1ULL)
                x = up[b][x];
        cout << x + 1 << '\n';
    }
}
