#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

using	namespace	std;
const	int M = 1e5 + 20;
const	int INF = 0x3f3f3f3f;

int N, C, F, H;
int lower[M], upper[M];
pair< int, int > cow[M];

int main()
{
	while( scanf( "%d%d%d", &N, &C, &F ) == 3 )
	{
		H = N / 2;
		for( int i = 0; i < C; i ++ )
			scanf( "%d%d", &cow[i].first, &cow[i].second );
		sort( cow, cow + C );

		{
			int total = 0;
			priority_queue< int > q;
			for( int i = 0; i < C; i ++ )
			{
				int size = ( int ) q.size();
				if( size == H )
					lower[i] = total;
				else
					lower[i] = INF;
				q.push( cow[i].second );
				total += cow[i].second;
				if( size + 1 > H )
				{
					total -= q.top();
					q.pop();
				}
			}
		}

		{
			int total = 0;
			priority_queue< int > q;
			for( int i = C - 1; i >= 0; i -- )
			{
				int size = ( int ) q.size();
				if( size == H )
					upper[i] = total;
				else
					upper[i] = INF;
				q.push( cow[i].second );
				total += cow[i].second;
				if( size + 1 > H )
				{
					total -= q.top();
					q.pop();
				}
			}
		}
		int ans = -1;
		for( int i = C - 1; i >= 0; i -- )
		{
			if( lower[i] + cow[i].second + upper[i] <= F )
			{
				ans = cow[i].first;
				break ;
			}
		}
		printf( "%d\n", ans );
	}
	return 0;
}
