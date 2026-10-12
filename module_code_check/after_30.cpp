#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
long long d[N][N];
void rectangle_add(int x1, int y1, int x2, int y2)
{
    d[x1][y1]++;
    d[x2 + 1][y1]--;
    d[x1][y2 + 1]--;
    d[x2 + 1][y2 + 1]++;
}
int main()
{
    int n, q;
    cin >> n >> q;
    while (q--)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        rectangle_add(x1, y1, x2, y2);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            d[i][j] += d[i - 1][j] + d[i][j - 1] - d[i - 1][j - 1];
            if (j > 1)
                cout << ' ';
            cout << d[i][j];
        }
        cout << '\n';
    }
}
