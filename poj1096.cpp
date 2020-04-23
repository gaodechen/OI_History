#include    <cstdio>

const   int N = 1e3 + 5;

int n, s;
double d[N][N];

int main()
{
    scanf("%d%d", &n, &s);
    int ns = n * s;
    for(int i = n; i >= 0; i --)
    {
        for(int j = s; j >= 0; j --)
        {
            if(i == n && j == s)
                continue ;
            d[i][j] = (ns + d[i+1][j] * (n - i) * j + d[i][j+1] * i * (s - j) + d[i+1][j+1] * (n - i) * (s - j)) / (ns - i * j);
        }
    }
    printf("%.4f\n", d[0][0]);
    return 0;
}
