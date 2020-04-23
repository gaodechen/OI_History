#include	<stdio.h>
#include	<string.h>
#include	<iostream>

using	namespace	std;
const	int N = 2e5 + 5;
const	int INF = 0x3fffffff;

int t, n, k, pos[N], sum[N];

int main()
{
	scanf( "%d", &t );
	while( t -- )
	{
		sum[0] = 0;
		memset( pos, 0, sizeof( pos ) );
		scanf( "%d%d", &n, &k );
		for( int i = 1; i <= n; i ++ )
		{
			int a;
			scanf( "%d", &a );
			sum[i] = sum[i-1] + a;
		}
		for( int i = n + 1; i < n + k; i ++ )
			sum[i] = sum[i-1] + sum[i-n] - sum[i-n-1];
		int head = 1, tail = 0;
		int res = -INF, p, p_;
		// Be careful with queue's head / tail!
		// Be careful! Using sum[i-1] as a[i]'s weight!
		for(int i = 1; i < n + k; i ++)
		{
			while(head <= tail && sum[i-1] < sum[pos[tail]])
				tail --;
			pos[++ tail] = i - 1;
			while(head <= tail && pos[head] + k < i)
				head ++;
			if(sum[i] - sum[pos[head]] > res)
			{
				res = sum[i] - sum[pos[head]];
				p = pos[head] + 1;
				p_ = i;
			}
		}
		printf( "%d %d %d\n", res, p, p_ > n ? p_ % n : p_ );
	}
	return 0;
}
