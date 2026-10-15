前置：[[20-群论基础与置换循环]]、[[07-乘法逆元与阶乘逆元]]。

## 难度与重要程度

| 算法或主题 | 难度 | 重要程度 | 理由 |
|---|---:|---:|---|
| Burnside引理 | 6/10 | 6/10 | 按对称变换的不动点计数 |
| Polya与循环计数 | 7/10 | 5/10 | 独立染色用循环数量代替逐方案检查 |

评分为本项目学习路线的主观建议，统一口径见 [[00-数学]]。

## 为什么不能总数直接除以旋转数

n 个位置、c 种颜色，全部染色有 $c^{n}$ 种。只允许旋转等价时，一个全同色方案旋转后只有 1 个，而一般方案可能有 n 个，轨道大小不同，直接 $c^{n}/n$ 会出错。

Burnside 引理给出轨道数 $(1/\lvert G\rvert )\sum _g Fix(g)$。对每个位置置换 g，要保持染色不变，同一个循环必须同色，不同循环独立，因此 $Fix(g)=c^{\mathrm{cycles}(g)}$。本篇主讲 Burnside 与无颜色数量约束的 Polya 特例；完整循环指标为后续选学。这个是无颜色数量约束时的 Polya 特例；完整 Polya 循环指标用每个循环长度的变量替换，能处理指定颜色个数，不能把任何染色约束都简化成 $c^{\text{循环数}}$。

## 三个位置的手算

$n=3,c=2$，只允许旋转。单位旋转有 3 个循环、$Fix=8$；旋转 1、2 格各 1 个循环、$Fix=2$。总数 $(8+2+2)/3=4$：全色0、全色1、两个0一个1、两个1一个0。

旋转 r 格时循环数 $\gcd (n,r)$。仅旋转的答案为 $\sum _{r=0}^{n-1}c^{\gcd (n,r)}/n$。若允许翻转，群增为 2n：奇数 n 每个反射循环数 $(n+1)/2$；偶数 n 有 n/2 个经过对顶点的反射（$n/2+1$ 个循环）、n/2 个经过对边的反射（n/2 个循环）。题目允许哪些变换必须先明确。

## 实现与条件

程序输入 $1\le n\le 100000$、$0\le c\le 10^{9}$，输出仅旋转等价下的染色数 mod 1000000007。$n<p$，所以能用 n 的逆元，$c=0$ 且 $n>0$ 时答案为 0。若 |G| 是模数的倍数，不能直接乘逆元；可在更大的模数 |G|p 下累加，再在整数中除 |G|，或用高精度。

直接 n 次 gcd 与快速幂为 $O(n \log n)$，空间 $O(1)$，循环中 gcd 与指数为 gcd(n,r) 的快速幂各需 $O(\log(n+1))$ 次固定宽度操作，最后求逆元再用 $O(\log p)$ 次模乘；约 30 位的是固定指数 p−2，而不是所有染色幂的指数。可按 d|n 分组，将旋转和写为 $\sum _{d|n}\varphi (n/d)c^{d}$；这是性能变体，需要因子与 $\varphi$ 的额外计算。

## 扩展选读：引理的双计数

统计所有 $(g,x)$ 且 g 固定 x 的对。按 g 得 $\sum Fix(g)$，按 x 得 $\sum \lvert \mathrm{Stab}(x)\rvert$。同一轨道中每个 x 的稳定子大小为 |G|/轨道大小，因此该轨道贡献恰 |G|。除以 |G| 即轨道数。

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

int main()
{
    long long n, colors;
    cin >> n >> colors;
    const long long MOD = 1000000007;
    long long sum = 0;
    for (long long shift = 0; shift < n; shift++)
    {
        sum = (sum + power_mod(colors, gcd(n, shift), MOD)) % MOD;
    }
    cout << sum * power_mod(n, MOD - 2, MOD) % MOD << '\n';
}
```

教学样例输入（不是平台官方样例）：

```text
3 2
```

输出：

```text
4
```

## 练习与复盘

先手算正文例子，再验证最小规模与常见错误。分层练习见 [[29-数学题单]]，独立建模见 [[30-数学综合练习]]。

返回：[[00-数学]]。
