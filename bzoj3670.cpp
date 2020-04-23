#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 1e6 + 5;
const   int MOD = 1e9 + 7;

long long ans;
int T, n, next[N], cnt[N];
char s[N];

inline void InitNext()
{
    int i = 0, j = -1;
    next[i] = j;
    while(i < n)
    {
        if(j == -1 || s[i] == s[j])
        {
            next[++ i] = ++ j;
            cnt[i] = cnt[next[i]] + 1;
        }
        else
            j = next[j];
    }
    i = 0, j = -1;
    while(i < n)
    {
        if(j == -1 || s[i] == s[j])
        {
            i ++, j ++;
            if(j > (i >> 1))
                j = next[j];
            // cnt[j]!
            ans *= cnt[j] + 1;
            if(ans >= MOD) ans %= MOD;
        }
        else
            j = next[j];
    }
    return ;
}

int main(int argc, char **argv)
{
    scanf("%d", &T);
    while(T --)
    {
        scanf("%s", s);
        n = strlen(s), ans = 1;
        InitNext();
        printf("%lld\n", ans);
    }
    return 0;
}
