#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <queue>
#include    <vector>

using   namespace   std;
const   int N = 5e3 + 5;
const   int INF = 0x3f3f3f3f;

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

vector<int> e[N];
int n, f[N][N], size[N];

void DFS(int u, int p)
{
    f[u][0] = 0;
    if(e[u].size() == 1) size[u] = 1;
    /* u is white, and we can compute f[u] using f[v] which v is also white easily */
    for(int i = 0; i < (int) e[u].size(); i ++)
    {
        int v = e[u][i];
        if(v == p) continue ;
        DFS(v, u);
        /* Select one at least in every child */
        for(int i = size[u]; i >= 0; i --)
            for(int j = 0; j <= size[v]; j ++)
                f[u][i + j] = min(f[u][i + j], f[u][i] + f[v][j]);
        size[u] += size[v];
    }
    /* i black vertexes -> i white vertexes, size[u] - i black ones */
    /* f[u][size[u] - i] + 1 */
    for(int i = 0; i <= size[u]; i ++)
        f[u][i] = min(f[u][i], f[u][size[u] - i] + 1);
    /* After this operator, f[u][i / 2 ... n]'s definition is different, */
    /* As f[u][i / 2 ... n] will be used in DP as f[u][i] + f[v][j] */
    /* This means it's the same as f[u][i] + f[v][size[v] - j] + 1 */
    /* One last thing about it here: i = size[u] / 2 + 1 is also correct */
    return ;
}

int main()
{
    n = in();
    memset(f, INF, sizeof(f));
    for(int i = 1; i < n; i ++)
    {
        int u = in(), v = in();
        e[u].push_back(v);
        e[v].push_back(u);
    }
    int root = 1;
    while(e[root].size() == 1)
        root ++;
    DFS(root, 0);
    printf("%d\n", f[root][size[root] >> 1]);
    return 0;
}
