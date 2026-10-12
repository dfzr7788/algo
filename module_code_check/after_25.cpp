#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
long long a[N], goal;
int n;
bool check(long long time)
{
    long long made = 0;
    for (int i = 0; i < n; i++)
    {
        long long add = time / a[i];
        if (add >= goal - made)
            return true;
        made += add;
    }
    return false;
}
int main()
{
    cin >> n >> goal;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    long long lo = 0, hi = *min_element(a, a + n) * goal;
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
