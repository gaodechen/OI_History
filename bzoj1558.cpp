#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using namespace	std;
const int INF = 0x3f3f3f3f;

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

const int N = 100005;

int a[N];

struct SegmentTree
{
    typedef SegmentTree Node;

    Node *lson, *rson;

    inline Node *NewNode()
    {
        static Node pool[N + N], *T = pool;
        return T ++;
    }

    inline void Update()
    {
        cnt = lson -> cnt + rson -> cnt;
        return ;
    }

    void BuildTree(int l, int r)
    {
        if(l == r)
        {
        }
        int mid = (l + r) >> 1;
        (lson = NewNode()) -> BuildTree(l, mid);
        (rson = NewNode()) -> BuildTree(mid + 1, r);
        return (void) (Update());
    }
} *seg;

int main(int argc, char **argv)
{
    int n = in();
    for(int i = 1; i <= n; i ++)
        a[i] = in();
    int Q = in();
    while(Q --)
    {
        char cmd[2];
        scanf("%s", cmd);
        if(cmd[0] == 'A')
        {
            int l = in(), r = in(), a = in(), b = in();
        }
        else
        {
            int l = in(), r = in();
        }
    }
    return 0;
}
