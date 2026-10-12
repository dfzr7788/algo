#include <bits/stdc++.h>
using namespace std;
long long a[25];
int main()
{
    int n;
    cin >> n;
    long long total = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        total += a[i];
    }
    long long best = total;
    for (unsigned mask = 0; mask < (1u << n); mask++)
    {
        long long sum = 0;
        for (int i = 0; i < n; i++)
            if (mask & (1u << i))
                sum += a[i];
        best = min(best, llabs(sum - (total - sum)));
    }
    cout << best << '\n';
}
