#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <vector>

using   namespace   std;
const   int N = 1001, K = 2000;

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

bool vis[N];
int f[N][2];
vector<int> e[N];

void DFS(int u)
{
    vis[u] = 1, f[u][0] = 0, f[u][1] = K;
    int size = (int) e[u].size();
    for(int i = 0; i < size; i ++)
    {
        int v = e[u][i];
        if(vis[v]) continue ;
        DFS(v);
        f[u][0] += f[v][1] + 1;
        if(f[v][0] < f[v][1])
            f[u][1] += f[v][0] + 1;
        else
            f[u][1] += f[v][1];
    }
    return ;
}

int main(int argc, char **argv)
{
    int T = in();
    while(T --)
    {
        int n = in(), m = in();
        for(int i = 0; i < n; i ++)
            e[i].clear();
        for(int i = 0; i < m; i ++)
        {
            int u = in(), v = in();
            e[u].push_back(v);
            e[v].push_back(u);
        }
        memset(vis, 0, sizeof(vis));
        int ans = 0;
        for(int i = 0; i < n; i ++)
        {
            if(vis[i]) continue ;
            DFS(i), ans += min(f[i][0], f[i][1]);
        }
        int a = ans / K, r = ans % K;
        printf("%d %d %d\n", a, m - r, r);
    }
    return 0;
}
