#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

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

const char A[] = "Stannis";
const char B[] = "Daenerys";

int main(int argc, char **argv)
{
    int n = in(), k = in(), Count0, Count1 = 0;
    for(int i = 1; i <= n; i ++)
        Count1 += in() & 1;
    Count0 = n - Count1;
    if(n == k) return puts(Count1 & 1 ? A : B), 0;
    int stepB = (n - k) / 2, stepA = n - k - stepB;
    if(stepB >= Count1) return puts(B), 0;
    if(stepA == stepB)
    {
        if(stepA >= Count0 && k & 1) return puts(A), 0;
        return puts(B), 0;
    }
    if(stepB >= Count0) return puts((k + 1) & 1 ? B : A), 0;
    return puts(A), 0;
}

