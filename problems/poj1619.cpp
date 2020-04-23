#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 30e4 + 5;

int mark[N], list[N], p[N];

void InitTable()
{
	list[1] = 1, mark[1] = 1;
	list[2] = 2, mark[2] = 1;
	p[2] = 4;
	for( int i = 3; i < N; i ++ )
		p[i] = i;
	return ;
}

int main()
{
	int n, a;
	InitTable();
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ )
	{
		scanf( "%d", &a );
		printf( "%d\n", list[a] );
	}
	return 0;
}
