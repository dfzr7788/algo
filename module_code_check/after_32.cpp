#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
pair<long long, long long> intervals[N];
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> intervals[i].first >> intervals[i].second;
    sort(intervals, intervals + n);
    long long total = 0, l = 0, r = 0;
    bool active = false;
    for (int i = 0; i < n; i++)
    {
        long long x = intervals[i].first, y = intervals[i].second;
        if (!active)
        {
            l = x;
            r = y;
            active = true;
        }
        else if (x <= r)
            r = max(r, y);
        else
        {
            total += r - l;
            l = x;
            r = y;
        }
    }
    if (active)
        total += r - l;
    cout << total << '\n';
}
