#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 51;

struct Data
{
    int num[N], d;
} f[101];

int n;

Data Mul(Data a)
{
    for(int i = 1; i <= a.d; i ++)
        a.num[i] *= 3;
    for(int i = 1; i <= a.d; i ++)
    {
        if(a.num[i] >= 10)
        {
            a.num[i + 1] += a.num[i] / 10;
            a.num[i] %= 10;
        }
    }
    if(a.num[a.d + 1])
        a.d ++;
    return a;
}

Data Sub(Data a, Data b)
{
    int t = 1;
    a.num[1] += 2;
    while(a.num[t] >= 10)
    {
        a.num[t + 1] += a.num[t] / 10;
        a.num[t ++] %= 10;
    }
    for(int i = 1; i <= a.d; i ++)
    {
        a.num[i] -= b.num[i];
        if(a.num[i] < 0)
        {
            a.num[i] += 10;
            a.num[i + 1] --;
        }
    }
    while(!a.num[a.d])
        a.d --;
    return a;
}

int main(int argc, char **argv)
{
    f[1].d = f[2].d = 1;
    f[1].num[1] = 1, f[2].num[1] = 5;
    scanf("%d", &n);
    for(int i = 3; i <= n; i ++)
        f[i] = Sub(Mul(f[i - 1]), f[i - 2]);
    for(int i = f[n].d; i; i --)
        printf("%d", f[n].num[i]);
    return 0;
}
