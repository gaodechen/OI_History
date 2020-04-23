#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<vector>

using	namespace	std;
const	int N = 2e2 + 5;
const	int M = 1e4 + 5;
const	int INF = 0x3f3f3f3f;

struct Edge
{
	int v, next;
} e[M];

vector< int > list[N];
bool G[N][N], mark[N];
int a[N], b[N], d[N][N], head[N];
int n, m, sig, col[N], pre[N][N];

inline void AddEdge( int u, int v )
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
	return ;
}

bool Color( int u )
{
	if( col[u] == 1 )
		list[m+m-1].push_back( u );
	else
		list[m+m].push_back( u );
	for( int i = head[u]; i; i = e[i].next )
	{
		int v = e[i].v;
		if( !col[v] )
		{
			col[v] = -col[u];
			if( !Color( v ) )
				return false;
		}
		else if( col[v] == col[u] )
			return false;
	}
	return true;
}

void Print( int k, int s )
{
	if( !k )
		return ;
	int p = pre[k][s];
	Print( k - 1, s - list[p].size() );
	for( int i = 0; i < ( int ) list[p].size(); i ++ )
		mark[list[p][i]] = 1;
	return ;
}

int main()
{
	scanf( "%d", &n );
	for( int i = 1, j; i <= n; i ++ )
		while( scanf( "%d", &j ) && j )
			G[i][j] = 1;
	for( int i = 1; i <= n; i ++ )
		for( int j = 1; j < i; j ++ )
			if( !( G[i][j] && G[j][i] ) )
				AddEdge( i, j ), AddEdge( j, i );
	for( int i = 1; i <= n; i ++ )
	{
		if( !col[i] )
		{
			col[i] = 1, m ++;
			if( !Color( i ) )
			{
				printf( "No solution\n" );
				return 0;
			}
			a[m] = list[m+m-1].size();
			b[m] = list[m+m].size();
		}
	}
	for( int i = 0; i < N; i ++ )
		for( int j = 0; j < N; j ++ )
			d[i][j] = -INF;
	d[0][0] = 0;
	for( int i = 1; i <= m; i ++ )
	{
		for( int j = n / 2; j; j -- )
		{
			int v = -INF, p;
			if( j >= a[i] && d[i-1][j-a[i]] >= 0 )
				v = d[i-1][j-a[i]] + a[i], p = i + i - 1;
			if( j >= b[i] && d[i-1][j-b[i]] + b[i] > v )
				v = d[i-1][j-b[i]] + b[i], p = i + i;
			d[i][j] = v, pre[i][j] = p;
		}
	}
	int t = n / 2;
	while( d[m][t] < 0 )
		t --;
	Print( m, d[m][t] );
	printf( "%d", d[m][t] );
	for( int i = 1; i <= n; i ++ ) if( mark[i] )
		printf( " %d", i );
	printf( "\n%d", n - d[m][t] );
	for( int i = 1; i <= n; i ++ ) if( !mark[i] )
		printf( " %d", i );
	return 0;
}
