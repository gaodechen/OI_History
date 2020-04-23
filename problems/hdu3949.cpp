#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
typedef long long data;
const int N = 10001;

int T, Q, n, tot;
bool zero;
data a[N];

inline void Gauss()
{
    zero = false;
    int p = 0, k;
    for(data i = (1LL << 60); i; i >>= 1)
    {
        for(k = p; k < n; k ++)
            if(a[k] & i)
                break ;
        if(k == n) continue ;
        swap(a[p], a[k]);
        for(int j = 0; j < n; j ++)
            if(j != p && (a[j] & i))
                a[j] ^= a[p];
        p ++;
    }
    if((tot = p) != n) zero = 1;
    return ;
}

inline data Query(data k)
{
    data r = 0;
    k -= zero;
    int i = 0;
    while(k != 0 && i < tot)
    {
        if(k & 1)
            r ^= a[tot - i - 1];
        k >>= 1, i ++;
    }
    if(i == tot && k)
        return -1;
    return r;
}

int main(int argc, char **argv)
{
    scanf("%d", &T);
    for(int t = 1; t <= T; t ++)
    {
        printf("Case #%d:\n", t);
        scanf("%d", &n);
        for(int i = 0; i < n; i ++)
            scanf("%I64d", &a[i]);
        Gauss();
        scanf("%d", &Q);
        while(Q --)
        {
            int k;
            scanf("%d", &k);
            printf("%I64d\n", Query(k));
        }
    }
    return 0;
}
