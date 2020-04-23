#include	<cstdio>

int main(int argc, char **argv)
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);

    int n;
    scanf("%d", &n);

    if(n == 3)
        puts("0 .. inf");
    else
        puts("unstable");

    return 0;
}
