#include    <cstdio>
#include    <iostream>
#include    <vector>

using   namespace   std;

int main(int argc, char **argv)
{
    int n, k = 1;
    vector<int> list;
    scanf("%d", &n);
    while(n >= k)
    {
        list.push_back(k);
        n -= k, k <<= 1;
    }
    if(n > 0)
    {
        if(n == list[list.size() - 1] && n != 1)
            list[list.size() - 1] --, n ++;
        list.push_back(n);
    }
    cout << list.size() << endl;
    for(int i = 0; i < (int) list.size(); i ++)
        cout << list[i] << " ";
    return 0;
}
