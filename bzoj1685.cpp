#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

inline int in()
{
	int k = 0, c = '\0';
	for(; c > '9' || c < '0';)
        c = getchar();
	for(; c >= '0' && c <= '9';)
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k;
}

struct Item
{
    int w, c;

    bool operator < (const Item &b) const
    {
        return w < b.w;
    }
} e[21];

int main(int argc, char **argv)
{
    int n = in(), c = in();
    for(int i = 1; i <= n; i ++)
        e[i].w = in(), e[i].c = in();
    int ans = 0;
    sort(e + 1, e + n + 1);
    while(e[n].w >= c)
        ans += e[n].c, n --;
    while(true)
    {
        int sur = c;
        for(int i = n; i >= 1; i --)
        {
            if(e[i].c == 0) continue ;
            int t = min(sur / e[i].w, e[i].c);
            sur -= t * e[i].w, e[i].c -= t;
        }
        for(int i = 1; i <= n; i ++)
            if(sur > 0 && e[i].c)
                sur -= e[i].w, e[i].c --;
        if(sur > 0) break ;
        ans ++;
    }
    printf("%d", ans);
    return 0;
}
