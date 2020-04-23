#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <vector>

using namespace std;
typedef unsigned long long data;

char buf[1 << 15], *S = buf, *T = buf;
#define GetChar() (S == T && (T = (S = buf) + fread(buf, 1, 1 << 15, stdin), S == T) ? 0 : *S ++)

inline int in()
{
    int k = 0, c = '\0';
    for(; c > '9' || c < '0';)
        c = GetChar();
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = GetChar();
    }
    return k;
}

int n, Q, w[N];
vector<int> E[N];

int main(int argc, char **argv)
{
    n = in();
    for(int v = 2; v <= n; v ++)
        E[in()].push_back(v);
    for(int i = 1; i <= n; i ++)
        w[i] = in();
    DFS(1);
    Q = in();
    while(Q --)
    {
        char s[2];
        if(s[0] == 'F')
        {
        }
    }
    return 0;
}
