#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 2e4 + 5;
const   int INF = 0x3f3f3f3f;

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

int n, used[N];
struct Point {int x, y;} e[N];

void Update(int &Xmin, int &Ymin, int &Xmax, int &Ymax)
{
    Xmin = Ymin = INF, Xmax = Ymax = -INF;
    for(int i = 1; i <= n; i ++)
    {
        if(used[i]) continue ;
        if(e[i].x < Xmin) Xmin = e[i].x;
        if(e[i].x > Xmax) Xmax = e[i].x;
        if(e[i].y < Ymin) Ymin = e[i].y;
        if(e[i].y > Ymax) Ymax = e[i].y;
    }
    return ;
}

inline bool f(int x, int l, int r) {return x >= l && x <= r;}

inline bool DFS(int dep, int l)
{
    int Xmin, Ymin, Xmax, Ymax;
    Update(Xmin, Ymin, Xmax, Ymax);

    if(Xmin == INF)
        return true;
    if(dep == 3)
        return max(Xmax - Xmin, Ymax - Ymin) <= l;

    // Xmin, Ymin
    for(int i = 1; i <= n; i ++)
        if(!used[i] && f(e[i].x, Xmin, Xmin + l) && f(e[i].y, Ymin, Ymin + l))
            used[i] = dep;
    if(DFS(dep + 1, l)) return true;
    for(int i = 1; i <= n; i ++) if(used[i] == dep) used[i] = 0;

    // Xmax, Ymin
    for(int i = 1; i <= n; i ++)
        if(!used[i] && f(e[i].x, Xmax - l, Xmax) && f(e[i].y, Ymin, Ymin + l))
            used[i] = dep;
    if(DFS(dep + 1, l)) return true;
    for(int i = 1; i <= n; i ++) if(used[i] == dep) used[i] = 0;

    // Xmin, Ymax
    for(int i = 1; i <= n; i ++)
        if(!used[i] && f(e[i].x, Xmin, Xmin + l) && f(e[i].y, Ymax - l, Ymax))
            used[i] = dep;
    if(DFS(dep + 1, l)) return true;
    for(int i = 1; i <= n; i ++) if(used[i] == dep) used[i] = 0;

    // Xmax, Ymax
    for(int i = 1; i <= n; i ++)
        if(!used[i] && f(e[i].x, Xmax - l, Xmax) && f(e[i].y, Ymax - l, Ymax))
            used[i] = dep;
    if(DFS(dep + 1, l)) return true;
    for(int i = 1; i <= n; i ++) if(used[i] == dep) used[i] = 0;

    return false;
}

inline bool Check(int l)
{
    memset(used, 0, sizeof(used));
    return DFS(1, l);
}

int main(int argc, char **argv)
{
    n = in();
    for(int i = 1; i <= n; i ++)
        e[i].x = in(), e[i].y = in();
    int Xmin, Ymin, Xmax, Ymax;
    Update(Xmin, Ymin, Xmax, Ymax);
    int l = 0, r = max(Xmax - Xmin, Ymax - Ymin);
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(Check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", l);
    return 0;
}
