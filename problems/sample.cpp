#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <vector>

using namespace	std;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> Pair;
typedef long long data;

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

int main(int argc, char **argv)
{
    return 0;
}
