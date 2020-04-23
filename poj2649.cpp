#include	<cmath>
#include	<cstdio>

int n, m, m_, tmp;

inline int F( int d )
{
	tmp = n;
	int sum = 0;
	while( tmp )
	{
		sum += tmp / d;
		tmp /= d;
	}
	return sum;
}

int main()
{
	while( scanf( "%d%d", &n, &m ) == 2 )
	{
		m_ = m;
		int flag = 1;
		if( ( n == 0 && m != 1 ) || m == 0  )
			flag = 0;
		else if( n >= m || m == 1 )
			;
		else
		{
			for( int i = 2; i <= sqrt( m + 0.5 ); i ++ )
			{
				if( m % i == 0 )
				{
					int sum = 0;
					while( m % i == 0 )
						sum ++, m /= i;
					if( sum > F( i ) )
					{
						flag = 0;
						break ;
					}
				}
			}
			if( m > 1 && F( m ) < 1 )
				flag = 0;
		}
		if( flag )
			printf( "%d divides %d!\n", m_, n );
		else
			printf( "%d does not divide %d!\n", m_, n );
	}
	return 0;
}
