#include	<cstdio>
#include	<cstdlib>
#include	<iostream>
#include    <algorithm>
#include    <ctime>
#include    <set>

using	namespace	std;
const	int N = 100001;

inline int Rand( int l, int r )
{
    return rand() % ( r - l + 1 ) + l;
}

void BuildTree(int n)
{
    int a[100001], pre[100001];
    for(int i = 1; i < n; i ++)
        a[i] = Rand(1, i);
    pre[1] = 1;
    for(int i = 1; i < n; i ++)
        pre[i + 1] = a[i];
    for(int i = 2; i <= n; i ++)
        // printf("%d %d\n", i, pre[i]);
        printf("%d %d %d\n", i, pre[i], Rand(1, 1000));
    return ;
}

int a[N];

int main(int argc, char **argv)
{
    srand(time(NULL));
    int n = 100000, m = 5000;
    cout << n << endl;
    BuildTree(n);
    while(m --)
    {
        int k = Rand(1, 4);
        if(k == 1)
            printf("Change %d %d\n", Rand(1, n - 1), Rand(1, 10000));
        else if(k == 2)
            printf("Cover %d %d %d\n", Rand(1, n), Rand(1, n), Rand(1, 10000));
        else if(k == 3)
            printf("Add %d %d %d\n", Rand(1, n), Rand(1, n), Rand(1, 1000));
        else
        {
            int u = Rand(1, n), v = Rand(1, n);
            while(u == v) v = Rand(1, n);
            printf("Max %d %d\n", Rand(1, n), Rand(1, n));
        }
    }
    puts("Stop");
    return 0;
}

