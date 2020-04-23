#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
typedef long long   data;
const   int N = 1e6 + 5;

int n, head, tail, q[N];
data X[N], p[N], c[N], f[N], sum[N], sump[N];

inline data W(int j, int i)
{
    return X[i] * (sump[i] - sump[j]) - (sum[i] - sum[j]);
}

inline data A(int x, int y)
{
    return f[x] + sum[x] - f[y] - sum[y];
}

inline data B(int x, int y)
{
    return sump[x] - sump[y];
}

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
        scanf("%lld%lld%lld", &X[i], &p[i], &c[i]);
    for(int i = 1; i <= n; i ++)
        sum[i] = sum[i-1] + X[i] * p[i];
    for(int i = 1; i <= n; i ++)
        sump[i] = sump[i-1] + p[i];
    for(int i = 1; i <= n; i ++)
    {
        while(head < tail && A(q[head + 1], q[head]) < X[i] * B(q[head + 1], q[head]))
            head ++;
        f[i] = f[q[head]] + W(q[head], i) + c[i];
        while(head < tail && A(q[tail], q[tail - 1]) * B(i, q[tail]) >= A(i, q[tail]) * B(q[tail], q[tail - 1]))
            // slope(i, tail) < slope(tail, tail - 1)
            tail --;
        q[++tail] = i;
    }
    printf("%lld", f[n]);
    return 0;
}
