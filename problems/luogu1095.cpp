#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;

int m, s, t;

int main()
{
	scanf( "%d%d%d", &m, &s, &t );
	int dis = s, cur = 0;
	while( dis > 0 && cur < t )
	{
		if( dis <= 17 )
			dis -= 17, cur ++;
		else if( m >= 10 )
		{
			int tmp = min( m / 10, t - cur );
			dis -= tmp * 60, cur += tmp, m -= tmp * 10;
		}
		else if( m >= 6 && cur + 1 <= t )
			m -= 6, dis -= 60, cur += 2;
		else if( m >= 2 && cur + 2 <= t )
			m -= 2, dis -= 60, cur += 3;
		else if( cur + 7 <= t && dis > 102 )
			dis -= 120, cur += 7;
		else
		{
			int tmp = min( ( dis + 16 ) / 17, t - cur );
			dis -= 17 * tmp, cur += tmp;
		}
	}
	if( dis > 0  )
		printf( "No\n%d\n", s - dis );
	else
		printf( "Yes\n%d\n", cur );
	return 0;
}
