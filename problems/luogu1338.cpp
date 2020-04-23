#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 5e4 + 5;

int a[N], pos[N];

int main(int argc, char **argv)
{
    int n, m, tmp = 0, pos;
    cin >> n >> m;
    if(!m)
    {
        for(int i = 1; i <= n; i ++)
            cout << i << " ";
        return 0;
    }
    for(int i = 1; i <= n; i ++)
        a[i] = i;
    for(int i = 1; i <= n; i ++) {
        if(tmp + i < m) {
            tmp += i;
        } else {
            pos = i; break ;
        }
    }
    int k = n - pos - 1, k_ = k;
    for(int i = 1; i <= k; i ++)
        cout << i << " ";
    for(; tmp <= m; tmp ++) k ++;
    for(int i = n; i > k_; i --)
        if(i != k) cout << i << " ";
    return 0;
}
