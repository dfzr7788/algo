#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int a[N], pos[N], op_left[N], op_right[N], operation_count;
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        pos[a[i]] = i;
    }
    for (int i = 0; i < n; i++)
    {
        if (a[i] == i + 1)
            continue;
        int j = pos[i + 1], other = a[i];
        swap(a[i], a[j]);
        pos[i + 1] = i;
        pos[other] = j;
        op_left[operation_count] = i + 1;
        op_right[operation_count] = j + 1;
        operation_count++;
    }
    cout << operation_count << '\n';
    for (int i = 0; i < operation_count; i++)
        cout << op_left[i] << ' ' << op_right[i] << '\n';
}
