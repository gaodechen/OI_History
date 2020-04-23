#include	<cstdio>
#include	<cstdlib>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<map>
#include	<cmath>
#include	<ctime>
#include	<vector>

using	namespace	std;
typedef	long long	data;
const	int N = 1000000;
const	data INF = 1e18;

data g, l;
bool mark[N];
int tot, prime[N];

inline data Mul( data a, data b, data n )
{
	data res = 0;
	a %= n;
	while( b )
	{
		if( b & 1 )
		{
			res += a;
			if( res >= n )
				res -= n;
		}
		a <<= 1;
		if( a >= n )
			a -= n;
		b >>= 1;
	}
	return res;
}

inline data Exp( data a, data b, data n )
{
	data res = 1;
	a %= n;
	while( b )
	{
		if( b & 1 )
			res = Mul( res, a, n );
		a = Mul( a, a, n );
		b >>= 1;
	}
	return res;
}

inline void InitTable()
{
	mark[0] = mark[1] = true;
	for( int i = 2; i < N; i ++ )
	{
		if( !mark[i] )
			prime[tot++] = i;
		for( int j = 0; j < tot; j ++ )
		{
			if( i * prime[j] >= N )
				break ;
			mark[i*prime[j]] = 1;
			if( i % prime[j] == 0 )
				break ;
		}
	}
	return ;
}

bool MillerRabin( data n, int time = 10 )
{
	if( n < 2 )
		return true;
	if( n == 2 )
		return false;
	if( !( n & 1 ) )
		return false;
	int k = 0;
	data q = n - 1;
	while( !( q & 1 ) )
		k ++, q >>= 1;
	for( int i = 0; i < time; i ++ )
	{
		data a = rand() % ( n - 1 ) + 1;
		data x = Exp( a, q, n );
		if( x == 1 )
			continue ;
		bool mark = false;
		for( int j = 0; j < k; j ++ )
		{
			if( x == n - 1 )
			{
				mark = true;
				break ;
			}
			x = Mul( x, x, n );
		}
		if( mark )
			continue ;
		return false;
	}
	return true;
}

data gcd( data a, data b )
{
	if( b == 0 )
		return a;
	return gcd( b, a % b );
}

data PollardRho( data n, int c )
{
	data x = 2, y = 2, d = 1;
	while( d == 1 )
	{
		x = Mul( x, x, n ) + c;
		y = Mul( y, y, n ) + c;
		y = Mul( y, y, n ) + c;
		d = gcd( x - y >= 0 ? x - y : y - x, n );
	}
	if( d == n )
		return PollardRho( n, c + 1 );
	return d;
}

bool Judge( data n )
{
	if( n < N )
		return !mark[n];
	return MillerRabin( n, 20 );
}

void Factorize( data n, map< data, int > &fac )
{
	if( Judge( n ) )
		fac[n] ++;
	else
	{
		for( int i = 0; i < tot; i ++ )
		{
			int p = prime[i];
			while( n % p == 0 )
			{
				fac[p] ++;
				n /= p;
			}
		}
		if( n != 1 )
		{
			if( Judge( n ) )
				fac[n] ++;
			else
			{
				data d = PollardRho( n, 1 );
				Factorize( d, fac );
				Factorize( n / d, fac );
			}
		}
	}
	return ;
}

int main()
{
	InitTable();
	srand( time( NULL ) );
	while( scanf( "%lld%lld", &g, &l ) == 2 )
	{
		vector< data > list;
		map< data, int > fac;
		if( l == g )
		{
			printf( "%lld %lld\n", l, g );
			continue ;
		}
		data c = l / g;
		Factorize( c, fac );
		map< data, int >::iterator iter = fac.begin();
		for( ; iter != fac.end(); iter ++ )
		{
			data mul = 1, k = iter -> first;
			while( iter -> second )
			{
				mul *= k;
				iter -> second --;
			}
			list.push_back( mul );
		}
		data optSum = INF, optX = 1, optY = c;
		int size = ( int ) list.size();
		for( int mask = 0; mask < ( 1 << size ); mask ++ )
		{
			data x = 1;
			for( int i = 0; i < size; i ++ )
				if( mask & ( 1 << i ) )
					x *= list[i];
			data y = c / x;
			if( x < y && x + y < optSum )
				optX = x, optY = y, optSum = x + y;
		}
		printf( "%lld %lld\n", optX * g, optY * g );
	}
	return 0;
}
