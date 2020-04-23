#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
typedef long long   data;
const   int MOD = 20100403;

void ExtendedGCD(int a, int b, data &x, data &y)
{
    if(b == 0)
        x = 1, y = 0;
    else
    {
        ExtendedGCD(b, a % b, y, x);
        y -= x * (a / b);
    }
    return ;
}

data inv(int a)
{
    data x, y;
    ExtendedGCD(a, MOD, x, y);
    return (x % MOD + MOD) % MOD;
}

data fact(int n)
{
    data r = 1;
    for(int i = 1; i <= n; i ++)
        r = r * i % MOD;
    return r;
}

data C(int n, int m)
{
    return fact(n) * inv(fact(m)) % MOD * inv(fact(n - m)) % MOD;
}

int main()
{
    int n, m;
    cin >> n >> m;
    int r = ((C(n + m, n) - C(n + m, n + 1)) % MOD + MOD) % MOD;
    cout << r << endl;
    return 0;
}
