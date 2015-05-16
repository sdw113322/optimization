#include "polys.h"
#include <ctype.h>

using namespace std;

Polys::Polys(string input)
{
    parse(input,p);
}

Polys::~Polys()
{

}

// 彈出數字
void Polys::pop(string& s, int& i, double &n){
    // 忽略次方符號
    if (s[i] == '^') ++i;
    // 忽略乘法符號
    if (s[i] == '*') ++i;
    // 忽略括弧
    if (s[i] == '(') ++i;
    if (s[i] == ')') ++i;
    // 忽略空白
    if (s[i] == ' ') ++i;

    // 數值
    n = 0;
    int m = 1;
    bool digit = false;
    unsigned int start,end;
    if(s[i]=='-'){
        m = -1;
        i++;
    }
    if(isdigit(s[i])){
        digit = true;
        start = i;
        for (; (isdigit(s[i])||s[i]=='.')&&i<(s.size()-1); ++i){}
        end = i-1;
        if(i==(s.size()-1))
            end = i;
        n = stod(s.substr(start,end-start+1));
        n = n * m;
    }
    if (n == 0 && !digit) n = 1;
}

void Polys::parse(string &s, vector<poly> &p){
    int n = 0;
    for (int i=0; i<s.size()-1; ++n)
    {
        poly tmp;
        // 正負號
        int m = 1;
        if (s[i] == '+') m = +1, ++i;
        if (s[i] == '-') m = -1, ++i;

        // 係數
        pop(s, i, tmp.c);
        tmp.c *= m;

        if (s[i] == '*') ++i;

        // 元與次方
        if (s[i] == 'x') pop(s, ++i, tmp.x);
        if (s[i] == '*') ++i;
        if (s[i] == 'y') pop(s, ++i, tmp.y);
        if (s[i] == '*') ++i;
        if (s[i] == 'z') pop(s, ++i, tmp.z);
        p.push_back(tmp);
    }
}
