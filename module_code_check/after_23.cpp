#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
long double a[N];
int n;
long double evaluate(long double x)
{
    long double result = 0;
    for (int i = 0; i < n; i++)
    {
        long double difference = x - a[i];
        result += difference * difference;
    }
    return result;
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    long double l = *min_element(a, a + n), r = *max_element(a, a + n);
    for (int it = 0; it < 150; it++)
    {
        long double m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        long double v1 = evaluate(m1), v2 = evaluate(m2);
        if (v1 > v2)
            l = m1;
        else if (v1 < v2)
            r = m2;
        else
        {
            l = m1;
            r = m2;
        }
    }
    long double x = (l + r) / 2;
    cout << fixed << setprecision(10) << x << ' ' << evaluate(x) << '\n';
}
