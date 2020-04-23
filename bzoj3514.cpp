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

char buf[1 << 15], *S = buf, *T = buf;
#define GetChar() (S == T && (T = (S = buf) + fread(buf, 1, 1 << 15, stdin), S == T) ? 0 : *S ++)

inline int in()
{
    int k = 0, c = '\0';
    for(; c > '9' || c < '0';)
        c = GetChar();
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = GetChar();
    }
    return k;
}

const int N = 400001, K = 15;

int pre[N], son[N][2], val[N], key[N];
bool rev[N];

inline void Update(int p)
{
    int a = son[p][0], b = son[p][1];
    key[p] = val[p];
    if(a) key[p] = min(key[p], key[a]);
    if(b) key[p] = min(key[p], key[b]);
}

inline bool isRoot(int u) {return son[pre[u]][0] != u && son[pre[u]][1] != u;}
inline void PushDown(int u) {if(rev[u]) rev[son[u][0]] ^= 1, rev[son[u][1]] ^= 1, rev[u] = 0, swap(son[u][0], son[u][1]);}

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

inline void Access(int u) {for(int p = 0; u; u = pre[u]) Splay(u), son[u][1] = p, p = u;}
inline void MakeRoot(int u) {Access(u), Splay(u), rev[u] ^= 1;}
inline void Link(int u, int v) {MakeRoot(u), pre[u] = v;}
inline void Cut(int u, int v) {MakeRoot(u), Access(v), Splay(v), son[v][0] = pre[u] = 0;}
inline int QueryPath(int u, int v) {MakeRoot(u), Access(v), Splay(v); return key[v];}

inline bool Connected(int u, int v)
{
    MakeRoot(u), Access(v), Splay(v);
    while(son[v][0]) v = son[v][0];
    return u == v;
}

struct SegmenTree
{
    struct Node
    {
        int Count;
        Node *lson, *rson;
    } *root[N];

    inline Node *NewNode()
    {
        static Node pool[N * K], *T = pool;
        return T ++;
    }

    inline void Initialize()
    {
        root[0] = NewNode(), root[0] -> lson = root[0] -> rson = root[0];
    }

    Node *Insert(Node *p, int l, int r, int k)
    {
        Node *a = NewNode();
        a -> lson = p -> lson, a -> rson = p -> rson;
        a -> Count = p -> Count + 1;
        if(l == r) return a;
        int mid = (l + r) >> 1;
        if(k <= mid)
            a -> lson = Insert(p -> lson, l, mid, k);
        else
            a -> rson = Insert(p -> rson, mid + 1, r, k);
        return a;
    }

    int Query(Node *a, Node *b, int l, int r, int k)
    {
        if(l == r) return b -> Count - a -> Count;
        int mid = (l + r) >> 1;
        if(k <= mid) return Query(a -> lson, b -> lson, l, mid, k);
        return b -> lson -> Count - a -> lson -> Count + Query(a -> rson, b -> rson, mid + 1, r, k);
    }
} seg;

int n, m, Q, Type, U[N], V[N], W[N];

int main(int argc, char **argv)
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    n = in(), m = in(), Q = in(), Type = in();

    for(int i = 1; i <= n; i ++)
        val[i] = key[i] = m + 1;
    for(int i = 1; i <= m; i ++)
    {
        U[i] = in(), V[i] = in();
        val[i + n] = key[i + n] = i;
    }

    for(int i = 1; i <= m; i ++)
    {
        int u = U[i], v = V[i];
        if(u == v)
            W[i] = m + 1;
        else
        {
            if(Connected(u, v))
            {
                int w = W[i] = QueryPath(u, v);
                Cut(U[w], w + n);
                Cut(V[w], w + n);
            }
            Link(U[i], i + n);
            Link(V[i], i + n);
        }
    }

    seg.Initialize();
    for(int i = 1; i <= m; i ++)
        seg.root[i] = seg.Insert(seg.root[i - 1], 0, m, W[i]);

    int ans = 0;

    while(Q --)
    {
        int l = in(), r = in();
        if(Type) l ^= ans, r ^= ans;
        int x = seg.Query(seg.root[l - 1], seg.root[r], 0, m, l - 1);
        printf("%d\n", (ans = n - x));
    }

    return 0;
}
