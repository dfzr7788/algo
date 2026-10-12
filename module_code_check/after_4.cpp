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
    unordered_map<long long, int> freq;
    int l = 0, best = 0;
    for (int r = 0; r < n; r++)
    {
        freq[a[r]]++;
        while (freq[a[r]] > 1)
            freq[a[l++]]--;
        best = max(best, r - l + 1);
    }
    cout << best << '\n';
}
