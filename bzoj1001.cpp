#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

#define		rep( i, l, r )		for( int i = l; i <= r; i ++ )

using	namespace	std;
typedef	const int & var;
const	int BUF = 1e7;
const	int N = 1e3 + 5;
const	int INF = 0x3f3f3f3f;

char buf[BUF], *s;
int n, m, sig, ind, head[N*N*2];
int g[3][N][N], l[N][N], d[N*N*2];

struct Edge
{
	int v, w, next;
} e[N*N*8];

struct Item
{
	int u, d;

	Item( int u, int d ): u( u ), d( d )
	{
	}

	bool operator < ( const Item &b ) const
	{
		return d > b.d;
	}
} ;

inline void Emit( var u, var v, var w )
{
	e[++sig].v = v, e[sig].w = w;
	e[sig].next = head[u], head[u] = sig;
	return ;
}

inline void AddEdge( var u, var v, var w )
{
	Emit( u, v, w ), Emit( v, u, w );
	return ;
}

inline int in()
{
	int k = 0;
	while( *s > '9' || *s < '0' )
		s ++;
	while( *s <= '9' && *s >= '0' )
	{
		k = k * 10 + *s - '0';
		s ++;
	}
	return k;
}

int main(int argc, char **argv)
{
	int len = fread( buf, 1, BUF, stdin );
    buf[len] = '\0', s = buf;

	n = in(), m = in();
	rep( i, 1, n ) rep( j, 1, m - 1 )
		g[1][i][j] = in();
	rep( i, 1, n - 1 ) rep( j, 1, m )
		g[2][i][j] = in();
	rep( i, 1, n - 1 ) rep( j, 1, m - 1 )
		g[0][i][j] = in();

	rep( i, 1, n - 1 ) rep( j, 1, m - 1 )
		ind ++, l[i][j] = ind + ind;
	ind = ind + ind + 1;
    
	rep( i, 2, n - 1 ) rep( j, 1, m - 1 )
		AddEdge( l[i-1][j] - 1, l[i][j], g[1][i][j] );
	rep( i, 1, n - 1 ) rep( j, 2, m - 1 )
		AddEdge( l[i][j-1], l[i][j] - 1, g[2][i][j] );
	rep( i, 1, n - 1 ) rep( j, 1, m - 1 )
		AddEdge( l[i][j] - 1, l[i][j], g[0][i][j] );

	rep( i, 1, n - 1 )
		AddEdge( 0, l[i][1] - 1, g[2][i][1] );
	rep( i, 1, m - 1 )
		AddEdge( 0, l[n-1][i] - 1, g[1][n][i] );
	rep( i, 1, m - 1 )
		AddEdge( l[1][i], ind, g[1][1][i] );
	rep(i, 1, n - 1)
		AddEdge(l[i][m-1], ind, g[2][i][m]);

	rep(i, 0, ind) d[i] = INF;
	priority_queue<Item> q;
	q.push(Item(0, 0));

	while( d[ind] == INF ) // && !q.empty()
	{
		Item t = q.top(); q.pop();
		int u = t.u, i = head[u], v = e[i].v;
		if( d[u] != INF )
			continue ;
		d[u] = t.d;
		while( i )
		{
			if( d[v] == INF )
				q.push( Item( v, d[u] + e[i].w ) );
			i = e[i].next, v = e[i].v;
		}
	}

	printf( "%d\n", d[ind] );

	return 0;
}

