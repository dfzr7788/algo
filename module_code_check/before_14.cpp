#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    if (n%4 != 0 && n%4 != 3) { cout << "NO\n"; return 0; }
    vector<int> a, b;
    int start = 1;
    if (n%4 == 3) { a = {1,2}; b = {3}; start = 4; }
    for (int x = start; x <= n; x += 4) {
        a.push_back(x); a.push_back(x+3);
        b.push_back(x+1); b.push_back(x+2);
    }
    auto print = [](const vector<int> &v) {
        cout << v.size() << '\n';
        for (int x : v) cout << x << ' ';
        cout << '\n';
    };
    cout << "YES\n"; print(a); print(b);
}
