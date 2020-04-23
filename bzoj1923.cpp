#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int n, m, M[2001][40];

int main(int argc, char **argv)
{
    scanf("%d%d", &n, &m);

    if(m < n) return puts("Cannot Determine"), 0;

    int P = n / 32, Q = n % 32;

    for(int i = 0, k; i < m; i ++)
    {
        char s[1001];
        scanf("%s%d", s, &k);
        for(int j = 0; j < n; j ++)
            M[i][j / 32] |= (s[j] - '0') << (j % 32);
        M[i][P] |= k << (Q);
    }

    int r = 1;

    for(int i = 0; i < n; i ++)
    {
        int k = r;

        for(int j = i; j < r; j ++)
        {
            if(M[j][i / 32] & (1 << (i % 32)))
            {
                k = j;
                break ;
            }
        }

        if(k == r)
        {
            while(k < m && !(M[k][i / 32] & (1 << i % 32)))
                k ++;
            if(k == m)
                return puts("Cannot Determine"), 0;
            r = k + 1;
        }

        if(k != i)
            for(int j = i / 32; j <= P; j ++)
                swap(M[k][j], M[i][j]);

        for(int j = i + 1; j < m; j ++)
            if(M[j][i / 32] & (1 << i % 32))
                for(k = i / 32; k <= P; k ++)
                    M[j][k] ^= M[i][k];
    }

    printf("%d\n", r);

    for(int i = n - 1; i >= 0; i --)
        for(int j = i + 1; j < n; j ++)
            if(M[i][j / 32] & (1 << j % 32))
                M[i][P] ^= M[j][P];

    for(int i = 0; i < n; i ++)
        puts((M[i][P] & (1 << Q)) ? "?y7M#" : "Earth");

    return 0;
}
