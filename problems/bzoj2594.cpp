#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
 
using   namespace   std;
typedef pair<int, int> Pair;
 
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
 
const int N = 1100001;
const int M = 1000001;
 
struct Edge
{
    int w, p; Pair e;
 
    bool operator < (const Edge &b) const
    {
        return e < b.e;
    }
} e[M], e0[M];
 
struct Query {int k, p, r; Pair e;} q[N];
 
bool cmpWeight(const Edge &a, const Edge &b)
{
    return a.w < b.w;
}
 
bool deleted[M];
int n, m, Q;
 
inline int BinarySearch(Pair k)
{
    int l = 0, r = m - 1;
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(e[mid].e == k) return mid;
        e[mid].e < k ? l = mid + 1 : r = mid;
    }
    return l;
}
 
int pre[N], son[N][2], val[N], key[N];
bool rev[N];
 
inline void Update(int p)
{
    int a = son[p][0], b = son[p][1];
    key[p] = p;
    if(val[key[a]] > val[key[p]]) key[p] = key[a];
    if(val[key[b]] > val[key[p]]) key[p] = key[b];
}
 
inline bool isRoot(int p) {return son[pre[p]][0] != p && son[pre[p]][1] != p;}
inline void PushDown(int p) {if(rev[p]) rev[p] = 0, rev[son[p][0]] ^= 1, rev[son[p][1]] ^= 1, swap(son[p][0], son[p][1]);}

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
inline int Query(int u, int v) {MakeRoot(u), Access(v), Splay(v); return key[v];}
 
int ufs[N];
 
int Find(int u)
{
    if(u != ufs[u])
        ufs[u] = Find(ufs[u]);
    return ufs[u];
}
 
inline void Unite(int u, int v) {ufs[Find(v)] = Find(u);}
 
int main(int argc, char **argv)
{
    n = in(), m = in(), Q = in();
    for(int i = 0; i < m; i ++)
    {
        int u = in(), v = in();
        if(u > v) swap(u, v);
        e[i].e = Pair(u, v), e[i].w = in();
    }
    sort(e, e + m);
    for(int i = 0; i < m; i ++)
        e[i].p = i;
    for(int i = 0; i < Q; i ++)
    {
        int k = in(), u = in(), v = in();
        if(u > v) swap(u, v);
        q[i].e = Pair(u, v), q[i].k = k;
        if(k == 2)
        {
            q[i].p = BinarySearch(q[i].e);
            deleted[q[i].p] = true;
        }
    }
    memcpy(e0, e, sizeof(e));
    for(int i = n + 1; i <= n + m; i ++)
        val[i] = e[i - n - 1].w;
    sort(e, e + m, cmpWeight);
    for(int i = 1; i <= n + m; i ++)
        ufs[i] = i;
    for(int i = 0, cnt = 0; i < m; i ++)
    {
        if(deleted[e[i].p]) continue ;
        int u = e[i].e.first, v = e[i].e.second;
        if(Find(u) == Find(v)) continue ;
        Link(u, e[i].p + n + 1), Link(v, e[i].p + n + 1), Unite(u, v);
        if(++ cnt == n - 1) break ;
    }
    for(int i = Q - 1; i >= 0; i --)
    {
        if(q[i].k == 1)
            q[i].r = Query(q[i].e.first, q[i].e.second);
        else
        {
            int p = q[i].p, u = q[i].e.first, v = q[i].e.second, x = Query(u, v);
            if(val[x] > e0[p].w)
            {
                Cut(e0[x - n - 1].e.first, x), Cut(e0[x - n - 1].e.second, x);
                Link(u, p + n + 1), Link(v, p + n + 1);
            }
        }
    }
    for(int i = 0; i < Q; i ++) if(q[i].k == 1)
        printf("%d\n", val[q[i].r]);
    return 0;
}
