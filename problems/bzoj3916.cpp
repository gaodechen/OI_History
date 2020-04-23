#include    <cstdio>
#include    <cstring>
#include    <iostream>

typedef unsigned long long data;
using   namespace   std;
const   int N = 2000002;
const   int BASE = 13131;

int n, mid;
char s[N], ans[N>>1];
data h0, hash[N], pow[N];

inline data Hash(int l, int r)
{
    return l > r ? 0 : hash[r] - hash[l-1] * pow[r-l+1];
}

inline bool Check(int p)
{
    data h1, h2;
    if(p < mid)
        h1 = Hash(1, p - 1) * pow[mid-p] + Hash(p + 1, mid), h2 = Hash(mid + 1, n);
    else if(p > mid)
        h1 = Hash(1, mid - 1), h2 = Hash(mid, p - 1) * pow[n-p] + Hash(p + 1, n);
    else
        h1 = Hash(1, mid - 1), h2 = Hash(mid + 1, n);
    if(h1 == h2)
    {
        if(h1 == h0)
            return 0;
        h0 = h1;
        if(p <= mid) for(int i = mid + 1, top = 0; i <= n; i ++)
            ans[++top] = s[i];
        else for(int i = 1; i < mid; i ++)
            ans[i] = s[i];
        return 1;
    }
    return 0;
}

int main()
{
    scanf("%d", &n);
    if(!(n & 1))
    {
        puts("NOT POSSIBLE");
        return 0;
    }
    mid = n / 2 + 1;
    scanf("%s", s + 1);
    pow[0] = 1;
    for(int i = 1; i <= n; i ++)
        pow[i] = pow[i-1] * BASE;
    for(int i = 1; i <= n; i ++)
        hash[i] = hash[i-1] * BASE + s[i];
    int cnt = 0;
    for(int i = 1; i <= n; i ++)
    {
        cnt += Check(i);
        if(cnt > 1)
            break ;
    }
    if(!cnt)
        puts("NOT POSSIBLE");
    else if(cnt == 1)
        puts(ans + 1);
    else
        puts("NOT UNIQUE");
    return 0;
}
