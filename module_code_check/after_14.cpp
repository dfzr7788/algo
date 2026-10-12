#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;
int group_a[N], group_b[N], count_a, count_b;
void print_group(int group[], int count)
{
    cout << count << '\n';
    for (int i = 0; i < count; i++)
        cout << group[i] << ' ';
    cout << '\n';
}
int main()
{
    int n;
    cin >> n;
    if (n % 4 != 0 && n % 4 != 3)
    {
        cout << "NO\n";
        return 0;
    }
    int start = 1;
    if (n % 4 == 3)
    {
        group_a[count_a++] = 1;
        group_a[count_a++] = 2;
        group_b[count_b++] = 3;
        start = 4;
    }
    for (int x = start; x <= n; x += 4)
    {
        group_a[count_a++] = x;
        group_a[count_a++] = x + 3;
        group_b[count_b++] = x + 1;
        group_b[count_b++] = x + 2;
    }
    cout << "YES\n";
    print_group(group_a, count_a);
    print_group(group_b, count_b);
}
