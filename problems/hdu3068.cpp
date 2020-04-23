#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 110001;

char S[N], s[N];
int f[N + N];

int main(int argc, char **argv)
{
    while(scanf("%s", S) == 1)
    {
        memset(f, 0, sizeof(f));
        int n = strlen(S);
        s[0] = '$', s[1] = '#';
        for(int i = 0; i < n; i ++)
            s[i + i + 2] = S[i], s[i + i + 3] = '#';
        f[0] = 1, n = n + n + 2;
        int mid = 0, side = 0;
        for(int i = 1; i < n; i ++)
        {
            if(side > i)
                f[i] = min(f[2 * mid - i], side - i);
            else
                f[i] = 1;
            while(s[i - f[i]] == s[i + f[i]])
                f[i] ++;
            if(i + f[i] > side)
                side = i + f[i], mid = i;
        }
        int r = 0;
        for(int i = 1; i < n; i ++)
            r = max(f[i] - 1, r);
        printf("%d\n", r);
    }
    return 0;
}
