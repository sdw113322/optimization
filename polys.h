#ifndef POLYS_H
#define POLYS_H
#include <vector>
#include <string>
#include <array>

using namespace std;

struct poly{
double c,x,y,z;
poly(){
    c = 0;
    x = 0;
    y = 0;
    z = 0;
}
};

class Polys
{
public:
    Polys(string input);
    ~Polys();
    vector<poly> p;
    double eval(double x,double y,double z);
    //suber: 將有兩個未知數的式子以特定的式子(ak+b)帶入至x,y中以變為一個未知數的函數
    void createSuber(double xc,double xa,double yc,double ya);
    double evalSuber(double a);
    void deleteSuber();
    array<double,2> gradient(double x,double y);
    array<array<double,2>,2> hessian(double x,double y);
    double dx (double x,double y);
    double dy (double x,double y);
    double dxx (double x,double y);
    double dxy (double x,double y);
    double dyx (double x,double y);
    double dyy (double x,double y);
private:
    //vector<poly> p;
    poly subx,suby;
    void pop(string& s, int& i, double &n, int mode);
    void parse(string& s, vector<poly>& p);
};

#endif // POLYS_H
