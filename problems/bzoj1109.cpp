#include    <cstdio>
#include    <iostream>
#include    <algorithm>

#define     x       first
#define     y       second

using   namespace   std;
typedef pair<int, int> data;
const   int N = 100001;

inline int in() {
	int k = 0, c = '\0';
	for(; c > '9' || c < '0';) {
		c = getchar();
    }
	for(; c >= '0' && c <= '9';) {
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k;
}

data a[N];
int m, d[N];

inline int BinarySearch(int k) {
    int l = 1, r = m;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(d[mid] >= k)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}

int main() {
    int n = in(), t = 0;
    for(int i = 1; i <= n; i ++) {
        int k = in();
        if(k <= i)
            a[++t].x = i - k, a[t].y = k;
    }
    sort(a + 1, a + t + 1);
    for(int i = 1, p; i <= t; i ++) {
        if(d[m] < a[i].y) {
            p = ++ m;
        } else {
            p = BinarySearch(a[i].y);
        }
        d[p] = a[i].y;
    }
    printf("%d\n", m);
    return 0;
}
