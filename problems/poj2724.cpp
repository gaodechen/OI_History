#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int INF = 0x3f3f3f3f;
const	int N = 2000, M = 1000000;

struct BPG
{
	bool vis[N];
	int n, sig, head[N], link[N];

	struct Edge
	{
		int v, next;
	} e[M];

	inline void Init( int x )
	{
		set( head, 0 );
		n = x, sig = 0;
		return ;
	}

	inline void AddEdge( int u, int v )
	{
		e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
		return ;
	}

	bool Augment( int u )
	{
		for( int i = head[u]; i; i = e[i].next )
		{
			int v = e[i].v;
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
		set( link, -1 );
		for( int i = 1; i <= n; i ++ )
		{
			set( vis, 0 );
			if( Augment( i ) )
				sum ++;
		}
		return sum;
	}

} g;

char buf[11];
int n, m, t, a[N], w[N], k[N];

int main()
{
	while( scanf( "%d%d", &n, &m ) == 2 && n )
	{
		t = 0;
		for( int i = 0; i < m; i ++ )
		{
			int s = 0, q = -1;
			scanf( "%s", buf );
			for( int j = 0; j < n; j ++ )
			{
				if( buf[j] == '1' )
					s += ( 1 << j );
				else if( buf[j] == '*' )
					q = j;
			}
			a[t++] = s;
			if( q != -1 )
				a[t++] = s + ( 1 << q );
		}
		sort( a, a + t );
		t = unique( a, a + t ) - a;
		int x = 0, y = 0;
		for( int i = 0; i < t; i ++ )
		{
			int q = 0, p = a[i];
			while( p )
			{
				p &= ( p - 1 ); 
				q ++;
			}
			k[i] = q & 1;
			if( k[i] )
				w[i] = ++ x;
			else
				w[i] = ++ y;
		}
		g.Init( x );
		for( int i = 0; i < t; i ++ )
		{
			for( int j = 0; j < i; j ++ )
			{
				int c = a[i] ^ a[j];
				if( ( c & ( c - 1 ) ) == 0 )
				{
					if( k[i] )
						g.AddEdge( w[i], w[j] );
					else
						g.AddEdge( w[j], w[i] );
				}
			}
		}
		m = g.Hungarian();
		printf( "%d\n", t - m );
	}
	return 0;
}
