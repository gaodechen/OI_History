#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<map>
#include	<cmath>

using	namespace	std;
typedef	long long	data;

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
	if(b == 1) return 0;
	int cnt = 0;
	data t = 1;
	for(int g = gcd(a, p); g != 1; g = gcd(a, p))
	{
		if(b % g) return -1;
		p /= g, b /= g, t = t * a / g % p, cnt ++;
        // (a / g) ^ (-1) * (b / g) = 1, the minimum answer is cnt
		if(b == t) return cnt;
	}
	map<int, int> hash;
	int m = (int) sqrt(p + 1);
	data base = b;
	for(int i = 0; i < m; i ++)
	{
		hash[base] = i;
		base = base * a % p;
	}
	base = Mul(a, m, p);
	data tmp = t;
	for(int i = 1; i <= m + 1; i ++)
	{
		tmp = tmp * base % p;
		if(hash.count(tmp))
			return i * m - hash[tmp] + cnt;
	}
	return -1;
}

int main()
{
	int a, b, p;
	while( scanf( "%d%d%d", &a, &p, &b ) && p )
	{
		int ans = BSGS( a, b, p );
		if( ans == -1 )
			printf( "No Solution\n" );
		else
			printf( "%d\n", ans );
	}
	return 0;
}
