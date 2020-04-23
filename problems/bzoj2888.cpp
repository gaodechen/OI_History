#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using namespace	std;
const int INF = 0x3f3f3f3f;

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

const int N = 40001;

int ans;

struct Edge {int v, next;} e[N + N];

int head[N];

inline void AddEdge(int u, int v)
{
    static int i = 0;
    e[++ i].v = v, e[i].next = head[u], head[u] = i;
    return ;
}

int pre[N], son[N][2], size[N];
int A[N], D[N], sum[N], sizeTree[N];

inline bool isRoot(int u)
{
    return u != son[pre[u]][0] && u != son[pre[u]][1];
}

inline void Update(int u)
{
    size[u] = size[son[u][0]] + size[son[u][1]] + 1;
    return ;
}

inline void Rotate(int p)
{
    int x = pre[p], y = pre[x];
    int g = p == son[x][1], t = son[p][g ^ 1];
    if(x == son[y][0]) son[y][0] = p;
    else if(x == son[y][1]) son[y][1] = p;
    pre[p] = y, son[x][g] = t, pre[t] = x;
    son[p][g ^ 1] = x, pre[x] = p;
    return (void) (Update(x));
}

int tagSize[N], tagA[N], tagD[N];

inline void Add1(int u, int x)
{
    if(u == 0) return ;
    sizeTree[u] += x, tagSize[u] += x;
    return ;
}

inline void Add2(int u, int a, int d)
{
    if(u == 0) return ;
    sum[u] += a + size[son[u][1]] * d;
    tagA[u] += a, tagD[u] += d;
    return ;
}

inline void PushDown(int u)
{
    if(tagSize[u])
    {
        Add1(son[u][0], tagSize[u]);
        Add1(son[u][1], tagSize[u]);
        tagSize[u] = 0;
    }
    if(tagD[u])
    {
        int t = tagA[u] + (size[son[u][1]] + 1) * tagD[u];
        Add2(son[u][0], t, tagD[u]);
        Add2(son[u][1], tagA[u], tagD[u]);
        tagA[u] = tagD[u] = 0;
    }
    return ;
}

inline void Splay(int u)
{
    PushDown(u);
    while(!isRoot(u))
    {
        int x = pre[u], y = pre[x];
        PushDown(y), PushDown(x), PushDown(u);
        if(isRoot(x))
            Rotate(u);
        else if((son[x][0] == u) ^ (son[y][0] == x))
            Rotate(u), Rotate(u);
        else
            Rotate(x), Rotate(u);
    }
    return (void) (Update(u));
}

inline void Access(int u)
{
    for(int p = 0; u; u = pre[u])
        Splay(u), son[u][1] = p, p = u;
    return ;
}

inline int Root(int u)
{
    Access(u), Splay(u);
    while(son[u][0])
        u = son[u][0];
    return u;
}

inline void AddLeaf(int u, int p)
{
    pre[u] = p, size[u] = 1, son[u][0] = son[u][1] = 0;
    sizeTree[u] = sum[u] = tagSize[u] = tagA[u] = tagD[u] = 0;

    p = Root(p), Access(u), Splay(p);
    Add1(p, 1), Add2(p, 0, 1);

    for(u = son[p][1]; son[u][0]; u = son[u][0]);
    Splay(u);

    int x = sizeTree[u], y = sizeTree[p];
    if(x * 2 > y)
    {
        sizeTree[u] = y, sizeTree[p] -= x;
        sum[p] -= sum[u] + x, sum[u] += sum[p] + y - x;
        Access(u), Splay(p), swap(son[p][0], son[p][1]);
    }

    return ;
}

void DFS(int u, int p)
{
    AddLeaf(u, p);
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == p) continue ;
        DFS(v, u);
    }
    return ;
}

inline void Link(int u, int v)
{
    int x = Root(u), y = Root(v);
    ans -= sum[x] + sum[y];
    if(sizeTree[x] < sizeTree[y]) swap(u, v);
    DFS(v, u), ans += sum[Root(u)];
    AddEdge(u, v), AddEdge(v, u);
    return ;
}

int main(int argc, char **argv)
{
    int n = in(), Q = in();
    for(int i = 1; i <= n; i ++)
        size[i] = sizeTree[i] = 1;
    while(Q --)
    {
        char buf[2];
        scanf("%s", buf);
        if(buf[0] == 'A')
            Link(in(), in());
        else
            printf("%d\n", ans);
    }
    return 0;
}

