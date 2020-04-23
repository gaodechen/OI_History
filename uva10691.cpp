#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<cmath>

using	namespace	std;
const	double EPS = 1e-9;
const	double PI = acos( -1.0 );
const	int	   N = 201, INF = 0x3f3f3f3f;

struct Point
{
	int x, y;
} e[N];

int t, n;

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ )
		{
			int x, y;
			scanf( "%d%d", &x, &y );
			scanf( "%d%d", &e[i].x. &e[i].y );
		}
	}
	return 0;
}
