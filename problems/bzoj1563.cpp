#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
typedef long double data;
const   int N = 1e5 + 5;
const   data INF = 1e18; 

data f[N], sum[N];
int T, n, L, p, len[N];

struct Item
{
    int l, r, p;

    Item(int l = 0, int r = 0, int p = 0): l(l), r(r), p(p)
    {
    }
} q[N];

inline data pow(data x)
{
    if(x < 0)
        x = -x;
    data r = 1;
    for(int i = 1; i <= p; i ++)
        r *= x;
    return r;
}

inline data F(int j, int i)
{
    return f[j] + pow(sum[i] - sum[j] + i - j - 1 - L);
}

// A Wrong Version:
inline int BinarySearch(Item a, int x)
{
    int l = a.l, r = a.r, y = a.p;
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(F(y, mid) <= F(x, mid))
            l = mid + 1;
        else
            r = mid;
    }
    if(F(y, l) <= F(x, l))
        l ++;
    return l;
}

inline void InterfaceDP()
{
    int head = 1, tail = 0;
    q[++tail] = Item(0, n, 0);
    for(int i = 1; i <= n; i ++)
    {
        if(head <= tail && q[head].r < i)
            head ++;
        f[i] = F(q[head].p, i);
        if(tail < head || F(i, n) <= F(q[tail].p, n))
        {
            while(head <= tail && F(i, q[tail].l) <= F(q[tail].p, q[tail].l))
                tail --;
            if(tail < head)
                q[++tail] = Item(i, n, i);
            else
            {
                int t = BinarySearch(q[tail], i);
                q[tail].r = t - 1;
                q[++tail] = Item(t, n, i);
            }
        }
    }
    return ;
}

int main()
{
    scanf("%d", &T);
    while(T --)
    {
        char buf[30];
        scanf("%d%d%d", &n, &L, &p);
        for(int i = 1; i <= n; i ++)
        {
            scanf("%s", buf);
            sum[i] = sum[i-1] + strlen(buf);
        }
        InterfaceDP();
        if(f[n] > INF)
            puts("Too hard to arrange");
        else
            printf("%lld\n", (long long) f[n]);
        puts("--------------------");
    }
    return 0;
}

