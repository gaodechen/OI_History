#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;
const int N = 40001;

int n, m, d[N], col[N], pre[N], next[N];
int a[N], L[N], c[N];

int main(int argc, char **argv)
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &a[i]);
    for(int i = 1; i <= n; i ++)
    {
        pre[i] = col[a[i]];
        col[a[i]] = i;
    }
    memset(col, 0, sizeof(col));
    for(int i = n; i >= 1; i --)
    {
        next[i] = col[a[i]];
        col[a[i]] = i;
        if(next[i] == 0)
            next[i] = n + 1;
    }
    for(int i = 1; i <= n; i ++)
        L[i] = 1;
    int K = sqrt(n);
    for(int i = 1; i <= n; i ++)
    {
        for(int j = 1; j <= K; j ++)
        {
            if(pre[i] < L[j])
            {
                if(++ c[j] > j)
                {
                    while(next[L[j]] <= i)
                        L[j] ++;
                    L[j] ++, c[j] --;
                }
            }
            if(d[L[j] - 1] + c[j] * c[j] < d[i] || !d[i])
                d[i] = d[L[j] - 1] + c[j] * c[j];
        }
    }
    printf("%d\n", d[n]);
    return 0;
}
