#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 4001, M = 201;

int K, next[M], len[N];
char S[N][M], buf[M];

inline void InitNext(char *s, int n)
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

inline int KMP(char *p, char *s, int n, int m)
{
    int r = 0, i = 0, j = 0;
    while(j < n && i < m)
    {
        if(j == -1 || s[i] == p[j])
            i ++, j ++;
        else
            j = next[j];
        r = max(r, j);
    }
    return r;
}

int main()
{
    while(scanf("%d", &K) == 1 && K)
    {
        int p = 0, ans = 0;
        for(int i = 0; i < K; i ++)
        {
            scanf("%s", S[i]);
            if(strlen(S[i]) < strlen(S[p]))
                p = i;
        }
        swap(S[p], S[0]);
        for(int i = 0; i < K; i ++)
            len[i] = strlen(S[i]);
        for(int i = 0; i < len[0]; i ++)
        {
            InitNext(S[0] + i, len[0] - i);
            int l = 0x3f3f3f3f;
            for(int j = 1; j < K; j ++)
            {
                int tmp = KMP(S[0] + i, S[j], len[0] - i, len[j]);
                l = min(tmp, l);
               if(!l) break ;
            }
            if(l > ans)
            {
                strncpy(buf, S[0] + i, ans = l);
                buf[l] = '\0';
            }
            else if(l == ans && l)
            {
                char tmp[M];
                strncpy(tmp, S[0] + i, l);
                tmp[l] = '\0';
                if(strcmp(tmp, buf) < 0)
                    strcpy(buf, tmp);
            }
        }
        if(ans == 0)
            puts("IDENTITY LOST");
        else
            puts(buf);
    }
    return 0;
}
