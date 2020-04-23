#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <queue>

#define     set(p, k)       memset(p, k, sizeof(p))
#define     cpy(p, q)       memcpy(p, q, sizeof(q))
#define     rep(i, n)       for(int i = 1; i <= n; i ++)

using   namespace   std;
const   int N = 1e4 + 5;
const   int M = 3e5 + 5;
const   int INF = 0x3f3f3f3f;
const   int K = 101;

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

int h[K][K], a[K][K], b[K][K], w[K][K], head[N];
int s, t, n, m, d[N], cur[N], gap[N], pre[N];

struct Edge {int v, cap, next;} e[M];

inline void AddEdge(int u, int v, int w)
{
    static int sig = 0;
    e[++sig].v = v, e[sig].cap = w;
    e[sig].next = head[u], head[u] = sig;
}

inline int F( int i ) {return ((i - 1) ^ 1) + 1;}
inline void Emit(int u, int v, int w) {AddEdge(u, v, w), AddEdge(v, u, 0);}

inline void BFS()
{
    queue< int > q;
    set(d, -1), set(gap, 0);
    q.push(t), d[t] = 0;
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        gap[d[u]] ++;
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(d[v] == -1 && e[F(i)].cap > 0)
            {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    return ;
}

inline int Augment()
{
    int sur = INF, u = t;
    while(u != s)
    {
        sur = min(sur, e[pre[u]].cap);
        u = e[F(pre[u])].v;
    }
    u = t;
    while( u != s )
    {
        e[pre[u]].cap -= sur;
        e[F(pre[u])].cap += sur;
        u = e[F(pre[u])].v;
    }
    return sur;
}

inline bool Advance(int &u)
{
    bool flag = false;
    for(int &i = cur[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(e[i].cap > 0 && d[u] == d[v] + 1)
        {
            u = v, pre[v] = i, flag = true;
            break ;
        }
    }
    return flag;
}

inline void Retreat(int &u)
{
    int k = t - 1;
    for(int i = head[u]; i; i = e[i].next)
        if(e[i].cap > 0)
            k = min(k, d[e[i].v]);
    d[u] = k + 1;
    gap[d[u]] ++;
    cur[u] = head[u];
    if(u != s)
        u = e[F(pre[u])].v;
    return ;
}

int MaxFlow()
{
    BFS(), cpy(cur, head);
    int u = s, flow = 0;
    while(d[s] < t)
    {
        if(u == t)
        {
            flow += Augment();
            u = s;
        }
        if(!Advance( u ))
        {
            if(-- gap[d[u]] == 0)
                break ;
            Retreat(u);
        }
    }
    return flow;
}

int main()
{
    int n = in(), m = in();
    rep(i, n) rep(j, m)
        h[i][j] = (i - 1) * m + j;
    s = n * m + 1, t = s + 1;
    int sum = 0;
    rep(i, n) rep(j, m)
        a[i][j] = in() << 1, sum += a[i][j];
    rep(i, n) rep(j, m)
        b[i][j] = in() << 1, sum += b[i][j];
    sum >>= 1;
    rep(i, n - 1) rep(j, m)
        w[i][j] = in(), a[i][j] += w[i][j], a[i+1][j] += w[i][j];
    rep(i, n - 1) rep(j, m)
    {
        int x = in();
        sum += w[i][j] + x, b[i][j] += x, b[i+1][j] += x;
        AddEdge(h[i][j], h[i+1][j], w[i][j] + x);
        AddEdge(h[i+1][j], h[i][j], w[i][j] + x);
    }
    rep(i, n) rep(j, m - 1)
        w[i][j] = in(), a[i][j] += w[i][j], a[i][j+1] += w[i][j];
    rep(i, n) rep(j, m - 1)
    {
        int x = in();
        sum += w[i][j] + x, b[i][j] += x, b[i][j+1] += x;
        AddEdge(h[i][j], h[i][j+1], w[i][j] + x);
        AddEdge(h[i][j+1], h[i][j], w[i][j] + x);
    }
    rep(i, n) rep(j, m)
        Emit(s, h[i][j], a[i][j]), Emit(h[i][j], t, b[i][j]);
    int flow = MaxFlow();
    printf("%d\n", sum - flow / 2);
    return 0;
}
