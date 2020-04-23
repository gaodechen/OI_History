#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
typedef long long   data;
const   int N = 1e6 + 5;

int n, pos, L[N], R[N];
data m, a[N], b[N], sum[N];

inline bool Check(data lim)
{
    data cost = 0;
    memcpy(b, a, sizeof(a));
    for(int i = 2; i <= n; i ++)
    {
        if(b[i] - b[i-1] > lim)
        {
            cost += b[i] - b[i-1] - lim;
            b[i] = b[i-1] + lim;
        }
    }
    for(int i = n - 1; i >= 1; i --)
    {
        if(b[i] - b[i+1] > lim)
        {
            cost += b[i] - b[i+1] - lim;
            b[i] = b[i+1] + lim;
        }
    }
    if(cost > m)
        return false;
    for(int i = 1; i <= n; i ++)
        sum[i] = sum[i-1] + b[i];
    for(int i = 1, j = 1; i <= n; i ++)
    {
        while(b[j] < (data) (i - j) * lim)
            j ++;
        L[i] = j;
    }
    for(int i = n, j = n; i >= 1; i --)
    {
        while(b[j] < (data) (j - i) * lim)
            j --;
        R[i] = j;
    }
    for(int i = 1; i <= n; i ++)
    {
        data tmp = sum[R[i]] - sum[L[i]-1];
        tmp -= (data) lim * (i - L[i]) * (i - L[i] + 1) / 2;
        tmp -= (data) lim * (R[i] - i) * (R[i] - i + 1) / 2;
        if(cost + tmp <= m)
        {
            pos = i;
            return true;
        }
    }
    return false;
}

int main()
{
    scanf("%d%lld", &n, &m);
    for(int i = 1; i <= n; i ++)
        scanf("%lld", &a[i]);
    int l = 0, r = 1e9;
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(Check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    Check(l);
    printf("%d %d", pos, l );
    return 0;
}
