#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
long long a[N];
int n, k;
bool check(long long limit)
{
    int parts = 1;
    long long current = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] > limit)
            return false;
        if (current > limit - a[i])
        {
            parts++;
            current = a[i];
        }
        else
            current += a[i];
    }
    return parts <= k;
}
int main()
{
    cin >> n >> k;
    long long lo = 0, hi = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        lo = max(lo, a[i]);
        hi += a[i];
    }
    while (lo < hi)
    {
        long long mid = lo + (hi - lo) / 2;
        if (check(mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    cout << lo << '\n';
}
