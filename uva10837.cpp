#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e4 + 5;
const	int INF = 0x3f3f3f3f;

bool mark[N];
int tot, tik, ans, prm[N], fac[N], v[N];

void InitTable()
{
	for( int i = 2; i < N; i ++ )
	{
		if( !mark[i] )
			prm[tot++] = i;
		for( int j = 0; j < tot; j ++ )
		{
			int k = i * prm[j];
			if( k >= N )
				break ;
			mark[k] = 1;
			if( i % prm[j] == 0 )
				break ;
		}
	}
	return ;
}

void GetFactors( int n )
{
	tik = 0;
	for( int i = 0; i < tot && ( prm[i] - 1 ) * ( prm[i] - 1 ) <= n; i ++ )
		if( n % ( prm[i] - 1 ) == 0 )
			fac[tik++] = prm[i];
	return ;
}

bool Judge( int n )
{
	if( n == 2 )
		return true;
	for( int i = 0; i < tot && prm[i] * prm[i] <= n; i ++ )
		if( n % prm[i] == 0 )
			return false;
	// Check if has been visited
	for( int i = 0; i < tik; i ++ )
		if( v[i] && fac[i] == n )
			return false;
	return true;
}

void DFS( int res, int cur, int d )
{
	if( d == tik )
	{
		if( Judge( cur + 1 ) )
		{
			if( cur == 1 )
				cur = 0;
			ans = min( ans, res * ( cur + 1 ) );
		}
		return ;
	}
	DFS( res, cur, d + 1 );
	if( cur % ( fac[d] - 1 ) == 0 )
	{
		v[d] = 1;
		res *= fac[d];
		cur /= ( fac[d] - 1 );
		while( true )
		{
			DFS( res, cur, d + 1 );
			if( cur % fac[d] )
				return ;
			res *= fac[d];
			cur /= fac[d];
		}
		v[d] = 0;
	}
	return ;
}

int Compute( int n )
{
	ans = INF;
	GetFactors( n );
	memset( v, 0, sizeof( v ) );
	DFS( 1, n, 0 );
	return ans;
}

int main()
{
	freopen( "a.in", "r", stdin );
	InitTable();
	int c = 0, n, ans;
	while( scanf( "%d", &n ) == 1 && n )
	{
		ans = Compute( n );
		printf( "Case %d: %d %d\n", ++ c, n, ans );
	}
	return 0;
}
