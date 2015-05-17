#ifndef POLYS_H
#define POLYS_H
#include <vector>
#include <string>

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
private:
    //vector<poly> p;
    poly subx,suby;
    void pop(string& s, int& i, double &n, int mode);
    void parse(string& s, vector<poly>& p);
};

#endif // POLYS_H
