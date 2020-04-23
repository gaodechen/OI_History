#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <cmath>
#include    <vector>

using   namespace   std;
const   int N = 60001;

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

vector<int> list[N];
int n, SIZE, w[N], size[N], top[N];

struct Graph
{
    int v[N], next[N], head[N], i;

    inline void AddEdge(int a, int b)
    {
        v[++ i] = b, next[i] = head[a], head[a] = i;
    }
} g, block, linker;

void InitBlock(int u, int p)
{
    int root = top[u];
    list[root].push_back(w[u]);
    for(int i = g.head[u]; i; i = g.next[i])
    {
        int v = g.v[i];
        if(v == p) continue ;
        block.AddEdge(u, v);
        if(size[root] < SIZE)
            size[root] ++, top[v] = root;
        else
            linker.AddEdge(root, v);
        InitBlock(v, u);
    }
    return ;
}

int sum;

void QueryBlock(int u, int x)
{
    sum += list[u].end() - upper_bound(list[u].begin(), list[u].end(), x);
    for(int i = linker.head[u]; i; i = linker.next[i])
        QueryBlock(linker.v[i], x);
    return ;
}

void QueryOutboard(int u, int x)
{
    if(w[u] > x) sum ++;
    for(int i = block.head[u]; i; i = block.next[i])
    {
        int v = block.v[i];
        if(top[u] == top[v])
            QueryOutboard(v, x);
        else
            QueryBlock(v, x);
    }
    return ;
}

int main(int argc, char **argv)
{
    n = in(), SIZE = (int) ceil(sqrt(n) * log2(n));
    for(int i = 1; i < n; i ++)
    {
        int u = in(), v = in();
        g.AddEdge(u, v), g.AddEdge(v, u);
    }
    for(int i = 1; i <= n; i ++)
        w[i] = in(), size[i] = 1, top[i] = i;
    InitBlock(1, 0);
    for(int i = 1; i <= n; i ++)
        if(top[i] == i)
            sort(list[i].begin(), list[i].end());
    int q = in(), last = 0;
    while(q --)
    {
        int c = in(), u = in() ^ last, x = in() ^ last;
        if(c == 0)
        {
            sum = 0;
            if(u == top[u])
                QueryBlock(u, x);
            else
                QueryOutboard(u, x);
            printf("%d\n", last = sum);
        }
        else if(c == 1)
        {
            int t = top[u];
            list[t].erase(lower_bound(list[t].begin(), list[t].end(), w[u]));
            list[t].insert(lower_bound(list[t].begin(), list[t].end(), x), x);
            w[u] = x;
        }
        else if(c == 2)
        {
            w[++ n] = x; int t = top[u];
            block.AddEdge(u, n);
            if(size[t] < SIZE)
            {
                top[n] = t, size[t] ++;
                list[t].insert(lower_bound(list[t].begin(), list[t].end(), x), x);
            }
            else
            {
                top[n] = n, size[u] = 1;
                list[n].push_back(x);
                linker.AddEdge(top[u], n);
            }
        }
    }
    return 0;
}
