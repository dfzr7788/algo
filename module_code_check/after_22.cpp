#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
long long a[N];
pair<long long, int> queries[N];
int answer[N];
int main()
{
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < q; i++)
    {
        cin >> queries[i].first;
        queries[i].second = i;
    }
    sort(a, a + n);
    sort(queries, queries + q);
    int p = 0;
    for (int i = 0; i < q; i++)
    {
        long long x = queries[i].first;
        int id = queries[i].second;
        while (p < n && a[p] <= x)
            p++;
        answer[id] = p;
    }
    for (int i = 0; i < q; i++)
        cout << answer[i] << '\n';
}
