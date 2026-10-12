#include <bits/stdc++.h>
using namespace std;
const int S = (1 << 20) + 5;
long long a[45], left_sum[S], right_sum[S];
void generate_sums(int l, int r, long long sums[], int &count)
{
    count = 1;
    sums[0] = 0;
    for (int j = l; j < r; j++)
    {
        int previous_count = count;
        for (int i = 0; i < previous_count; i++)
            sums[count++] = sums[i] + a[j];
    }
}
int main()
{
    int n;
    long long target;
    cin >> n >> target;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int left_count, right_count, middle = n / 2;
    generate_sums(0, middle, left_sum, left_count);
    generate_sums(middle, n, right_sum, right_count);
    sort(right_sum, right_sum + right_count);
    long long answer = 0;
    for (int i = 0; i < left_count; i++)
    {
        auto range = equal_range(right_sum, right_sum + right_count, target - left_sum[i]);
        answer += range.second - range.first;
    }
    cout << answer << '\n';
}
