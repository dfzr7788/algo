#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int a[N], next_value[N];
int main()
{
    int n, t;
    cin >> n >> t;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int step = 0; step < t; step++)
    {
        for (int i = 0; i < n; i++)
            next_value[i] = a[i] ^ a[(i + n - 1) % n];
        for (int i = 0; i < n; i++)
            a[i] = next_value[i];
    }
    for (int i = 0; i < n; i++)
    {
        if (i > 0)
            cout << ' ';
        cout << a[i];
    }
    cout << '\n';
}
