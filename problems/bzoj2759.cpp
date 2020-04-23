#include	<cstdio>
#include	<cstring>
#include	<iostream>

using namespace	std;
typedef long long data;
const int MOD = 10007;
const int N = 30001;

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

int inv[MOD];

inline int M(int x)
{
    if(x >= MOD) return x % MOD;
    return x;
}

struct Item
{
    int k, b;

    Item(int k = 1, int b = 0): k(k), b(b) {}

    Item operator + (const Item &r) const
    {
        return Item(M(k * r.k), M(r.k * b + r.b));
    }
};

int pre[N], son[N][2], preS[N];
Item S[N], W[N];

inline bool isRoot(int u)
{
    return son[pre[u]][0] != u && son[pre[u]][1] != u;
}

inline void Update(int u)
{
    S[u] = S[son[u][0]] + W[u] + S[son[u][1]];
    return ;
}

inline void Rotate(int u)
{
    int x = pre[u], y = pre[x];
    int g = u == son[x][1], z = son[u][g ^ 1];
    if(x == son[y][0]) son[y][0] = u;
    else if(x == son[y][1]) son[y][1] = u;
    pre[u] = y, son[x][g] = z, pre[z] = x;
    son[u][g ^ 1] = x, pre[x] = u;
    return (void) (Update(x));
}

inline void Splay(int p)
{
    while(!isRoot(p))
    {
        int x = pre[p], y = pre[x];
        if(isRoot(x))
            Rotate(p);
        else if((p == son[x][0]) ^ (x == son[y][0]))
            Rotate(p), Rotate(p);
        else
            Rotate(x), Rotate(p);
    }
    return (void) (Update(p));
}

inline int Access(int u)
{
    int p = 0;
    while(u != 0)
    {
        Splay(u), son[u][1] = p;
        Update(u), p = u, u = pre[u];
    }
    return p;
}

inline int Root(int u)
{
    while(son[u][0])
        u = son[u][0];
    return u;
}

inline int Prev(int u)
{
    Splay(u);
    u = son[u][0];
    while(son[u][1])
        u = son[u][1];
    return u;
}

inline int Query(int u)
{
    Access(u);
    Splay(u);
    Item c = S[u];
    int root = Root(u), rootS = preS[root];
    Access(rootS), Splay(rootS);
    Item t = S[rootS];
    if(t.k == 1 && c.k)
        return t.b ? -1 : -2;
    // When x[i] = 0 * x[p] + b (if(c.k != 0) above)
    // There will be a solution
    int x = M(inv[M(1 - t.k + MOD)] * t.b);
    return M(c.k * x + c.b);
}

inline void Modify(int u, int k, int p, int b)
{
    int root = Root(Access(u));
    if(u == root)
        W[root].k = k, W[root].b = b, Update(root);
    else
    {
        // Once cut root -> preS[root], the nodes whose depth <= preS[root]
        // are on cycle, so we judge if u is on it by LCA(preS[root], u)
        int LCA = Access(preS[root]);
        Access(u);
        int v = Prev(u);
        Splay(v), son[v][1] = 0, Update(v);
        Splay(u), pre[u] = 0, W[u].k = k, W[u].b = b, Update(u);
        if(LCA == u) Splay(root), pre[root] = preS[root], preS[root] = 0;
    }
    if(Root(Access(p)) == u)
        pre[u] = 0, preS[u] = p;
    else
        pre[u] = p, preS[u] = 0;
    return ;
}

int ufs[N];

int Find(int u)
{
    if(u != ufs[u])
        ufs[u] = Find(ufs[u]);
    return ufs[u];
}

int main(int argc, char **argv)
{
    inv[1] = 1;
    for(int i = 2; i < MOD; i ++)
        inv[i] = M((MOD - MOD / i) * inv[MOD % i]);
    int n = in();
    for(int i = 1; i <= n; i ++)
        ufs[i] = i;
    for(int i = 1; i <= n; i ++)
    {
        int k = in(), p = in(), b = in();
        W[i] = Item(k, b);
        int u = Find(i), v = Find(p);
        if(u == v)
            preS[i] = p;
        else
            ufs[v] = u, pre[i] = p;
    }
    int Q = in();
    char cmd[10];
    while(Q --)
    {
        scanf("%s", cmd);
        if(cmd[0] == 'A')
            printf("%d\n", Query(in()));
        else
        {
            int x = in(), k = in(), p = in(), b = in();
            Modify(x, k, p, b);
        }
    }
    return 0;
}
