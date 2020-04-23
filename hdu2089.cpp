#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 10;

int l, r, d[N][N], dig[N];

int f( int n )
{
	int len = 0, n_ = n;
	while( n_ )
	{
		dig[++len] = n_ % 10;
		n_ /= 10;
	}
	dig[len+1] = 0;
	int res = 0;
	for(int i = len; i; i --)
	{
		for(int j = 0; j < dig[i]; j ++)
			if( !( j == 2 && dig[i+1] == 6) && j != 4)
				res += d[i][j];
		if( ( dig[i] == 2 && dig[i+1] == 6 ) || dig[i] == 4 )
			break ;
	}
	return res;
}

int main()
{
    freopen("in", "r", stdin);
	d[0][0] = 1;
	for( int i = 1; i <= 7; i ++ )
		for( int j = 0; j <= 9; j ++ )
			for( int k = 0; k <= 9; k ++ )
				if( !( j == 6 && k == 2 ) && j != 4 )
					d[i][j] += d[i-1][k];
	while( scanf( "%d%d", &l, &r ) == 2 && l && r )
		printf( "%d\n", f( r + 1 ) - f( l ) );
	return 0;
}
