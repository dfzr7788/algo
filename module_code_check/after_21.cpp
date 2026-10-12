#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int a[N], count_value[N];
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        count_value[a[i]]++;
    }
    long long total = 0;
    for (int i = 1; i <= n; i++)
    {
        long long count = count_value[i];
        total += count * (count - 1) / 2;
    }
    for (int i = 0; i < n; i++)
        cout << total - (count_value[a[i]] - 1) << '\n';
}
