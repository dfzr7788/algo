#include <bits/stdc++.h>
using namespace std;
const int N = 500005;
long long a[N], temporary[N];
long long solve(int l, int r)
{
    if (r - l <= 1)
        return 0;
    int mid = l + (r - l) / 2;
    long long answer = solve(l, mid) + solve(mid, r);
    int i = l, j = mid, k = l;
    while (i < mid && j < r)
    {
        if (a[i] <= a[j])
            temporary[k++] = a[i++];
        else
        {
            answer += mid - i;
            temporary[k++] = a[j++];
        }
    }
    while (i < mid)
        temporary[k++] = a[i++];
    while (j < r)
        temporary[k++] = a[j++];
    for (int p = l; p < r; p++)
        a[p] = temporary[p];
    return answer;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << solve(0, n) << '\n';
}
