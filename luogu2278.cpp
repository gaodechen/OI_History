#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <queue>
#include    <vector>

using   namespace   std;
const   int N = 3e5 + 5;
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

struct Item
{
    int num, s, k, rank;

    bool operator < (const Item &b) const
    {
        return rank < b.rank || (rank == b.rank && s > b.s);
    }
};

vector<Item> list;

int main(int argc, char **argv)
{
    int num, s, k, rank, T = 0;
    priority_queue<Item> q;
    while(scanf("%d", &num) == 1)
    {
        s = in(), k = in(), rank = in();
        while(T < s && !q.empty())
        {
            Item x = q.top(); q.pop();
            T = max(T, x.s);
            int d = min(x.k, s - T);
            x.k -= d, T += d;
            if(x.k)
                q.push(x);
            else
                printf("%d %d\n", x.num, T);
        }
        q.push((Item) {num, s, k, rank});
    }
    while(!q.empty())
    {
        Item x = q.top(); q.pop();
        printf("%d %d\n", x.num, T += x.k);
    }
    return 0;
}
