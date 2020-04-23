#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
typedef	long long	data;

data p, q, a1, a2, n, MOD;

struct Matrix
{
	data a[2][2];

	Matrix()
	{
		memset( a, 0, sizeof( a ) );
	}

	Matrix operator * ( const Matrix &b ) const
	{
		Matrix c;
		for( int i = 0; i < 2; i ++ )
		{
			for( int k = 0; k < 2; k ++ ) if( a[i][k] )
			{
				for( int j = 0; j < 2; j ++ ) if( b.a[k][j] )
				{
					c.a[i][j] += a[i][k] * b.a[k][j];
					if( c.a[i][j] >= MOD )
						c.a[i][j] %= MOD;
				}
			}
		}
		return c;
	}

} e, r, o;

Matrix Pow( int k )
{
	Matrix c = e, b = r;
	while( k )
	{
		if( k & 1 )
			c = c * b;
		b = b * b;
		k >>= 1;
	}
	return c;
}

int main()
{
	cin >> p >> q >> a1 >> a2 >> n >> MOD;
	if( n == 1 )
	{
		cout << a1 << endl;
		return 0;
	}
	e.a[0][0] = e.a[1][1] = 1;
	o.a[0][0] = a2, o.a[1][0] = a1;
	r.a[0][0] = p, r.a[0][1] = q, r.a[1][0] = 1;
	int ans = ( Pow( n - 1 ) * o ).a[1][0];
	cout << ans % MOD << endl;
	return 0;
}
