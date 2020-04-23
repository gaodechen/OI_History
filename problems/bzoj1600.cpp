#include    <cstdio>

int n, f[5][2501];

int main() {
    f[0][0] = 1;
    scanf("%d", &n);
    int t = (n + 1) / 2 - 1;
    for(int i = 1; i <= 4; i ++) {
        for(int j = 1; j <= n; j ++) {
            for(int k = 1; k <= t && k <= j; k ++)
            f[i][j] += f[i-1][j-k];
        }
    }
    printf("%d\n", f[4][n]);
    return 0;
}
