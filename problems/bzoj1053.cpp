#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
typedef long long   data;

int n, ans, tik, q = 10;
int prime[15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void DFS(int k, int num, int cnt, int lim)
{
    if((num > ans && cnt > tik) || (num <= ans && cnt >= tik))
        ans = num, tik = cnt;
    for(int i = 1; i <= lim; i ++)
    {
        data tmp = (data) num * prime[k];
        if(tmp > n)
            break ;
        DFS(k + 1, num *= prime[k], cnt * (i + 1), i);
    }
    return ;
}

int main()
{
    scanf("%d", &n);
    DFS(0, 1, 1, 20);
    printf("%d", ans);
    return 0;
}
