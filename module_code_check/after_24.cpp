#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
long long a[N];
int main()
{
    int n;
    long long target;
    cin >> n >> target;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int l = 0;
    long long current = 0, answer = 0;
    for (int r = 0; r < n; r++)
    {
        current += a[r];
        while (l <= r && current > target)
            current -= a[l++];
        if (l <= r && current == target)
            answer++;
    }
    cout << answer << '\n';
}
