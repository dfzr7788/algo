#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
long long pre[N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        long long x;
        cin >> x;
        pre[i] = pre[i - 1] + x;
    }
    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        cout << pre[r] - pre[l - 1] << '\n';
    }
}
