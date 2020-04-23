#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<vector>

using	namespace	std;
const	int N = 200;

int n, m, k;
vector< int > e[N];
int link[N], vis[N];

bool Augment( int u )
{
	for( int i = 0; i < ( int )e[u].size(); i ++ )
	{
		int v = e[u][i];
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
	for( int i = 1; i < n; i ++ )
	{
		memset( vis, 0, sizeof( vis ) );
		if( Augment( i ) )
			sum ++;
	}
	return sum;
}

int main()
{
	while( scanf( "%d%d%d", &n, &m, &k ) == 3 )
	{
		for(int i = 0; i < n; i ++)
			e[i].clear();
		while(k --)
		{
			int x, y;
			scanf("%*d%d%d", &x, &y);
			if(x && y)
				e[x].push_back(y);
		}
		printf("%d\n", Hungarian());
	}
	return 0;
}

