#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<map>

using	namespace	std;
const	int N = 31;

int n, m, tick;
double dis[N][N];
map< string, int > hash;

int main()
{
	while( scanf( "%d", &n ) && n )
	{
		hash.clear();
		memset( dis, 0, sizeof( dis ) );
		for( int i = 1; i <= n; i ++ )
		{
			char s[50];
			dis[i][i] = 1.0;
			scanf( "%s", s );
			hash[s] = ( int )hash.size();
		}
		scanf( "%d", &m );
		for( int i = 1; i <= m; i ++ )
		{
			double k;
			char s1[50], s2[50];
			scanf( "%s%lf%s", s1, &k, s2 );
			int u = hash[s1], v = hash[s2];
			dis[u][v] = k;
		}
		for( int k = 1; k <= n; k ++ )
			for( int i = 1; i <= n; i ++ )
				for( int j = 1; j <= n; j ++ )
					if( dis[i][j] < dis[i][k] * dis[k][j] )
						dis[i][j] = dis[i][k] * dis[k][j];
		bool flag = false;
		for( int i = 1; i <= n; i ++ )
			if( dis[i][i] > 1.0 )
				flag = true;
		printf( "Case %d: %s\n", ++ tick, flag ? "Yes" : "No" );
	}
	return 0;
}
