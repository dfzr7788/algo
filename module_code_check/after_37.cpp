#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
long long raw[N], tag[N], block_sum[N];
int n, block_size;
void range_add(int l, int r, long long value)
{
    for (int i = l; i <= r;)
    {
        int b = i / block_size, end = min(n, (b + 1) * block_size);
        if (i == b * block_size && end - 1 <= r)
        {
            tag[b] += value;
            block_sum[b] += value * (end - i);
            i = end;
        }
        else
        {
            raw[i] += value;
            block_sum[b] += value;
            i++;
        }
    }
}
long long range_sum(int l, int r)
{
    long long answer = 0;
    for (int i = l; i <= r;)
    {
        int b = i / block_size, end = min(n, (b + 1) * block_size);
        if (i == b * block_size && end - 1 <= r)
        {
            answer += block_sum[b];
            i = end;
        }
        else
        {
            answer += raw[i] + tag[b];
            i++;
        }
    }
    return answer;
}
int main()
{
    int q;
    cin >> n >> q;
    block_size = max(1, (int)sqrt(n));
    for (int i = 0; i < n; i++)
    {
        cin >> raw[i];
        block_sum[i / block_size] += raw[i];
    }
    while (q--)
    {
        int type, l, r;
        cin >> type >> l >> r;
        l--;
        r--;
        if (type == 1)
        {
            long long value;
            cin >> value;
            range_add(l, r, value);
        }
        else
            cout << range_sum(l, r) << '\n';
    }
}
