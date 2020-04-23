#include    <cstdio>
#include    <iostream>

using   namespace   std;

/* const   int N = 21;

   int n = N - 1;
   bool win[N][N];

   int main()
   {
   for(int i = 1; i <= n; i ++)
   for(int j = 1; j < i; j ++)
   for(int k = i - j; k >= 0; k -= j)
   if(!win[j][k]) win[i][j] = 1;
   for(int i = 1; i <= n; i ++)
   for(int j = 1; j < i; j ++)
   win[j][i] = win[i][j];
   for(int i = 1; i <= n; i ++)
   {
   for(int j = 1; j <= n; j ++)
   cout << win[i][j] << " ";
   cout << endl;
   }
   return 0;
   } */

bool Win(int x, int y)
{
    if(x < y) swap(x ,y);
    if(x == y || x >= y + y)
        return true;
    return !Win(y, x - y);
}

int main(int argc, char **argv)
{
    int T, n, m;
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d%d", &n, &m);
        if(Win(n, m))
            printf("Stan wins\n");
        else
            printf("Ollie wins\n");
    }
    return 0;
}
