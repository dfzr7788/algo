#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;
pair<long long, long long> intervals[N];
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> intervals[i].first >> intervals[i].second;
    sort(intervals, intervals + n,
         [](const pair<long long, long long> &a, const pair<long long, long long> &b)
         {
             return a.second < b.second;
         });
    bool selected = false;
    long long last = 0;
    int answer = 0;
    for (int i = 0; i < n; i++)
    {
        long long l = intervals[i].first, r = intervals[i].second;
        if (!selected || l >= last)
        {
            answer++;
            last = r;
            selected = true;
        }
    }
    cout << answer << '\n';
}
