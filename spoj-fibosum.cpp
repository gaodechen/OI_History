#include	<cstdio>
#include	<cstring>
#include	<iostream>

#define		set( p, k )		memset( p, k, sizeof( p ) )

using	namespace	std;
const	int N = 2, M = 1000000007;

struct Matrix
{
	long long a[2][2];

	Matrix operator * ( const Matrix &b ) const
	{
		Matrix c;
		memset( c.a, 0, sizeof( c.a ) );
		for( int i = 0; i < N; i ++ )
			for( int k = 0; k < N; k ++ ) if( a[i][k] )
				for( int j= 0; j < N; j ++ ) if( b.a[k][j] )
					c.a[i][j] += ( a[i][k] * b.a[k][j] ) % M;
		return c;
	}
} e, f, q;

Matrix Power( int k )
{
	Matrix res = e, base = f;
	while( k )
	{
		if( k & 1 )
			res = res * base;
		base = base * base;
		k >>= 1;
	}
	return res;
}

int t, a, b;

int main()
{
	set(e.a, 0), set(f.a, 0), set(q.a, 0);
	e.a[0][0] = e.a[1][1] = 1;
	q.a[0][0] = q.a[1][0] = 1;
	f.a[0][0] = f.a[0][1] = f.a[1][0] = 1;
	scanf("%d", &t);
	while(t --)
	{
		long long t1, t2;
		scanf( "%d%d", &a, &b );
		t1 = Power(a + 1).a[0][1];
		t2 = Power(b + 2).a[0][1];
		printf("%lld\n", ((t2 - t1) % M + M) % M);
	}
	return 0;
}
