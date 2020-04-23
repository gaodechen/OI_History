#include	<cstdio>
#include	<iostream>

using	namespace	std;
typedef long long 	data;
const	int N = 1e5 + 5;
const   data INF = 0x3f3f3f3f3f3f;

int n, q[N];
data m, a[N], f[N];

data Compute()
{
	data sum = 0;
	int l, r, k, t;
	l = 1, r = 0, k = 0;
	for( int i = 1; i <= n; i ++ )
	{
		if( a[i] > m )
			return -1;
		sum += a[i];
		while( sum > m )
			sum -= a[++k];
        // sum[a[k+1]...a[i]] <= m
		while( l <= r && a[q[r]] <= a[i] )
			r --;
		q[++r] = i;
		while( l <= r && q[l] <= k )
            l ++;
		t = k, f[i] = INF;
		for( int j = l; j <= r; j ++ )
		{
			data tmp = f[t] + a[q[j]];
			if( tmp < f[i] )
				f[i] = tmp;
			t = q[j];
		}
	}
	return f[n];
}

int main()
{
	scanf( "%d%lld", &n, &m );
	for( int i = 1; i <= n; i ++ )
		scanf( "%d", &a[i] );
	data ans = Compute();
	printf( "%lld\n", ans );
	return 0;
}
