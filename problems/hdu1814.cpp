#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <vector>

using   namespace   std;
const   int N = 16000;

struct TSat
{
    bool mark[N];
    int n, top, stack[N];
    vector<int> G[N];

    inline void Init(int n)
    {
        this -> n = n;
        for(int i = 0; i < n + n; i ++)
            G[i].clear();
        memset(mark, 0, sizeof(mark));
        return ;
    }

    inline void AddEdge(int x, int y)
    {
        G[x].push_back(y ^ 1);
        G[y].push_back(x ^ 1);
        return ;
    }

    bool DFS(int x)
    {
        if(mark[x^1])
            return false;
        if(mark[x])
            return true;
        mark[x] = true;
        stack[top++] = x;
        for(int i = 0; i < (int) G[x].size(); i ++)
            if(!DFS(G[x][i]))
                return false;
        return true;
    }

    bool Compute()
    {
        for(int i = 0; i < n + n; i += 2)
        {
            if(!mark[i] && !mark[i + 1])
            {
                top = 0;
                if(!DFS(i))
                {
                    while(top > 0)
                        mark[stack[-- top]] = false;
                    if(!DFS(i + 1))
                        return false;
                }
            }
        }
        return true;
    }

    inline void Interface()
    {
        if(!Compute())
            printf("NIE\n");
        else
        {
            for(int i = 0; i < n; i ++)
            {
                if(mark[i+i])
                    printf("%d\n", i + i + 1);
                else
                    printf("%d\n", i + i + 2);
            }
        }
        return ;
    }
} sat;

int main()
{
    int n, m, u, v;
    while(scanf("%d%d", &n, &m) == 2)
    {
        sat.Init(n);
        while(m --)
        {
            scanf("%d%d", &u, &v);
            sat.AddEdge(u - 1, v - 1);
        }
        sat.Interface();
    }
    return 0;
}

