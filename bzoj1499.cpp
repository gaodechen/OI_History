#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
typedef pair<int, int> data;
const   int INF = 0x3f3f3f3f;
const   int N = 201, M = 40001;

struct Item {int l, r, d;} e[N];

bool a[N][N];
int n, m, k, X, Y, d[N][N][2];

data q[N];
int head, tail, ans;

inline void clear() {head = 1, tail = 0;};

inline void push(int pos, int val)
{
    while(head <= tail && q[tail].second <= val)
        tail --;
    return (void) (q[++tail] = data(pos, val));
}

inline int query(int pos, int lim)
{
    while(head <= tail && pos - q[head].first > lim)
        head ++;
    return q[head].second;
}

inline void Update(int time, int x, int y, int i)
{
    int t = i & 1;
    if(!a[x][y])
        d[x][y][t] = -INF, clear();
    else
    {
        push(time, d[x][y][t ^ 1] - time);
        d[x][y][t] = query(time, e[i].r - e[i].l + 1) + time;
    }
    if(d[x][y][t] > ans)
        ans = d[x][y][t];
    return ;
}

int main(int argc, char **argv)
{
    scanf("%d%d%d%d%d", &n, &m, &X, &Y, &k);
    for(int i = 1; i <= n; i ++)
    {
        char buf[N];
        scanf("%s", buf + 1);
        for(int j = 1; j <= m; j ++)
            a[i][j] = buf[j] == '.';
    }
    for(int i = 1; i <= k; i ++)
        scanf("%d%d%d", &e[i].l, &e[i].r, &e[i].d);
    memset(d, 128, sizeof(d));
    d[X][Y][0] = 0;
    for(int t = 1; t <= k; t ++) {
        if(e[t].d == 1) {
            for(int j = 1; j <= m; j ++) {
                clear();
                for(int i = n; i >= 1; i --)
                    Update(n - i, i, j, t);
            }
        } else if(e[t].d == 2) {
            for(int j = 1; j <= m; j ++) {
                clear();
                for(int i = 1; i <= n; i ++)
                    Update(i, i, j, t);
            }
        } else if(e[t].d == 3) {
            for(int i = 1; i <= n; i ++) {
                clear();
                for(int j = m; j >= 1; j --)
                    Update(m - j, i, j, t);
            }
        } else {
            for(int i = 1; i <= n; i ++) {
                clear();
                for(int j = 1; j <= m; j ++)
                    Update(j, i, j, t);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
