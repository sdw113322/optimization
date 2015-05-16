#include "polys.h"

Polys::Polys(string input)
{

}

Polys::~Polys()
{

}

// 彈出數字
Polys::pop(string& s,int& i,int &n){
    // 忽略次方符號
    if (s[i] == '^') ++i;

    // 數值
    n = 0;
    bool digit = false;
    for (; isdigit(s[i]); ++i)
    {
        n = n * 10 + s[i] - '0';
        digit = true;
    }
    if (n == 0 && !digit) n = 1;
}

Polys::parse(string &s, vector<poly> &p, int &n){
    n = 0;
    for (int i=0; i<s.size(); ++n)
    {
        // 正負號
        int m = 1;
        if (s[i] == '+') m = +1, ++i;
        if (s[i] == '-') m = -1, ++i;

        // 係數
        pop(s, i, p[N].c);
        p[N].c *= m;

        // 元與次方
        if (s[i] == 'x') pop(s, ++i, p[N].x);
        if (s[i] == 'y') pop(s, ++i, p[N].y);
        if (s[i] == 'z') pop(s, ++i, p[N].z);
    }
}
