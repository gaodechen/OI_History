#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 1e6 + 5;

char s[N];
int n, next[N];

inline void InitNext()
{
    int i = 0, j = -1;
    next[0] = -1;
    while(i < n)
    {
        if(j == -1 || s[i] == s[j])
            next[++ i] = ++ j;
        else
            j = next[j];
    }
    return ;
}

int main()
{
    while(scanf("%s", s) == 1)
    {
        if(s[0] == '.')
            break ;
        n = strlen(s);
        InitNext();
        if(n % (n - next[n]) == 0)
            printf("%d\n", n / (n - next[n]));
        else
            printf("%d\n", 1);
    }
    return 0;
}
