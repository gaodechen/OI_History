#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
typedef long long data;

int main(int argc, char **argv)
{
    data n, m;
    cin >> m >> n;
    data ans = n * m;
    if(n >= m)
    {
        for(data i = 1, p; i <= m; i = p + 1)
        {
            p = min(m, n / (n / i)); data t = n / i;
            ans -= (i + p) * (p - i + 1) / 2 * t;
        }
        cout << ans << endl;
        return 0;
    }
    for(data i = 1, p; i <= n; i = p + 1)
    {
        p = n / (n / i); data t = n / i;
        ans -= (i + p) * (p - i + 1) * t / 2;
    }
    cout << ans << endl;
    return 0;
}
