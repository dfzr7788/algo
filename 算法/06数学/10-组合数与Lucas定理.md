前置：[[07-乘法逆元与阶乘逆元]]。

## 难度与重要程度

| 算法或主题 | 难度 | 重要程度 | 理由 |
|---|---:|---:|---|
| 加法乘法原理 | 2/10 | 10/10 | 互斥分类与独立选择 |
| Pascal组合数递推 | 3/10 | 9/10 | 适用于任意正模数 |
| 阶乘法组合数 | 4/10 | 10/10 | 大量素数模数询问 |
| Lucas定理 | 5/10 | 7/10 | 小素数模数下的大n |

评分为本项目学习路线的主观建议，统一口径见 [[00-数学]]。

## 先确定对象是否有序

互斥分类用加法原理，逐步独立选择用乘法原理。n 个不同对象选 k 个并排列为 $A(n,k)=n!/(n-k)!$；只选集合为 $C(n,k)=n!/[k!(n-k)!]$，因为每个集合对应 $k!$ 个排列。不要把相同对象与不同对象混为一谈。

例 5 人选 2 人当普通成员，10 种；选队长和副队长，20 种。$C(n,0)=C(n,n)=1$，$k<0$ 或 $k>n$ 时为 0。

## 三种计算方法按条件选择

Pascal 递推 $C(n,k)=C(n-1,k-1)+C(n-1,k)$，按“是否选指定对象”划分。$O(NK)$ 时间、$O(K)$ 滚动空间，对任意正模数都成立，逆向更新防止本轮重复使用。

素数 p 且 $N<p$ 时，阶乘与阶乘逆元预处理 $O(N+\log p)$、空间 $O(N)$，每次 $O(1)$。$N\ge p$ 会遇到零阶乘，不能继续套公式。

小素数 p、大 n 时，用 Lucas 定理按 p 进制逐位相乘：$C(n,k)\equiv \prod C(n_i,k_i) \bmod p$。预处理到 $p-1$ 后，每次 $O(\log_p(n+1))$。例如 $C(8,3) \bmod 5$，$8=(13)_5$，$3=(03)_5$，结果 $C(1,0)C(3,3)=1$，对应 $56 \bmod 5=1$。

## 程序约定与应用

输入 T，再 T 行 n k p，$0\le n,k\le 10^{18}$，p 为素数且 $2\le p\le 1000000$，逐行输出 $C(n,k) \bmod p$。每组重新建立阶乘表。此模板是教学的大 n 版本；[洛谷 P3807](https://www.luogu.com.cn/problem/P3807) 输入 n,m,p 求的是 $C(n+m,n)$，需要传 $n+m$ 与 n，且多测范围不同。

非负整数解 $x1+\ldots+xr=s$（$r\ge 1$）可插板得到 $C(s+r-1,r-1)$。每个 $xi\ge 1$ 则平移成 $C(s-1,r-1)$。有上界时不能只用插板，见 [[11-容斥原理]]。组合概率除以总方案数时还要检查分母模 p 是否为 0。

## 扩展选读：Lucas为什么按位

在模素数 p 下 $(1+x)^{p}\equiv 1+x^{p}$，因此将 n 的 p 进制展开代入 $(1+x)^{n}$，按不同位选择项，比较 $x^{k}$ 系数可得到按位乘积。p 非素数时这个推导不成立，合数模组合数属于后续选学。

## 完整 C++17 教学程序

```cpp
#include <bits/stdc++.h>
using namespace std;

long long power_mod(long long a, long long b, long long mod)
{
    a %= mod;
    if (a < 0)
    {
        a += mod;
    }
    long long result = 1 % mod;
    while (b > 0)
    {
        if (b & 1)
        {
            result = (__int128)result * a % mod;
        }
        a = (__int128)a * a % mod;
        b >>= 1;
    }
    return result;
}

const int MAXN = 1000000 + 5;
long long fac[MAXN], ifac[MAXN];
long long mod_value;

void build_factorials(int n)
{
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        fac[i] = fac[i - 1] * i % mod_value;
    }
    ifac[n] = power_mod(fac[n], mod_value - 2, mod_value);
    for (int i = n; i >= 1; i--)
    {
        ifac[i - 1] = ifac[i] * i % mod_value;
    }
}

long long combination(int n, int k)
{
    if (k < 0 || k > n)
    {
        return 0;
    }
    return fac[n] * ifac[k] % mod_value * ifac[n - k] % mod_value;
}

long long lucas(long long n, long long k)
{
    long long result = 1;
    while (n > 0 || k > 0)
    {
        result = result * combination(n % mod_value, k % mod_value) % mod_value;
        n /= mod_value;
        k /= mod_value;
    }
    return result;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long n, k;
        cin >> n >> k >> mod_value;
        build_factorials(mod_value - 1);
        cout << lucas(n, k) << '\n';
    }
}
```

教学样例输入（不是平台官方样例）：

```text
2
8 3 5
3 4 7
```

输出：

```text
1
0
```

## 补充实现

Pascal滚动数组的独立程序：输入 $0\le n,k\le 2000$、$1\le \mathrm{mod}\le 10^{9}$，输出 $C(n,k)$ 的余数。按n轮更新、每轮k倒序，$j=0$ 固定为`1%mod`。$O((n+1)(k+1))$ 时间、$O(k+1)$ 空间，对合数模同样成立；k=0 仍有外层循环成本。

```cpp
#include <bits/stdc++.h>
using namespace std;

long long row[2000 + 5];

int main()
{
    int n, k;
    long long mod;
    cin >> n >> k >> mod;
    row[0] = 1 % mod;
    for (int i = 1; i <= n; i++)
    {
        for (int j = k; j >= 1; j--)
        {
            row[j] = (row[j] + row[j - 1]) % mod;
        }
    }
    cout << row[k] << '\n';
}
```

教学样例输入：

```text
5 2 6
```

输出：

```text
4
```

## 练习与复盘

先手算正文例子，再验证最小规模与常见错误。分层练习见 [[29-数学题单]]，独立建模见 [[30-数学综合练习]]。

返回：[[00-数学]]。
