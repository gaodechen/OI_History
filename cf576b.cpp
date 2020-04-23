#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <vector>

using   namespace   std;
const   int N = 1e5 + 5;

bool vis[N];
vector<int> list[N];
int n, t, pos1, pos2, flag, a[N];

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &a[i]);
    for(int i = 1; i <= n; i ++)
    {
        if(vis[i])
            continue ;
        vector<int> &p = list[++t];
        int j = i;
        while(!vis[j])
        {
            p.push_back(j);
            vis[j] = 1;
            j = a[j];
        }
        if(p.size() == 1)
            pos1 = i;
        else if(p.size() == 2)
            pos2 = t;
        else if(p.size() > 2 && (p.size() & 1))
            flag = 1;
    }
    if(pos1)
    {
        puts("YES");
        for(int i = 1; i <= n; i ++)
            if(i != pos1)
                printf("%d %d\n", pos1, i);
        return 0;
    }
    if(flag || !pos2)
    {
        puts("NO");
        return 0;
    }
    puts("YES");
    vector<int> &p = list[pos2];
    printf("%d %d\n", p[0], p[1]);
    for(int i = 1; i <= t; i ++)
    {
        if(i == pos2)
            continue ;
        for(int j = 0, k = 0; j < (int) list[i].size(); j ++, k ^= 1)
            printf("%d %d\n", list[i][j], p[k]);
    }
    return 0;
}
