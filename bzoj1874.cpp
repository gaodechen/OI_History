#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int M = 10, N = 1001;

bool mark[N];
int n, m, a[M], b[M], sg[N];

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        scanf("%d", &a[i]); scanf("%d", &m);
    for(int i = 0; i < m; i ++)
        scanf("%d", &b[i]);
    for(int i = 1; i < N; i ++)
    {
        memset(mark, 0, sizeof(mark));
        for(int j = 0; j < m; j ++)
            if(i - b[j] >= 0)
                mark[sg[i-b[j]]] = 1;
        for(int j = 0; j <= 10; j ++)
        {
            if(!mark[j])
            {
                sg[i] = j;
                break ;
            }
        }
    }
    int sum = 0;
    for(int i = 0; i < n; i ++)
        sum ^= sg[a[i]];
    if(sum == 0)
        puts("NO");
    else
    {
        puts("YES");
        for(int i = 0; i < n; i ++)
        {
            for(int j = 0; j < m; j ++)
            {
                if(sg[a[i]-b[j]] == (sum ^ sg[a[i]]))
                {
                    printf("%d %d\n", i + 1, b[j]);
                    return 0;
                }
            }
        }
    }
    return 0;
}
