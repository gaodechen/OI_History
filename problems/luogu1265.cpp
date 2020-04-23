#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <cmath>
#include    <queue>

using   namespace   std;
const   int N = 5e3 + 5;

struct Point
{
    double x, y;
} p[N];

struct Item
{
    int v;
    double d;

    Item( int v, double d ): v( v ), d( d )
    {
    }

    bool operator < ( const Item &b ) const
    {
        return d > b.d;
    }
} ;

inline double Distance( const Point &a, const Point &b )
{
    double d1 = a.x - b.x;
    double d2 = a.y - b.y;
    return sqrt( d1 * d1 + d2 * d2 );
}

int n;
priority_queue< Edge > q[N];

int main()
{
    freopen( "a.in", "r", stdin );
    scanf( "%d", &n );
    for( int i = 1; i <= n; i ++ )
        cin >> p[i].x >> p[i].y;
    for( int i = 1; i <= n; i ++ )
        for( int j = 1; j <= n; j ++ )
            q.push( Item( j, Distance( p[i], p[j] ) );
    return 0;
}
