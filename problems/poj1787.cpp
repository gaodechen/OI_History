#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 1e4 + 5;

char s[][10] = { "cents", "nickels", "dimes", "quarters" };
int n, k[4], q[4] = { 1, 5, 10, 25 }, d[N], pre[N][2], used[4];

void BinaryPack( int k, int t )
{
	for( int j = n; j >= t * q[k]; j -- )
	{
		if( d[j-t*q[k]] + t > d[j] )
		{
			d[j] = d[j-t*q[k]] + t;
			pre[j][0] = k;
			pre[j][1] = t;
		}
	}
	return ;
}

void InfinitePack( int k )
{
	for( int j = q[k]; j <= n; j ++ )
	{
		if( d[j-q[k]] + 1 > d[j] )
		{
			d[j] = d[j-q[k]] + 1;
			pre[j][0] = k;
			pre[j][1] = 1;
		}
	}
	return ;
}

void GetPath( int v )
{
	if( v <= 0 )
		return ;
	used[pre[v][0]] += pre[v][1];
	GetPath( v - pre[v][1] * q[pre[v][0]] );
	return ;
}

int main()
{
	while( scanf( "%d", &n ) && n )
	{
		memset( d, 128, sizeof( d ) );
		memset( pre, -1, sizeof( pre ) );
		memset( used, 0, sizeof( used ) );
		d[0] = 0;
		for( int i = 0; i < 4; i ++ )
			scanf( "%d", &k[i] );
		for( int i = 0; i < 4; i ++ )
		{
			if( k[i] * q[i] >= n )
				InfinitePack( i );
			else
			{
				int t = 1;
				while( k[i] >= t )
				{
					BinaryPack( i, t );
					k[i] -= t;
					t <<= 1;
				}
				// Be careful with that k[i] should > 0!
				if( k[i] )
					BinaryPack( i, k[i] );
			}
		}
		if( d[n] >= 0 )
		{
			GetPath( n );
			printf( "Throw in %d %s, %d %s, %d %s, and %d %s.\n", used[0], s[0], used[1], s[1], used[2], s[2], used[3], s[3] );
		}
		else
			printf( "Charlie cannot buy coffee.\n" );
	}
	return 0;
}
