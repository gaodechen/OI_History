#include    <cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <set>
#include    <map>
#include    <cmath>
#include    <queue>
#include    <vector>

#define     foreach(u)     for(int i = head[u]; i; i = e[i].next)

using	namespace	std;
typedef pair<int, int> Pair;
typedef long long   data;

inline int in()
{
    int k = 0, c = '\0', f = 1;
    for(; c > '9' || c < '0';)
        if((c = getchar()) == '-')
            f = 0;
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return f ? k : -k;
}

const int N = 1e5 + 5;

int sig, head[N], degree[N];

struct Edge {int v, next;} e[N];

struct Item {int type, u, v;} q[N];

inline void AddEdge(int u, int v)
{
    e[++ sig].v = v, e[sig].next = head[u], head[u] = sig;
}

int pre[N], dep[N], son[N], size[N];

void DFS1(int u, int p)
{
    dep[u] = dep[p] + 1, size[u] = 1, pre[u] = p;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v != p)
        {
            DFS1(v, u);
            size[u] += size[v];
            if(size[v] > size[son[u]])
                son[u] = v;
        }
    }
    return ;
}

int tik, pos[N], top[N], ufs[N];

void DFS2(int u, int t)
{
    pos[u] = ++ tik, top[u] = t;
    if(son[u]) DFS2(son[u], t);
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v != pre[u] && v != son[u])
            DFS2(v, v);
    }
    return ;
}

inline int Find(int u)
{
    if(u != ufs[u])
        ufs[u] = Find(ufs[u]);
    return ufs[u];
}

bool ans[N], vis[N];
vector<int> Head[N], Tail[N];
vector<Pair> query[N];

inline void Modify(int u, int v, int w)
{
    int a = top[u], b = top[v];
    while(a != b)
    {
        Head[pos[a]].push_back(w);
        Tail[pos[u]].push_back(w);
        u = pre[a], a = top[u];
    }
    Head[pos[v]].push_back(w);
    Tail[pos[u]].push_back(w);
    return ;
}

int main(int argc, char **argv)
{
    int n = in(), Q = in();
    for(int i = 1; i <= n; i ++)
        ufs[i] = i;
    for(int i = 0; i < Q; i ++)
    {
        q[i].type = in();
        if(q[i].type == 2)
            q[i].u = in();
        else
        {
            q[i].u = in(), q[i].v = in();
            if(q[i].type == 1)
            {
                degree[q[i].u] ++;
                AddEdge(q[i].v, q[i].u);
            }
        }
    }
    for(int i = 1; i <= n; i ++)
        if(!degree[i]) DFS1(i, 0), DFS2(i, i);
    int Color = 0, number = 0;
    for(int i = 0; i < Q; i ++)
    {
        if(q[i].type == 1)
            ufs[Find(q[i].u)] = Find(q[i].v);
        else if(q[i].type == 2)
            Modify(q[i].u, Find(q[i].u), ++ Color);
        else
            query[pos[q[i].u]].push_back(Pair(q[i].v, number ++));
    }
    for(int i = 1; i <= n; i ++)
    {
        for(int j = 0; j < (int) Head[i].size(); j ++)
            vis[Head[i][j]] = 1;
        for(int j = 0; j < (int) query[i].size(); j ++)
            ans[query[i][j].second] = vis[query[i][j].first];
        for(int j = 0; j < (int) Tail[i].size(); j ++)
            vis[Tail[i][j]] = 0;
    }
    for(int i = 0; i < number; i ++)
        puts(ans[i] ? "YES" : "NO");
    return 0;
}
