#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using namespace	std;

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

const int N = 5e4 + 5;

int q[N];

int main(int argc, char **argv)
{
    int n = in(); in();
    int ans = n, head = 1, tail = 0;
    for(int i = 1; i <= n; i ++)
    {
        int y = in(); y = in();
        if(y == 0)
        {
            head = 1, tail = 0, ans --;
            continue ;
        }
        while(head <= tail && q[tail] > y)
            tail --;
        if(head <= tail && q[tail] == y)
            ans --, tail --;
        q[++ tail] = y;
    }
    printf("%d", ans);
    return 0;
}
