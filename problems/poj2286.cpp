#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;

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

int row[8][7] = {
    { 0,  2,  6, 11, 15, 20, 22},
    { 1,  3,  8, 12, 17, 21, 23},
    {10,  9,  8,  7,  6,  5,  4},
    {19, 18, 17, 16, 15, 14, 13},
};

const int rev[8] = {5, 4, 7, 6, 1, 0, 3, 2};
const int center[8] = {6, 7, 8, 11, 12, 15, 16, 17};

int a[24];

inline bool Judge()
{
    for(int i = 0; i < 8; i ++)
        if(a[center[i]] != a[center[0]]) return false;
    return true;
}

inline int cmp(int target)
{
    int r = 0;
    for(int i = 0; i < 8; i ++)
        if(a[center[i]] != target) r ++;
    return r;
}

inline int h()
{
    return min(cmp(1), min(cmp(2), cmp(3)));
}

inline void Move(int i)
{
    int t = a[row[i][0]];
    for(int j = 0; j < 6; j ++)
        a[row[i][j]] = a[row[i][j + 1]];
    a[row[i][6]] = t;
    return ;
}

char ans[1000];

bool DFS(int d, int limit)
{
    if(Judge())
    {
        ans[d] = '\0', puts(ans);
        return true;
    }
    if(d + h() > limit) return false;
    for(int i = 0; i < 8; i ++)
    {
        ans[d] = 'A' + i, Move(i);
        if(DFS(d + 1, limit)) return true;
        Move(rev[i]);
    }
    return false;
}

int main(int argc, char **argv)
{
    for(int i = 4; i < 8; i ++)
        for(int j = 0; j < 7; j ++)
            row[i][j] = row[rev[i]][6 - j];
    while(scanf("%d", &a[0]) && a[0])
    {
        for(int i = 1; i < 24; i ++) a[i] = in();
        if(Judge()) puts("No moves needed");
        else for(int dep = 0; ; dep ++)
            if(DFS(0, dep)) break ;
        printf("%d\n", a[6]);
    }
    return 0;
}
