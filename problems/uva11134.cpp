#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

using	namespace	std;
const	int N = 5e3 + 5;

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

int n, a[N], b[N];

struct Item
{
	int l, r, id;

	bool operator < ( const Item &b ) const
	{
		return l < b.l;
	}
} x[N], y[N];

struct Item_
{
	int p, v;

	Item_( int p = 0, int v = 0 ): p( p ), v( v )
	{
	}

	bool operator < ( const Item_ &b ) const
	{
		return v > b.v;
	}
};

inline bool Compute(Item *e, int *q)
{
	bool vis[N];
	int cur = 1, sum = 0;
	priority_queue<Item_> Q;
	memset(vis, 0, sizeof(vis));
	for(int i = 1; i <= n; i ++)
	{
		while( cur <= n && e[cur].l <= i )
		{
			Q.push( Item_( e[cur].id, e[cur].r ) );
			cur ++;
		}
		while( !vis[i] && !Q.empty() )
		{
			Item_ t = Q.top(); Q.pop();
			if( t.v < i )
				continue ;
			sum ++, vis[i] = 1;
			q[t.p] = i;
		}
	}
	return sum == n;
}

int main()
{
	while(scanf("%d", &n) && n)
	{
		for(int i = 1; i <= n; i ++)
		{
			x[i].l = in(), y[i].l = in();
			x[i].r = in(), y[i].r = in();
			x[i].id = y[i].id = i;
		}
		sort(x + 1, x + n + 1);
		sort(y + 1, y + n + 1);
		if(Compute(x, a) && Compute(y, b))
		{
			for(int i = 1; i <= n; i ++)
				printf("%d %d\n", a[i], b[i]);
		}
		else puts("IMPOSSIBLE");
	}
	return 0;
}
