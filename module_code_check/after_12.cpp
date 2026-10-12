#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
pair<long long, long long> jobs[N];
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> jobs[i].second >> jobs[i].first;
    sort(jobs, jobs + n);
    priority_queue<long long> chosen;
    long long total = 0;
    for (int i = 0; i < n; i++)
    {
        long long deadline = jobs[i].first, duration = jobs[i].second;
        total += duration;
        chosen.push(duration);
        if (total > deadline)
        {
            total -= chosen.top();
            chosen.pop();
        }
    }
    cout << chosen.size() << '\n';
}
