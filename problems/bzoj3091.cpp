#include	<cstdio>
#include	<iostream>

using namespace	std;
typedef unsigned long long data;

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

const int N = 50001;

bool rev[N];
int pre[N], son[N][2];
data sum[N], E[N], val[N], mark[N], lSum[N], rSum[N], size[N];

inline bool isRoot(int u)
{
    return son[pre[u]][0] != u && son[pre[u]][1] != u;
}

inline void Update(int u)
{
    int a = son[u][0], b = son[u][1];
    size[u] = size[a] + size[b] + 1;
    sum[u] = sum[a] + sum[b] + val[u];
    lSum[u] = lSum[a] + (size[a] + 1) * (val[u] + sum[b]) + lSum[b];
    rSum[u] = rSum[b] + (size[b] + 1) * (val[u] + sum[a]) + rSum[a];
    E[u] = E[a] + (size[b] + 1) * lSum[a] + E[b] + (size[a] + 1) * rSum[b];
    E[u] += val[u] * (size[a] + 1) * (size[b] + 1);
    return ;
}

inline void Modify(int u, data k)
{
    if(u == 0) return ;
    data s = size[u];
    val[u] += k, sum[u] += k * s, E[u] += s * (s + 1) * (s + 2) / 6 * k;
    lSum[u] += ((s + 1) * s >> 1) * k, rSum[u] += ((s + 1) * s >> 1) * k;
    mark[u] += k;
    return ;
}

inline void Reverse(int u)
{
    swap(son[u][0], son[u][1]), swap(lSum[u], rSum[u]);
    rev[u] ^= 1;
    return ;
}

inline void PushDown(int u)
{
    if(rev[u])
    {
        if(son[u][0]) Reverse(son[u][0]);
        if(son[u][1]) Reverse(son[u][1]);
        rev[u] = 0;
    }
    if(mark[u])
    {
        if(son[u][0]) Modify(son[u][0], mark[u]);
        if(son[u][1]) Modify(son[u][1], mark[u]);
        mark[u] = 0;
    }
    return ;
}

inline void Rotate(int x)
{
    int p = pre[x], z = pre[p], g = x == son[p][1], y = son[x][g ^ 1];
    if(p == son[z][0]) son[z][0] = x; else if(p == son[z][1]) son[z][1] = x;
    pre[x] = z, son[p][g] = y, pre[y] = p, son[x][g ^ 1] = p, pre[p] = x;
    return (void) (Update(p));
}

inline void Splay(int p)
{
    PushDown(p);
    while(!isRoot(p))
    {
        int x = pre[p], y = pre[x];
        PushDown(y), PushDown(x), PushDown(p);
        if(isRoot(x))
            Rotate(p);
        else if((p == son[x][0]) ^ (x == son[y][0]))
            Rotate(p), Rotate(p);
        else
            Rotate(x), Rotate(p);
    }
    return (void) (Update(p));
}

inline void Access(int p)
{
    int last = 0;
    while(p != 0)
    {
        Splay(p), son[p][1] = last;
        last = p, p = pre[p];
    }
    return ;
}

inline void MakeRoot(int u)
{
    Access(u), Splay(u), Reverse(u);
    return ;
}

inline int Find(int u)
{
    Access(u), Splay(u);
    while(son[u][0]) u = son[u][0];
    return u;
}

inline bool Connected(int u, int v)
{
    return Find(u) == Find(v);
}

inline void Link(int u, int v)
{
    if(Connected(u, v)) return ;
    MakeRoot(u), pre[u] = v;
    return ;
}

inline void Cut(int u, int v)
{
    MakeRoot(u), Access(v), Splay(v);
    // If son[u][1] exists, v and one u's right son have edge!
    // Cut() doesn't need Update()!
    if(son[v][0] != u || son[u][1]) return ;
    pre[u] = son[v][0] = 0;
    return ;
}


data gcd(data a, data b)
{
    return b ? gcd(b, a % b) : a;
}

struct Edge {int v, next;} e[N + N];

int head[N];

inline void AddEdge(int u, int v)
{
    static int i = 0;
    e[++ i].v = v, e[i].next = head[u], head[u] = i;
    return ;
}

void DFS(int u, int p)
{
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == p) continue ;
        pre[v] = u, DFS(v, u);
    }
    return ;
}

int main(int argc, char **argv)
{
    int n = in(), Q = in();
    for(int i = 1; i <= n; i ++)
    {
        val[i] = in(), size[i] = 1;
        sum[i] = E[i] = lSum[i] = rSum[i] = val[i];
    }
    for(int i = 1; i < n; i ++)
    {
        int u = in(), v = in();
        AddEdge(u, v), AddEdge(v, u);
    }
    DFS(1, 0);
    while(Q --)
    {
        int c = in(), u = in(), v = in();
        if(c == 1) Cut(u, v);
        else if(c == 2) Link(u, v);
        else if(c == 3)
        {
            data w = in();
            if(Connected(u, v))
            {
                MakeRoot(u), Access(v), Splay(v);
                Modify(v, w);
            }
        }
        else if(c == 4)
        {
            if(!Connected(u, v))
                puts("-1");
            else
            {
                MakeRoot(u), Access(v), Splay(v);
                data A = E[v], B = size[v] * (size[v] + 1) >> 1, d = gcd(A, B);
                // printf("%I64u/%I64u\n", A / d, B / d);
                printf("%llu/%llu\n", A / d, B / d);
            }
        }
    }
    return 0;
}
