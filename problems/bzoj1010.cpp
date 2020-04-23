#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
typedef long long   data;
const   int N = 5e4 + 5;
const   int INF = 0x3f3f3f3f;

data d[N], s[N];
int n, l, q[N], head, tail;

inline data sqr(data x)
{
    return x * x;
}

inline data S(int x, int y)
{
    return d[x] - d[y] + sqr(s[x]) - sqr(s[y]);
}

inline data G(int x, int y)
{
    return 2 * (s[x] - s[y]);
}

int main(int argc, char **argv)
{
    scanf("%d%d", &n, &l), l ++;
    for(int i = 1; i <= n; i ++)
        scanf("%lld", &s[i]);
    for(int i = 1; i <= n; i ++)
        s[i] += s[i - 1] + 1;
    for(int i = 1; i <= n; i ++)
    {
        while(head < tail && S(q[head + 1], q[head]) <= (s[i] - l) * G(q[head + 1], q[head]))
            head ++;
        d[i] = d[q[head]] + sqr(s[i] - s[q[head]] - l);
        while(head < tail && S(q[tail - 1], q[tail]) * G(q[tail], i) > S(q[tail], i) * G(q[tail - 1], q[tail]))
            tail --;
        q[++ tail] = i;
    }
    printf("%lld", d[n]);
    return 0;
}
