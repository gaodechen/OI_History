#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 61;

bool vis[N];
int n, tmp, ans, sum, a[N], pre[N];

void DFS( int p, int ind, int len )
{
    if( ind && ind == sum / tmp && sum % tmp == 0 )
        ans = tmp;
    int q = -1;
    if( pre[n] - pre[p-1] < tmp - len )
        return ;
    else for( int i = p; i <= n; i ++ )
    {
        if(vis[i] || len + a[i] > tmp || q == a[i])
            continue ;
        vis[i] = 1;
        if( len + a[i] == tmp )
            DFS(1, ind + 1, 0);
        else
            DFS(i + 1, ind, len + a[i]);
        q = a[i];
        vis[i] = 0;
        if( ans || !len )
            break ;
    }
    return ;
}

int main()
{
    scanf( "%d", &tmp );
    for( int i = 1, l; i <= tmp; i ++ )
    {
        scanf( "%d", &l );
        if( l > 50 )
            continue ;
        a[++n] = l, sum += l;
    }
    sort( a + 1, a + n + 1, greater< int >() );
    for( int i = 1; i <= n; i ++ )
        pre[i] = pre[i-1] + a[i];
    for( int i = a[1]; i <= sum; i ++ )
    {
        if( sum % i == 0 )
        {
            tmp = i;
            DFS( 1, 0, 0 );
            if( ans )
                break ;
        }
    }
    printf( "%d\n", ans );
    return 0;
}
