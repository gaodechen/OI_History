#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 1001;

struct Edge
{
	int v, next;
} e[N*N];

int head[N], sig;

void AddEdge( int u, int v )
{
	e[++sig].v = v;
	e[sig].next = head[u];
	head[u] = sig;
	return ;
}

bool vis[N];
int n, link[N];

bool Augment( int u )
{
	for( int i = head[u]; i; i = e[i].next )
	{
		int &v = e[i].v;
		if( !vis[v] )
		{
			vis[v] = 1;
			if( link[v] == -1 || Augment( link[v] ) )
			{
				link[v] = u;
				return true;
			}
		}
	}
	return false;
}

int Hungarian()
{
	int sum = 0;
	memset( link, -1, sizeof( link ) );
	for( int i = 1; i <= n; i ++ )
	{
		memset( vis, 0, sizeof( vis ) );
		if( Augment( i ) )
			sum ++;
	}
	return sum;
}

int main()
{
	while( scanf( "%d", &n ) == 1 )
	{
		sig = 0;
		memset( head, 0, sizeof( head ) );
		for( int j = 1;  j <= n; j ++ )
		{
			int u, v, k;
			scanf( "%d: (%d)", &u, &k );
			for( int i = 1; i <= k; i ++ )
			{
				scanf( "%d", &v );
				AddEdge( u + 1, v + 1 );
			}
		}
		printf( "%d\n", n - Hungarian() / 2 );
	}
	return 0;
}
