#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
typedef long long   data;
const   int N = 1e5 + 5;

inline int in()
{
    int k = 0, c = '\0', f = 1;
    for(; c > '9' || c < '0';)
    {
        c = getchar();
        if(c == '-')
            f = 0;
    }
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return f ? k : -k;
}

int n, m, a[N];

struct BIT
{
    data node[N];

    BIT()
    {
        memset(node, 0, sizeof(node));
    }

    inline int lowbit(int p)
    {
        return p & (-p);
    }

    inline data Query(int p)
    {
        data sum = 0;
        for(; p; p -= lowbit(p))
            sum += node[p];
        return sum;
    }

    inline void Modify(int p, data x)
    {
        for(; p <= n; p += lowbit(p))
            node[p] += x;
        return ;
    }
} bit1, bit2;

int main()
{
    freopen("in", "r", stdin);
    n = in(), m = in();
    for(int i = 1; i <= n; i ++)
    {
        a[i] = in();
        bit1.Modify(i, (data) (n - i + 1) * a[i]);
        bit2.Modify(i, a[i]);
    }
    while(m --)
    {
        char buf[6];
        scanf("%s", buf);
        if(buf[0] == 'Q')
        {
            int p = in();
            printf("%lld\n", bit1.Query(p) - bit2.Query(p) * (n - p));
        }
        else
        {
            int p = in(), x = in();
            bit2.Modify(p, x - a[p]);
            bit1.Modify(p, (data) (n - p + 1) * (x - a[p]));
            a[p] = x;
        }
    }
    return 0;
}
