#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<queue>

using	namespace	std;
const	int N = 3e5 + 5;
const   int INF = 0x3f3f3f3f;

inline int in()
{
	int k = 0, c = '\0';
	for( ; c > '9' || c < '0'; )
		c = getchar();
	for( ; c >= '0' && c <= '9'; )
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k;
}

struct Edge
{
	int v, next;
} e[N+N];

int n, m, sig, tik, pre[N], mark[N];
int seq[N], head[N], fire[N], dynamite[N];

inline void AddEdge(int u, int v)
{
	e[++sig].v = v, e[sig].next = head[u];
	return (void) (head[u] = sig);
}

inline void BFS()
{
	queue<int> q;
	q.push(1);
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		seq[++tik] = u;
		for(int i = head[u]; i; i = e[i].next)
		{
			int v = e[i].v;
            if(v != pre[u])
			{
				q.push(v);
				pre[v] = u;
			}
		}
	}
	return ;
}

inline bool Check(int k)
{
    for(int i = 1; i <= n; i ++)
    {
        fire[i] = INF;
        if(mark[i])
            dynamite[i] = 0;
        else
            dynamite[i] = -INF;
    }
    int cnt = 0;
    // fire: The distance to the nearest fire vertex
    // dynamite: The distance to the farthest vertex waiting for burning
    for(int i = n; i; i --)
	{
		int u = seq[i];
        if(fire[u] > k)
            fire[u] = INF;
        if(dynamite[u] + fire[u] <= k)
            dynamite[u] = -INF;
        if(dynamite[u] == k)
        {
            dynamite[u] = -INF;
            fire[u] = 0;
            cnt ++;
        }
        if(cnt > m)
            break ;
        int p = pre[u];
        fire[p] = min(fire[p], fire[u] + 1);
        dynamite[p] = max(dynamite[p], dynamite[u] + 1);
	}
    if(dynamite[1] >= 0)
        cnt ++;
	return cnt <= m;
}

int main()
{
    n = in(), m = in();
	for(int i = 1; i <= n; i ++)
        mark[i] = in();
	for(int i = 1; i < n; i ++)
	{
		int u = in(), v = in();
		AddEdge(u, v);
		AddEdge(v, u);
	}
	BFS();
	int l = 0, r = (n + 1) / 2;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(Check(mid))
			r = mid;
		else
			l = mid + 1;
	}
	printf("%d\n", l);
	return 0;
}
