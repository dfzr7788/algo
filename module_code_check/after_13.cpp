#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    if (n == 2 || n == 3)
    {
        cout << "NO SOLUTION\n";
        return 0;
    }
    bool first = true;
    for (int parity : {0, 1})
        for (int x = parity == 0 ? 2 : 1; x <= n; x += 2)
        {
            if (!first)
                cout << ' ';
            cout << x;
            first = false;
        }
    cout << '\n';
}
