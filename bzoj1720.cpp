#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <set>
#include    <map>
#include    <queue>
#include    <vector>

#define     set(p, k)       memset(p, k, sizeof(p))
#define     cpy(p, q)       memcpy(p, q, sizeof(q))
#define     rep(i, n)       for(int i = 1; i <= n; i ++)

using   namespace   std;
const   int INF = 0x3f3f3f3f;

inline int in()
{
    int k = 0, c = '\0';
    for(; c > '9' || c < '0';)
        c = getchar();
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return k;
}

const   int N = 501;

struct Item {int x, y;} p[N];

int a[N][N], R, C, n, c;
set<int> X, Y;
vector<int> posX, posY;
map<int, int> mapX, mapY;

#define Find(V, k) upper_bound(V.begin(), V.end(), k)

inline bool Judge(int k)
{
    for(int i = 1; i <= R; i ++)
    {
        for(int j = 1; j <= C; j ++)
        {
            int x = Find(posX, posX[i - 1] + k - 1) - posX.begin();
            int y = Find(posY, posY[j - 1] + k - 1) - posY.begin();
            if(a[x][y] - a[x][j - 1] - a[i - 1][y] + a[i - 1][j - 1] >= c)
                return true;
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    c = in(), n = in();
    for(int i = 0; i < n; i ++)
    {
        p[i].x = in(), p[i].y = in();
        X.insert(p[i].x), Y.insert(p[i].y);
    }
    set<int>::iterator P;
    for(P = X.begin(); P != X.end(); P ++)
        posX.push_back(*P);
    for(P = Y.begin(); P != Y.end(); P ++)
        posY.push_back(*P);
    for(int i = 0; i < (int) posX.size(); i ++)
        mapX[posX[i]] = i + 1;
    for(int i = 0; i < (int) posY.size(); i ++)
        mapY[posY[i]] = i + 1;
    for(int i = 0; i < n; i ++)
        a[mapX[p[i].x]][mapY[p[i].y]] ++;
    R = posX.size(), C = posY.size();
    int T = max(R, C);
    for(int i = 1; i <= T; i ++)
        for(int j = 1; j <= T; j ++)
            a[i][j] += a[i][j - 1];
    for(int j = 1; j <= T; j ++)
        for(int i = 1; i <= T; i ++)
            a[i][j] += a[i - 1][j];
    int l = 1, r = 10001;
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(Judge(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%d\n", l);
    return 0;
}
