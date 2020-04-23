#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 4e5 + 5;

char s[N];
int next[N], list[N];

inline void InitNext(int n)
{
    int i = 0, j = -1;
    next[i] = j;
    while(i < n)
    {
        if(j == -1 || s[i] == s[j])
            next[++i] = ++ j;
        else
            j = next[j];
    }
    return ;
}

int main()
{
    while(scanf("%s", s) == 1)
    {
        int n = strlen(s);
        InitNext(n);
        int p = n, k = 0;
        while(p != 0)
        {
            list[k++] = next[p];
            p = next[p];
        }
        for(int i = k - 2; i >= 0; i --)
            printf("%d ", list[i]);
        printf("%d\n", n);
    }
    return 0;
}
