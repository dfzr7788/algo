#include <bits/stdc++.h>
using namespace std;
long long weight[30], value[30], best;
int order_id[30], n;
long long upper(int i, long long cap)
{
    long long result = 0;
    for (; i < n; i++)
    {
        int id = order_id[i];
        if (weight[id] <= cap)
        {
            cap -= weight[id];
            result += value[id];
        }
        else
        {
            result += (value[id] * cap + weight[id] - 1) / weight[id];
            break;
        }
    }
    return result;
}
void dfs(int i, long long cap, long long current)
{
    best = max(best, current);
    if (i == n || current + upper(i, cap) <= best)
        return;
    int id = order_id[i];
    if (weight[id] <= cap)
        dfs(i + 1, cap - weight[id], current + value[id]);
    dfs(i + 1, cap, current);
}
int main()
{
    long long W;
    cin >> n >> W;
    for (int i = 0; i < n; i++)
    {
        cin >> weight[i] >> value[i];
        order_id[i] = i;
    }
    sort(order_id, order_id + n,
         [](int x, int y)
         {
             return value[x] * weight[y] > value[y] * weight[x];
         });
    dfs(0, W, 0);
    cout << best << '\n';
}
