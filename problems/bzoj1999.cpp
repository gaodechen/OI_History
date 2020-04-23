#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 5e5 + 5;
const   int INF = 0x3f3f3f3f;

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

inline int max(int a, int b)
{
    return a > b ? a : b;
}

inline int min(int a, int b)
{
    return a < b ? a : b;
}

struct Edge
{
    int v, w, mark, next;
} e[N+N];

int sig, n, S, p;
int head[N], w[N], f[N], seq[N], sum[N];

inline void AddEdge(int u, int v, int w)
{
    e[++sig].v = v, e[sig].w = w;
    e[sig].next = head[u], head[u] = sig;
}

inline int BFS(int s, bool c)
{
    int front = 1, tail = 0;
    int q[N], pre[N], d[N] = {0};
    q[++tail] = s;
    while(front <= tail)
    {
        int u = q[front++];
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if(!d[v] && v != s)
            {
                d[v] = d[u] + e[i].w;
                if(c) pre[v] = u, w[v] = e[i].w;
                q[++tail] = v;
            }
        }
    }
    int k = 0, v;
    for(int i = 1; i <= n; i ++)
        if(d[i] > k)
            k = d[i], v = i;
    if(c)
    {
        int u = v;
        while(u != s)
            seq[++p] = u, u = pre[u];
        seq[++p] = s;
        for(int i = 1; i <= p; i ++)
            sum[i] = sum[i-1] + w[seq[i-1]];
    }
    return v;
}

bool vis[N];

inline void BFS_()
{
    int q[N], d[N] = {0};
    for(int i = 1; i <= p; i ++)
        vis[seq[i]] = 1;
    for(int k = 1; k <= p; k ++)
    {
        int front = 1, tail = 0;
        q[++tail] = seq[k];
        while(front <= tail)
        {
            int u = q[front++];
            for(int i = head[u]; i; i = e[i].next)
            {
                int v = e[i].v;
                if(!vis[v])
                {
                    d[v] = d[u] + e[i].w;
                    f[k] = max(f[k], d[v]);
                    q[++tail] = v, vis[v] = 1;
                }
            }
        }
    }
    return ;
}

inline int Interface()
{
    int q[N], r = INF, s = 0;
    int L = 1, R = 0, head = 1, tail = 0;
    for(int i = 1; i <= p; i ++)
    {
        while(head <= tail && f[q[tail]] <= f[i])
            tail --;
        q[++tail] = i, s += w[seq[R]], R ++;
        while(L <= R && s > S)
            s-= w[seq[L++]];
        r = min(r, max(max(sum[L], sum[p] - sum[R]), f[q[head]]));
    }
    return r;
}

int main()
{
    n = in(), S = in();
    for(int i = 1; i < n; i ++)
    {
        int u = in(), v = in(), w = in();
        AddEdge(u, v, w), AddEdge(v, u, w);
    }
    BFS(BFS(1, 0), 1), BFS_();
    int ans = Interface();
    printf("%d\n", ans);
    return 0;
}
