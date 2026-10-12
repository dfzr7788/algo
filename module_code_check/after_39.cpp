#include <bits/stdc++.h>
using namespace std;
const int N = 125;
long long a[N][N], col[N];
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    long long best = LLONG_MIN;
    for (int top = 0; top < n; top++)
    {
        fill(col, col + n, 0);
        for (int bottom = top; bottom < n; bottom++)
        {
            for (int j = 0; j < n; j++)
                col[j] += a[bottom][j];
            long long ending = col[0];
            best = max(best, ending);
            for (int j = 1; j < n; j++)
            {
                ending = max(col[j], ending + col[j]);
                best = max(best, ending);
            }
        }
    }
    cout << best << '\n';
}
