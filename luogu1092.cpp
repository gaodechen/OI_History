#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 27;

bool used[N];
int n, q[N], ans[N], a[N], b[N], c[N];

inline int mod(int x, int mod)
{
    if(x < mod)
        return x;
    return x - mod;
}

inline bool Check()
{
    bool flag = true;
    for(int i = n - 1; i >= 0; i --)
    {
        if(q[a[i]] != -1 && q[b[i]] != -1 && q[c[i]] != -1)
        {
            int t = q[a[i]] + q[b[i]];
            if(mod(t, n) != q[c[i]] && mod(t + 1, n) != q[c[i]] && i != n - 1)
            {
                flag = false;
                break ;
            }
        }
    }
    return flag;
}

void DFS(int m, int x)
{
    bool flag = true;
    for(int i = n - 1, r = 0; i >= 0; i --) {
        if(q[a[i]] != -1 && q[b[i]] != -1 && q[c[i]] != -1) {
            if(mod(q[a[i]] + q[b[i]] + r, n) != q[c[i]]) {
                flag = false;
                break ;
            }
            r = (q[a[i]] + q[b[i]] + r) >= n;
        }
        else {
            flag = false;
            break ;
        }
    }
    if(m == -1) {
        if(flag)
            for(int i = 0; i < n; i ++)
                ans[i] = q[i];
        return ;
    }
    if(x == 0) {
        if(q[a[m]] == -1) {
            for(int i = n - 1; i >= 0; i --) {
                if(!used[i]) {
                    used[i] = 1, q[a[m]] = i;
                    if(Check())
                        DFS(m, 1);
                    used[i] = 0, q[a[m]] = -1;
                    if(ans[0] != -1)
                        return ;
                }
            }
        } else
            DFS(m, 1);
    } else if(x == 1) {
        if(q[b[m]] == -1) {
            for(int i = n - 1; i >= 0; i --) {
                if(!used[i]) {
                    used[i] = 1, q[b[m]] = i;
                    int t = q[a[m]] + q[b[m]];
                    if(q[c[m]] != -1) {
                        if(mod(t, n) == q[c[m]] || (mod(t + 1, n) == q[c[m]] && m != n - 1)) {
                            if(Check())
                                DFS(m - 1, 0);
                            if(ans[0] != -1)
                                return ;
                        }
                    } else
                        DFS(m, 2);
                    used[i] = 0, q[b[m]] = -1;
                }
            }
        } else
            DFS(m, 2);
    } else {
        if(q[c[m]] == -1) {
            int t = mod(q[a[m]] + q[b[m]], n);
            if(!used[t]) {
                q[c[m]] = t, used[t] = 1;
                if(Check())
                    DFS(m - 1, 0);
                used[t] = 0, q[c[m]] = -1;
                if(ans[0] != -1)
                    return ;
            }
            t = mod(t + 1, n);
            if(!used[t] && m != n - 1)
            {
                q[c[m]] = t, used[t] = 1;
                if(Check())
                    DFS(m - 1, 0);
                used[t] = 0, q[c[m]] = -1;
                if(ans[0] != -1)
                    return ;
            }
        } else
            DFS(m - 1, 0);
    }
    return ;
}

int main(int argc, char **argv) {
    char s1[N], s2[N], s[N];
    memset(q, -1, sizeof(q));
    memset(ans, -1, sizeof(ans));
    scanf("%d%s%s%s", &n, s1, s2, s);
    for(int i = 0; i < n; i ++)
        a[i] = s1[i] - 'A';
    for(int i = 0; i < n; i ++)
        b[i] = s2[i] - 'A';
    for(int i = 0; i < n; i ++)
        c[i] = s[i] - 'A';
    DFS(n - 1, 0);
    for(int i = 0; i < n; i ++)
        cout << ans[i] << " ";
    return 0;
}
