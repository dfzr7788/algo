#include <bits/stdc++.h>
using namespace std;
const int N = 5000005;
long long d[N];
void range_add(int l, int r, long long value)
{
    d[l] += value;
    d[r + 1] -= value;
}
int main()
{
    int n, q;
    cin >> n >> q;
    long long previous = 0;
    for (int i = 1; i <= n; i++)
    {
        long long x;
        cin >> x;
        d[i] = x - previous;
        previous = x;
    }
    while (q--)
    {
        int l, r;
        long long value;
        cin >> l >> r >> value;
        range_add(l, r, value);
    }
    long long current = 0;
    for (int i = 1; i <= n; i++)
    {
        current += d[i];
        if (i > 1)
            cout << ' ';
        cout << current;
    }
    cout << '\n';
}
