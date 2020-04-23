#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 1e6 + 5;
const   int M = 1e4 + 5;

char p[M], s[N];
int next[M], T, n, m;

inline void InitNext()
{
    int i = 0, j = -1;
    next[0] = -1;
    while(i < n)
    {
        if(j == -1 || p[i] == p[j])
            next[++ i] = ++ j;
        else
            j = next[j];
    }
    return ;
}

inline int KMP()
{
    int i = 0, j = 0, r = 0;
    while(i < m)
    {
        if(s[i] == p[j] || j == -1)
            i ++, j ++;
        else
            j = next[j];
        if(j == n)
        {
            j = next[j - 1];
            r ++, i --;
        }
    }
    return r;
}

int main()
{
    scanf("%d", &T);
    while(T --)
    {
        scanf("%s%s", p, s);
        n = strlen(p), m = strlen(s);
        InitNext();
        printf("%d\n", KMP());
    }
    return 0;
}
