#include	<cmath>
#include	<cstdio>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e4 + 5;

double l, w, w_;
int vis[N], n, t;

struct Interval
{
	double a, b;
	bool operator < ( const Interval &p ) const
	{
		return a < p.a;
	}
} e[N];

int main()
{
	while( scanf( "%d%lf%lf", &n, &l, &w ) == 3 )
	{
		t = 0;
		for( int i = 1; i <= n; i ++ )
		{
			double p, r;
			scanf( "%lf%lf", &p, &r );
			if( r + r <= w )
				continue ;
			w_ = sqrt( r * r - w * w / 4.0 );
			e[++t].a = p - w_;
			e[t].b = p + w_;
		}
		sort( e + 1, e + t + 1 );
		double pos = 0;
		int k = 0, flag = 1, ans = 0;
		while( pos < l )
		{
			double tmp = pos;
			for( int i = k + 1; e[i].a <= pos && i <= t; i ++ )
			{
				if( e[i].b > tmp )
				{
					k = i;
					tmp = e[i].b;
				}
			}
			if( tmp <= pos )
			{
				flag = 0;
				break ;
			}
			pos = tmp, ans ++;
		}
		printf( "%d\n", flag ? ans : -1 );
	}
	return 0;
}
