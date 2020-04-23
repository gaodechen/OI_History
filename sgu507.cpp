#include    <cstdio>
#include    <iostream>
#include    <algorithm>
#include    <set>
#include    <vector>

using   namespace   std;
const   int N = 5e4 + 5;
const   int INF = 2147483647;

int n, m, w[N];
set<int> val[N];
vector<int> e[N];
set<int>::iterator T, pre, suf;

inline int Merge(set<int> &x, set<int> &y)
{
    int r = INF;
    if(x.size() < y.size())
        swap(x, y);
    for(T = y.begin(); T != y.end(); T ++)
    {
        pre = suf = x.lower_bound(*T);
        if(pre != x.begin())
            pre --;
        if(pre != x.end())
            r = min(r, abs(*T - *pre));
        if(suf != x.end())
            r = min(r, abs(*T - *suf));
        x.insert(*T);
    }
    return r;
}

void DFS(int u)
{
    if(!e[u].size())
    {
        val[u].insert(w[u]);
        w[u] = INF;
        return ;
    }
    w[u] = INF;
    for(int i = 0; i < (int) e[u].size(); i ++)
    {
        int v = e[u][i];
        DFS(v);
        w[u] = min(w[u], w[v]);
        w[u] = min(w[u], Merge(val[u], val[v]));
    }
    return ;
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 2, p; i <= n; i ++)
    {
        scanf("%d", &p);
        e[p].push_back(i);
    }
    for(int i = n - m + 1; i <= n; i ++)
        scanf("%d", &w[i]);
    DFS(1);
    for(int i = 1; i <= n - m; i ++)
        printf("%d ", w[i]);
    return 0;
}
