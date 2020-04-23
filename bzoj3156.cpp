#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
typedef long long   data;
const   int N = 1e6 + 5;

data d[N], a[N];
int n, head, tail, q[N];

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

inline double slope(data j, data k)
{
    return double(d[j] - d[k] + (j * j - k * k + j - k) / 2.0) / double(j - k);
}

int main(int argc, char **argv)
{
    n = in();
    for(int i = n - 1; i + 1; i --)
        a[i] = in();
    d[0] = a[0];
    for(int i = 1; i <= n; i ++)
    {
        while(head < tail && slope(q[head+1], q[head]) < i)
            head ++;
        int j = q[head];
        d[i] = d[j] + (data) (i - j) * (i - j - 1) / 2 + a[i];
        while(head < tail && slope(i, q[tail]) < slope(q[tail], q[tail - 1]))
            tail --;
        q[++ tail] = i;
    }
    printf("%lld\n", d[n]);
    return 0;
}
