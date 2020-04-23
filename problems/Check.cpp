#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

const int SIZE = 1024;

inline void Compile(string FileName)
{
    string temp = "g++ -o " + FileName + ".exe " + FileName + ".cpp";
    return (void) (system(temp.c_str()));
}

int main(int argc, char **argv)
{
    string FileName;
    // cin >> FileName;
    FileName = "bzoj1984";

    Compile("DataMaker");
    Compile("std");
    Compile(FileName);

    bool flag = true;

    while(flag)
    {
        string temp = FileName + ".exe < in > my.out";
        system("DataMaker.exe > in");
        system("std.exe < in > std.out");
        system(temp.c_str());

        fstream MyBuf("my.out");
        fstream StdBuf("std.out");

        while(!MyBuf.eof())
        {
            int MyVar, StdVar;
            MyBuf >> MyVar, StdBuf >> StdVar;
            if(MyVar != StdVar)
            {
                flag = false, puts("WA");
                break ;
            }
        }
        
        if(flag) puts("AC");
        else break ;
    }

    return 0;
}
