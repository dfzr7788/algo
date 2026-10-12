#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
pair<long long, int> a[N];
int main()
{
    int n;
    long long target;
    cin >> n >> target;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].first;
        a[i].second = i + 1;
    }
    sort(a, a + n);
    int l = 0, r = n - 1;
    while (l < r)
    {
        long long sum = a[l].first + a[r].first;
        if (sum == target)
        {
            cout << a[l].second << ' ' << a[r].second << '\n';
            return 0;
        }
        if (sum < target)
            l++;
        else
            r--;
    }
    cout << "IMPOSSIBLE\n";
}
