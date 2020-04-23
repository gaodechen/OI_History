#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

using	namespace	std;
const	int N = 2501;

struct Cow
{
	int l, r;

	bool operator < ( const Cow &b ) const
	{
		return l < b.l;
	}
} cow[N];

struct Lotion
{
	int c, n;

	bool operator < ( const Lotion &b ) const
	{
		return c < b.c;
	}
} e[N];

int n, m;
priority_queue<int, vector<int>, greater<int> > q;

int main(int argc, char **argv)
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		scanf("%d%d", &cow[i].l, &cow[i].r);
	for(int i = 1; i <= m; i ++)
		scanf("%d%d", &e[i].c, &e[i].n);
	sort(cow + 1, cow + n + 1);
	sort(e + 1, e + m + 1);
	int cur = 1, ans = 0;
	for(int i = 1; i <= m; i ++)
	{
		while(cur <= n && cow[cur].l <= e[i].c)
			q.push(cow[cur ++].r);
		while(!q.empty() && e[i].n)
		{
			int x = q.top(); q.pop();
			if(x < e[i].c) continue ;
			ans ++, e[i].n --;
		}
	}
	printf("%d\n", ans);
	return 0;
}
