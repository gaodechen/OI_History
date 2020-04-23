#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 1e5 + 5;

inline int in()
{
    int k = 0, c = '\0', f = 1;
    for(; c > '9' || c < '0';)
        if((c = getchar()) == '-')
            f = 0;
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return f ? k : -k;
}

int X[N], Y[N], W[N];
int sumW[N], sumD[N], disO[N];
int f[N], q[N];

inline int DIS(int i, int j) {
    return abs(X[i] - X[j]) + abs(Y[i] - Y[j]);
}

inline int F(int j) {
    return f[j] + disO[j + 1] - sumD[j + 1];
}

int main(int argc, char **argv)
{
    int T = in(), C, n;
    while(T --)
    {
        C = in(), n = in();
        for(int i = 1; i <= n; i ++)
            X[i] = in(), Y[i] = in(), W[i] = in();
        for(int i = 1; i <= n; i ++)
        {
            sumW[i] = W[i] + sumW[i - 1];
            sumD[i] = DIS(i, i - 1) + sumD[i - 1];
            disO[i] = DIS(i, 0);
        }
        memset(f, 0x3f, sizeof(f)), f[0] = 0;
        int head = 1, tail = 0;
        q[++ tail] = 0;
        for(int i = 1; i <= n; i ++)
        {
            // The next two steps shouldn't be reversed ...
            while(head <= tail && sumW[i] - sumW[q[head]] > C)
                head ++;
            f[i] = F(q[head]) + sumD[i] + disO[i];
            while(head <= tail && F(i) < F(q[tail]))
                tail --;
            q[++ tail] = i;
        }
        printf("%d\n", f[n]);
        if(T) puts("");
    }
    return 0;
}
