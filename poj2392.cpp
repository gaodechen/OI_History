#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

#define		set(p, k)		memset(p, k, sizeof(p))
#define		cpy(p, k)		memcpy(p, k, sizeof(k))

using	namespace	std;
typedef const int & var;
const	int INF = 0x3f3f3f3f;
const	int N = 401, M = 400001;

struct Item
{
	int h, a, c;

	bool operator < (const Item &b) const
	{
		return a < b.a; 
	}
} e[N];

bool d[M];
int k, sum;

void BinaryPack(int cost, int lim)
{
	for(int j = lim; j >= cost; j --)
		d[j] = d[j] || d[j-cost];
	return ;
}

int main()
{
	scanf("%d", &k);
	for(int i = 1; i <= k; i ++)
	{
		scanf("%d%d%d", &e[i].h, &e[i].a, &e[i].c);
		sum += e[i].h * e[i].c;
	}
	sort(e + 1, e + k + 1);
	d[0] = 1;
	for(int i = 1; i <= k; i ++)
	{
		int k = 1;
		while(k < e[i].c)
		{
			BinaryPack(k * e[i].h, e[i].a);
			e[i].c -= k;
			k <<= 1;
		}
		BinaryPack(e[i].c * e[i].h, e[i].a);
	}
	int ans;
	for(int i = sum; i >= 0; i --)
	{
		if(d[i])
		{
			ans = i;
			break ;
		}
	}
	printf("%d\n", ans);
	return 0;
}
