#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
long long a[N];
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a, a + n);
    int count = unique(a, a + n) - a;
    cout << count << '\n';
}
