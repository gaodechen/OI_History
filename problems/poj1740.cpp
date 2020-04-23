#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 1e3 + 1;

int n;
bool cnt[N];

int main()
{
    while(scanf("%d", &n) && n)
    {
        memset(cnt, 0, sizeof(cnt));
        for(int i = 1, a; i <= n; i ++)
        {
            scanf("%d", &a);
            cnt[a] ^= 1;
        }
        bool flag = 0;
        for(int i = 1; i < N; i ++)
            if(cnt[i])
                flag = 1;
        printf("%d\n", flag);
    }
    return 0;
}
