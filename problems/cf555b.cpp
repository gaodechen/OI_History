#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

using namespace std;
typedef long long data;
const int N = 2e5 + 5;

template <typename T> inline T in()
{
	T k = 0; int f = 1, c = '\0';
	for(; c > '9' || c < '0';)
		if((c = getchar()) == '-')
            f = 0;
	for(; c >= '0' && c <= '9';)
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return f ? k : -k;
}

struct Cow
{
    data l, r; int tick;

    bool operator < ( const Cow &b ) const
    {
        return l < b.l;
    }
} cow[N], cow0[N];

struct Lotion
{
    data c; int tick;

    bool operator < ( const Lotion &b ) const
    {
        return c < b.c;
    }
} e[N];

struct cmp
{
    bool operator() (const int &a, const int &b)
    {
        return cow0[a].r > cow0[b].r;
    }
};

int n, m, ans[N];
priority_queue<int, vector<int>, cmp > q;
data l[N], r[N];

int main(int argc, char **argv)
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++)
        l[i] = in<data>(), r[i] = in<data>();
    for(int i = 2; i <= n; i ++)
    {
        cow[i - 1].l = l[i] - r[i - 1];
        cow[i - 1].r = r[i] - l[i - 1];
        cow[i - 1].tick = i - 1;
    }
    n --;
    for(int i = 1; i <= m; i ++)
        e[i].c = in<data>(), e[i].tick = i;
    memcpy(cow0, cow, sizeof(cow));
    sort(cow + 1, cow + n + 1);
    sort(e + 1, e + m + 1);
    int cur = 1, Count = 0;
    for(int i = 1; i <= m; i ++)
    {
        while(cur <= n && cow[cur].l <= e[i].c)
            q.push(cow[cur ++].tick);
        if(!q.empty())
        {
            int x = q.top(); q.pop();
            if(cow0[x].r < e[i].c) continue ;
            ans[cow0[x].tick] = e[i].tick;
            Count ++;
        }
    }
    if(Count != n) return puts("No"), 0;
    puts("Yes");
    for(int i = 1; i <= n; i ++)
        printf("%d ", ans[i]);
    return 0;
}
