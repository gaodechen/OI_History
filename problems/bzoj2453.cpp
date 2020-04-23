#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <cmath>
#include    <vector>
#include    <algorithm>

using   namespace   std;
const   int N = 1e4 + 5;
const   int M = 1e6 + 5;

inline int in()
{
    int k = 0, c = '\0';
    for(; c > '9' || c < '0';)
        c = getchar();
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return k;
}

int n, m, q, B;
int a[N], pre[N], pos[N], last[M];
vector<int> block[N];

inline void Extract(int k)
{
    int l = B * (k - 1) + 1, r = min(k * B, n);
    block[k].clear();
    for(int i = l; i <= r; i ++)
        block[k].push_back(pre[i]);
    sort(block[k].begin(), block[k].end());
    return ;
}

inline void InitBlock()
{
    for(int i = 1; i <= n; i ++)
    {
        pre[i] = last[a[i]];
        last[a[i]] = i;
        pos[i] = (i + B - 1) / B;
    }
    m = (n + B - 1) / B;
    for(int i = 1; i <= m; i ++)
        Extract(i);
    return ;
}

inline int Count(int l, int r, int p)
{
    int sum = 0;
    for(int i = l; i <= r; i ++)
        if(pre[i] < p) sum ++;
    return sum;
}

inline int Query(int l, int r)
{
    if(pos[l] == pos[r])
        return Count(l, r, l);
    int sum = 0;
    sum += Count(l, B * pos[l], l);
    sum += Count(B * (pos[r] - 1) + 1, r, l);
    int a = Count(l, B * pos[l], l);
    int b = Count(B * (pos[r] - 1) + 1, r, l);
    for(int i = pos[l] + 1; i < pos[r]; i ++)
        sum += upper_bound(block[i].begin(), block[i].end(), l - 1) - block[i].begin();
    return sum;
}

inline void Modify(int p, int x)
{
    for(int i = p + 1; i <= n; i ++)
    {
        if(a[i] != a[p]) continue ;
        pre[i] = pre[p], Extract(pos[i]);
        break ;
    }
    a[p] = x;
    for(int i = p + 1; i <= n; i ++)
    {
        if(a[i] != a[p]) continue ;
        pre[i] = p, Extract(pos[i]);
        break ;
    }
    bool flag = false;
    for(int i = p - 1; i >= 1; i --)
    {
        if(a[i] != a[p]) continue ;
        pre[p] = i, flag = true;
        break ;
    }
    if(!flag) pre[p] = 0;
    Extract(pos[p]);
    return ;
}

int main(int argc, char **argv)
{
    n = in(), q = in();
    B = ceil(sqrt(n) * log2(n));
    for(int i = 1; i <= n; i ++)
        a[i] = in();
    InitBlock();
    for(int i = 0; i < q; i ++)
    {
        char s[2];
        scanf("%s", s);
        int x = in(), y = in();
        if(s[0] == 'Q')
            printf("%d\n", Query(x, y));
        else if(a[x] != y)
            Modify(x, y);
    }
    return 0;
}
