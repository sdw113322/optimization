#include "polys.h"
#include <ctype.h>
#include <math.h>

using namespace std;

Polys::Polys(string input)
{
    parse(input,p);
}

Polys::~Polys()
{

}

// 彈出數字
void Polys::pop(string& s, int& i, double &n,int mode){
    bool valid = false;
    if(mode == 0)
        valid = true;
    // 忽略次方符號
    if (s[i] == '^'){
        ++i;
        if(mode == 1)
            valid = true;
    }
    // 忽略乘法符號
    if (s[i] == '*') ++i;
    // 忽略括弧
    if (s[i] == '(') ++i;
    if (s[i] == ')') ++i;
    // 忽略空白
    if (s[i] == ' ') ++i;

    // 數值
    if(valid == true){
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
    }else
        n = 1;
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
        pop(s, i, tmp.c,0);
        tmp.c *= m;

        if (s[i] == '*') ++i;

        // 元與次方
        if (s[i] == 'x') pop(s, ++i, tmp.x,1);
        if (s[i] == '*') ++i;
        if (s[i] == 'y') pop(s, ++i, tmp.y,1);
        if (s[i] == '*') ++i;
        if (s[i] == 'z') pop(s, ++i, tmp.z,1);
        p.push_back(tmp);
    }
}

//求值
double Polys::eval(double x,double y,double z){
    double result = 0;
    for(int i=0;i<p.size();i++){
        double term = 1;
        term *= pow(x,p[i].x);
        term *= pow(y,p[i].y);
        term *= pow(z,p[i].z);
        term *= p[i].c;
        result += term;
    }
    return result;
}

void Polys::createSuber(double xc,double xa,double yc,double ya){
    subx.c = xc;
    subx.x = xa;
    suby.c = yc;
    suby.x = ya;
}

double Polys::evalSuber(double a){
    return eval(subx.c+subx.x*a,suby.c+suby.x*a,0);
}

void Polys::deleteSuber(){
    subx.c = 0;
    subx.x = 0;
    suby.c = 0;
    suby.x = 0;
}

array<double,2> Polys::gradient(double x,double y){
    double h = 0.000001;
    array<double,2> result;
    result[0] = (eval(x+h,y,0)-eval(x-h,y,0))/(2*h);
    result[1] = (eval(x,y+h,0)-eval(x,y-h,0))/(2*h);
    return result;
}

double Polys::dx (double x,double y){
    double h = 0.000001;
    return (eval(x+h,y,0)-eval(x-h,y,0))/(2*h);
}
double Polys::dy (double x,double y){
    double h = 0.000001;
    return (eval(x,y+h,0)-eval(x,y-h,0))/(2*h);
}
double Polys::dxx (double x,double y){
    double h = 0.000001;
    return (dx(x+h,y)-dx(x-h,y))/(2*h);
}
double Polys::dyy (double x,double y){
    double h = 0.000001;
    return (dy(x,y+h)-dy(x,y-h))/(2*h);
}
double Polys::dxy (double x,double y){
    double h = 0.000001;
    return (dx(x,y+h)-dx(x,y-h))/(2*h);
}
double Polys::dyx (double x,double y){
    double h = 0.000001;
    return (dy(x+h,y)-dy(x-h,y))/(2*h);
}

array<array<double,2>,2> Polys::hessian(double x,double y){
    double h = 0.001;
    array<array<double,2>,2> result;

    result[0][0] = dxx(x,y);
    result[0][1] = dxy(x,y);
    result[1][0] = dyx(x,y);
    result[1][1] = dyy(x,y);
    return result;
}
