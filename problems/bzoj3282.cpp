#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <set>
#include    <map>
#include    <cmath>
#include    <queue>
#include    <vector>


using namespace	std;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> Pair;
typedef long long data;

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

const int N = 300001;

bool rev[N];
int son[N][2], pre[N], val[N], sum[N];

inline bool isRoot(int u)
{
    return son[pre[u]][0] != u && son[pre[u]][1] != u;
}

inline void Update(int u)
{
    sum[u] = sum[son[u][0]] ^ sum[son[u][1]] ^ val[u];
    return ;
}

inline void PushDown(int u)
{
    if(rev[u] == 0) return ;
    rev[son[u][0]] ^= 1, rev[son[u][1]] ^= 1, rev[u] = 0;
    swap(son[u][0], son[u][1]);
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

inline void Access(int u)
{
    for(int p = 0; u; u = pre[u])
        Splay(u), son[u][1] = p, Update(u), p = u;
    return ;
}

inline void MakeRoot(int u)
{
    Access(u), Splay(u), rev[u] ^= 1;
    return ;
}

inline void Link(int u, int v)
{
    MakeRoot(u), pre[u] = v;
    return ;
}

inline void Cut(int u, int v)
{
    MakeRoot(u), Access(v), Splay(v);
    pre[u] = son[v][0] = 0;
    return ;
}

inline int Find(int u)
{
    Access(u), Splay(u);
    while(son[u][0]) u = son[u][0];
    return u;
}

int main(int argc, char **argv)
{
    int n = in(), Q = in();
    for(int i = 1; i <= n; i ++)
        val[i] = in();
    while(Q --)
    {
        int c = in(), x = in(), y = in();
        if(c == 0)
        {
            MakeRoot(x), Access(y), Splay(y);
            printf("%d\n", sum[y]);
        }
        else if(c == 1 && Find(x) != Find(y))
            Link(x, y);
        else if(c == 2 && Find(x) == Find(y))
            Cut(x, y);
        else if(c == 3)
            Access(x), Splay(x), val[x] = y, Update(x);
    }
    return 0;
}
