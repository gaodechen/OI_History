#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 2e4 + 5;
const   int M = 1e5 + 5;
const   int S = 1e7 + 5;

char buf[S], *s;

inline int in()
{
    int k = 0;
    while( *s > '9' || *s < '0' )
        s ++;
    while( *s <= '9' && *s >= '0' )
    {
        k = k * 10 + *s - '0';
        s ++;
    }
    return k;
}

struct Edge
{
    int u, v;
} e[M];

bool mark[M];
int n, m, k, pre[N];

int Find( int u )
{
    if( u != pre[u] )
        pre[u] = Find( pre[u] );
    return pre[u];
}

inline void Union(int u, int v)
{
    return (void) (pre[pre[v]] = pre[u]);
}

int main(int argc, char **argv)
{
    int len = fread(buf, 1, S, stdin);
    buf[len] = '\0', s = buf;
    n = in(), m = in(), k = in();
    int l = 0, r = m + 1;
    for(int i = 1; i <= m; i ++)
    {
        int u, v, w;
        u = in(), v = in(), w = in();
        if(w)
            e[++l].u = u, e[l].v = v;
        else
            e[--r].u = u, e[r].v = v;
    }
    for(int i = 1; i <= n; i ++)
        pre[i] = i;
    int cnt = 0, cnt_ = 0;
    for(int i = 1; i <= m; i ++)
    {
        int u = e[i].u, v = e[i].v;
        if(Find(u) != Find(v))
        {
            cnt_ ++;
            if(i >= r)
                cnt ++, mark[i] = 1;;
            Union(u, v);
        }
        if(cnt_ >= n - 1)
            break ;
    }
    if(cnt < k) puts("no solution");
    for(int i = 1; i <= n; i ++)
        pre[i] = i;
    for(int i = r; i <= m; i ++) if(mark[i])
            Union(e[i].u, e[i].v);
    for( int i = r; i <= m; i ++ )
    {
        int u = e[i].u, v = e[i].v;
        if(!mark[i] && cnt < k && Find(u) != Find(v))
        {
            cnt ++, mark[i] = 1;
            Union(u, v);
        }
    }
    if(cnt < k) puts("no solution");
    cnt_ = cnt;
    for(int i = 1; i <= l; i ++)
    {
        int u = e[i].u, v = e[i].v;
        if(Find(u) != Find(v))
        {
            cnt_ ++, mark[i] = 1;
            Union(u, v);
        }
        if(cnt_ == n - 1)
            break ;
    }
    for(int i = 1; i <= m; i ++) if(mark[i])
        printf("%d %d %d\n", e[i].u, e[i].v, i <= l);
    return 0;
}
