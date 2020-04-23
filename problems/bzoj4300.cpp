#include    <cstdio>

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

int f[32];

int main()
{
    int n = in(), ans = 0;
    while(n --)
    {
        int a = in(), t = 0;
        for(int i = 0; i < 31; i ++)
            if(a & (1 << i) && t < f[i] + 1)
                t = f[i] + 1;
        for(int i = 0; i < 31; i ++)
            if(a & (1 << i) && f[i] < t)
                f[i] = t;
        if(t > ans) ans = t;
    }
    printf("%d\n", ans);
    return 0;
}
