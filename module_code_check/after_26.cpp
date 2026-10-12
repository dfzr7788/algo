#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    long long K;
    cin >> n >> K;
    unordered_map<long long, long long> freq;
    freq[0] = 1;
    long long pre = 0, ans = 0;
    for (int i = 0; i < n; ++i)
    {
        long long x;
        cin >> x;
        pre += x;
        auto it = freq.find(pre - K);
        if (it != freq.end())
            ans += it->second;
        ++freq[pre];
    }
    cout << ans << '\n';
}
