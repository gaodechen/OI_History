#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 1e6 + 5;

struct Item
{
    int k, next;
} e[N];

char a[N], b[N];
int n, tot, head[26], w[N], node[N];

inline int lowbit( int x )
{
    return x & ( -x );
}

inline void Insert( int p )
{
    for( ; p <= n; p += lowbit( p ) )
        node[p] += 1;
    return ;
}

inline int Query( int p )
{
    int sum = 0;
    for( ; p; p -= lowbit( p ) )
        sum += node[p];
    return sum;
}

int main()
{
    scanf( "%d%s%s", &n, a, b );
    for( int i = 0; i < n; i ++ )
    {
        int c = a[i] - 'A';
        e[++tot].next = head[c];
        e[tot].k = i + 1, head[c] = tot;
    }
    for( int i = n - 1; i + 1; i -- )
    {
        int c = b[i] - 'A';
        w[i] = e[head[c]].k;
        head[c] = e[head[c]].next;
    }
    long long sum = 0;
    for( int i = 0; i < n; i ++ )
    {
        int k = w[i];
        sum += Query( n ) - Query( k );
        Insert( k );
    }
    printf( "%lld\n", sum );
    return 0;
}
