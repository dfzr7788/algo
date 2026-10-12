#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
long long a[N], values[N];
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        values[i] = a[i];
    }
    sort(values, values + n);
    int count = unique(values, values + n) - values;
    for (int i = 0; i < n; i++)
        cout << lower_bound(values, values + count, a[i]) - values << '\n';
}
