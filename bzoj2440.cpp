#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <cmath>

using   namespace   std;
const   int N = 46000;

bool mark[N];
int tot, prime[N], mu[N];

inline void InitTable()
{
    mu[1] = 1;
    for(int i = 2; i < N; i ++)
    {
        if(!mark[i])
        {
            prime[tot++] = i;
            mu[i] = -1;
        }
        for(int j = 0, k; j < tot && (k = i * prime[j]) < N; j ++)
        {
            mark[k] = 1;
            if(i % prime[j] == 0)
            {
                mu[k] = 0;
                break ;
            }
            mu[k] = -mu[i];
        }
    }
    for(int i = 1; i < N; i ++)
        mu[i] += mu[i-1];
    return ;
}

inline int Sum(int k)
{
    int r = 0;
    for(int i = 1, next; i * i <= k; i = next + 1)
    {
        int n = k / i / i;
        next = sqrt(k / n);
        r += (mu[next] - mu[i-1]) * n;
    }
    return r;
}

int main()
{
    int T, a;
    InitTable();
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d", &a);
        int l = 1, r = a + a;
        while(l < r)
        {
            int mid = l + ((r - l) >> 1);
            if(Sum(mid) < a)
                l = mid + 1;
            else
                r = mid;
        }
        printf("%d\n", l);
    }
    return 0;
}
