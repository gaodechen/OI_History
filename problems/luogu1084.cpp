#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <queue>
#include    <vector>

using   namespace   std;
typedef long long   data;
const   int N = 50005, K = 16;

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

int head[N];

struct Edge {int v, w, next;} e[N + N];

inline void AddEdge(int u, int v, int w)
{
    static int i = 0;
    e[++ i].v = v, e[i].w =  w;
    e[i].next = head[u], head[u] = i;
}

struct Item
{
    int v, d, f;

    bool operator < (const Item &b) const {
        return d < b.d;
    }
};

bool army[N], cov[N];
int n, m, pos[N], d[N][K], pre[N][K], sub[N];

void DFS(int u, int p, int w, int f)
{
    pre[u][0] = p, d[u][0] = w, sub[u] = f;
    for(int i = 1; i < K; i ++)
    {
        pre[u][i] = pre[pre[u][i - 1]][i - 1];
        d[u][i] = d[pre[u][i - 1]][i - 1] + d[u][i - 1];
    }
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == p) continue ;
        DFS(v, u, e[i].w, u == 1 ? v : f);
    }
    return ;
}

bool DFS2(int u, bool cov)
{
    int size = 0;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == pre[u][0]) continue ;
        if(!DFS2(v, cov | army[u])) return false;
        size ++;
    }
    if(!size) return cov;
    return true;
}

vector<Item> Node, Army;

inline bool Judge(data time_)
{
    Node.clear(), Army.clear();
    memset(army, 0, sizeof(army));
    memset(cov, 0, sizeof(cov));
    for(int i = 0; i < m; i ++)
    {
        int u = pos[i], time = time_;
        for(int j = K - 1; j >= 0; j --)
            if(d[u][j] <= time && pre[u][j])
                time -= d[u][j], u = pre[u][j];
        if(u == 1 && time >= 0)
            Army.push_back((Item) {1, time, pos[i]});
        army[u] = 1;
    }
    for(int i = head[1]; i; i = e[i].next) {
        if(!DFS2(e[i].v, army[e[i].v]))
            Node.push_back((Item) {e[i].v, e[i].w, 0});
        else
            cov[e[i].v] = 1;
    }
    sort(Army.begin(), Army.end());
    sort(Node.begin(), Node.end());
    int aSize = (int) Army.size(), bSize = (int) Node.size();
    for(int i = 0, j = 0; i < aSize && j < bSize;)
    {
        if(cov[sub[Node[j].v]]) {
            j ++; continue ;
        }
        if(!cov[sub[Army[i].f]])
            cov[sub[Army[i].f]] = 1, i ++;
        else if(Army[i].d >= Node[j].d)
            cov[sub[Node[j].v]] = 1, i ++, j ++;
        else i ++;
    }
    bool r = true;
    for(int i = 0; i < bSize; i ++)
        if(!cov[sub[Node[i].v]]) r = false;
    return r;
}

int main(int argc, char **argv)
{
    n = in();
    int tmp = 0;
    for(int i = 1; i < n; i ++)
    {
        int u = in(), v = in(), w = in();
        AddEdge(u, v, w), AddEdge(v, u, w);
        tmp = max(w, tmp);
    }
    m = in();
    for(int i = 0; i < m; i ++)
        pos[i] = in();
    DFS(1, 0, 0, 0);
    data l = 0, r = m * tmp + 1;
    while(l < r)
    {
        data mid = (l + r) >> 1LL;
        if(Judge(mid))
            r = mid;
        else
            l = mid + 1;
    }
    if(l <= m * tmp)
        printf("%lld\n", l);
    else
        puts("-1");
    return 0;
}

