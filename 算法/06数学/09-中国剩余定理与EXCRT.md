前置：[[06-裴蜀定理与扩展欧几里得]]、[[07-乘法逆元与阶乘逆元]]。

## 难度与重要程度

| 算法或主题 | 难度 | 重要程度 | 理由 |
|---|---:|---:|---|
| 经典CRT | 5/10 | 7/10 | 互质模数下构造统一余数 |
| 扩展CRT | 6/10 | 7/10 | 兼容不互质模数与冲突判断 |

评分为本项目学习路线的主观建议，统一口径见 [[00-数学]]。

## 同时满足多个余数条件

给定 x≡a_i mod m_i，要找最小非负 x。逐个整数试到所有条件满足可能扫描 lcm 个数。经典 CRT 要求模数两两互质：令 M=∏m_i，M_i=M/m_i，t_i 为 M_i 模 m_i 的逆元，x=Σa_iM_it_i mod M。第 i 项在其余模数下为 0，在 m_i 下为 a_i，因此构造正确。

例余数为 2 mod 3、3 mod 5、2 mod 7，M=105，三个分量分别 140、63、30，相加 233 mod 105=23。

## 不互质时逐条合并

维护已经处理的全部条件等价于 x≡r mod M。新条件 x≡a mod m，写 x=r+Mt，得到 Mt≡a−r mod m。g=gcd(M,m) 必须整除 a−r，否则无解。扩欧返回 Mu+mv=g，于是 t≡u(a−r)/g mod (m/g)。新周期为 M(m/g)，新余数为 r+Mt 对新周期取模。

例 x≡2 mod 6，x≡5 mod 9：g=3，差 3 可整除，6t≡3 mod 9，t≡2 mod 3，得到 x≡14 mod 18。改为余 4 时差 2，立即冲突。

输入 n，接着 n 行 m a，1<=n<=100000、1<=m<=10^12、0<=a<=10^12，保证全部模数 lcm<=10^18。输出最小非负解，无解输出 NO SOLUTION。与 [洛谷 P4777](https://www.luogu.com.cn/problem/P4777) 同模型，该题保证有解；教学程序额外处理冲突。

## 实现安全与复杂度

维护 0<=r<M；中间的 u×差值、M×t、系数回溯使用 __int128，即使最终结果不超过 10^18，中间也可能更大。n=0 在此未允许，若无条件可约定 x=0。

每次合并与原条件交集等价，归纳得到最终解集。时间 O(n log U)（U 为合并周期与模数的上界），递归空间 O(log U)，额外只保存当前余数和周期。最终周期超过范围时需要高精度，不能靠取模截断周期。

## 完整 C++17 教学程序

```cpp
#include <bits/stdc++.h>
using namespace std;

using i128 = __int128;

i128 extended_gcd(i128 a, i128 b, i128 &x, i128 &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    i128 x1, y1;
    i128 g = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    return g;
}

i128 normalize(i128 x, i128 mod)
{
    x %= mod;
    if (x < 0)
    {
        x += mod;
    }
    return x;
}

int main()
{
    int n;
    cin >> n;
    i128 remainder = 0;
    i128 period = 1;
    for (int i = 0; i < n; i++)
    {
        long long m, a;
        cin >> m >> a;
        i128 x, y;
        i128 g = extended_gcd(period, m, x, y);
        i128 difference = (i128)a - remainder;
        if (difference % g != 0)
        {
            cout << "NO SOLUTION\n";
            return 0;
        }
        i128 t = normalize(x * (difference / g), m / g);
        remainder += period * t;
        period *= m / g;
        remainder = normalize(remainder, period);
    }
    cout << (long long)remainder << '\n';
}
```

教学样例输入（不是平台官方样例）：

```text
2
6 2
9 5
```

输出：

```text
14
```

## 练习与复盘

先手算正文例子，再验证最小规模与常见错误。分层练习见 [[29-数学题单]]，独立建模见 [[30-数学综合练习]]。

返回：[[00-数学]]。
