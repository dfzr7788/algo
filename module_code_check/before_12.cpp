#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin>>n;
    vector<pair<long long,long long>> jobs(n);
    // 存储为 (截止时间, 耗时)，输入为 t d。
    for (auto &[d,t] : jobs) cin>>t>>d;
    sort(jobs.begin(),jobs.end());
    priority_queue<long long> chosen;
    long long total=0;
    for (auto [d,t] : jobs) {
        total+=t; chosen.push(t);
        if (total>d) { total-=chosen.top(); chosen.pop(); }
    }
    cout<<chosen.size()<<'\n';
}
