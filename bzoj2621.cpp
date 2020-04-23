#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>

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

int c[20], Sum[1 << 20], f[1 << 20][20];

int main(int argc, char **argv)
{
    int n = in(), w = in(), m = (1 << n);
    for(int i = 0; i < n; i ++)
        c[i] = in();
    for(int i = 0; i < m; i ++)
        for(int j = 0; j < n; j ++)
            if(i & (1 << j))
                Sum[i] += c[j];
    for(int s = 0; s < m; s ++)
    {
        for(int i = 1; i <= n; i ++)
        {
            int q = 0;
            for(int j = 0; j < n; j ++)
            {
                if(!(s & (1 << j))) continue ;
                int t = s ^ (1 << j);
                q = max(q, f[t][i - 1]);
            }
            if(Sum[s] - q <= w)
                f[s][i] = Sum[s];
        }
    }
    for(int i = 1; i <= n; i ++)
    {
        if(f[m - 1][i])
        {
            printf("%d", i);
            break ;
        }
    }
    return 0;
}
