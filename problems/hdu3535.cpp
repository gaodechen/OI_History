#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 110;

int n, t, m, s, d[N], f[N], cost, val;

void Pack0()
{
	memcpy(f, d, sizeof(d));
	memset(d, -1, sizeof(d));
	for(int i = 0; i < m; i ++)
	{
		scanf("%d%d", &cost, &val);
		for(int j = t; j >= cost; j --)
		{
			if(d[j - cost] != -1)
				d[j] = max(d[j], d[j - cost] + val);
			if(f[j - cost] != -1)
				d[j] = max(d[j], f[j - cost] + val);
		}
	}
	return ;
}

void Pack1()
{
	memcpy(f, d, sizeof(d));
	for(int i = 1; i <= m; i ++)
	{
		scanf("%d%d", &cost, &val);
		for(int i = t; i >= cost; i --)
			if(f[i - cost] != -1)
				d[i] = max(d[i], f[i - cost] + val);
	}
	return ;
}

void Pack2()
{
	for(int i = 1; i <= m; i ++)
	{
		scanf("%d%d", &cost, &val);
		for(int i = t; i >= cost; i --)
			if(d[i - cost] != -1)
				d[i] = max(d[i], d[i - cost] + val);
	}
	return ;
}

int main()
{
	while(scanf("%d%d", &n, &t) == 2)
	{
		memset(d, 0, sizeof(d));
		for(int i = 1; i <= n; i ++)
		{
			scanf("%d%d", &m, &s);
			if(s == 0) Pack0();
			else if(s == 1) Pack1();
			else Pack2();
		}
		printf("%d\n", d[t]);
	}
	return 0;
}
