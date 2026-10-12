#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
long long a[N], times[N], delta[N], value[N];
int left_end[N], right_end[N];
int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= m; i++)
        cin >> left_end[i] >> right_end[i] >> value[i];
    while (k--)
    {
        int x, y;
        cin >> x >> y;
        times[x]++;
        times[y + 1]--;
    }
    for (int i = 1; i <= m; i++)
    {
        times[i] += times[i - 1];
        long long change = times[i] * value[i];
        delta[left_end[i]] += change;
        delta[right_end[i] + 1] -= change;
    }
    for (int i = 1; i <= n; i++)
    {
        delta[i] += delta[i - 1];
        if (i > 1)
            cout << ' ';
        cout << a[i] + delta[i];
    }
    cout << '\n';
}
