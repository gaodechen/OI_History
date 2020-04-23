#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<map>
#include	<cmath>

using	namespace	std;
typedef	long long	data;
const	int MOD = 133331;

inline int in()
{
	int k = 0, c = '\0';
	for( ; c > '9' || c < '0'; )
		c = getchar();
	for( ; c >= '0' && c <= '9'; )
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k;
}

int sig, hash[MOD], head[MOD], next[MOD], key[MOD];

void Insert( int x, int p )
{
	int k = x % MOD;
	hash[++sig] = x, key[sig] = p;
	next[sig] = head[k], head[k] = sig;
	return ;
}

inline int Find( int x )
{
	int k = x % MOD;
	for(int i = head[k]; i; i = next[i])
		// hash[i] == (x): WA here at first
		if(hash[i] == x)
			return key[i];
	return -1;
}

inline int Mul( data x, data p, data mod )
{
	data k = 1;
	while( p )
	{
		if( p & 1 )
			k = x * k % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return k;
}

int gcd( int a, int b )
{
	return b ? gcd( b, a % b ) : a;
}

int BSGS( int a, int b, int p )
{
	a %= p, b %= p;
	if( b == 1 )
		return 0;
	int cnt = 0;
	data t = 1;
	for( int g = gcd( a, p ); g != 1; g = gcd( a, p ) )
	{
		if( b % g )
			return -1;
		p /= g, b /= g;
		t = t * a / g % p;
		cnt ++;
		if( b == t )
			return cnt;
	}
	int m = ( int ) sqrt( p + 1 );
	data base = b;
	for( int i = 0; i < m; i ++ )
	{
		Insert( base, i );
		base = base * a % p;
	}
	base = Mul( a, m, p );
	data tmp = t;
	for( int i = 1; i <= m + 1; i ++ )
	{
		tmp = tmp * base % p;
		if( tmp == 296979 )
			;
		int t = Find( tmp );
		if( t != -1 )
			return i * m - t + cnt;
	}
	return -1;
}

int main()
{
	int a, b, p;
	while( true )
	{
		a = in(), p = in(), b = in(), sig = 0;
		if( !p )
			break ;
		memset( head, -1, sizeof( head ) );
		int ans = BSGS( a, b, p );
		if( ans == -1 )
			printf( "No Solution\n" );
		else
			printf( "%d\n", ans );
	}
	return 0;
}
