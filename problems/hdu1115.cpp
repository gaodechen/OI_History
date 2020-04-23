#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int N = 1e6 + 5;

int T, n;
double x[N], y[N];

int main(int argc, char **argv)
{
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d", &n);
        for(int i = 0; i < n; i ++)
            scanf("%lf%lf", &x[i], &y[i]);
        double X = 0, Y = 0, M = 0;
        for(int i = 1; i < n; i ++)
        {
            double m = x[i - 1] * y[i] - x[i] * y[i - 1];
            X += (x[i] + x[i - 1]) * m;
            Y += (y[i] + y[i - 1]) * m;
            M += m;
        }
        double m = x[n - 1] * y[0] - x[0] * y[n - 1];
        X += (x[0] + x[n - 1]) * m;
        Y += (y[0] + y[n - 1]) * m;
        M += m;
        printf("%.2lf %.2lf\n", X / (3 * M), Y / (3 * M));
    }
    return 0;
}
