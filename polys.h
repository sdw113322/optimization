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
private:
    //vector<poly> p;
    void pop(string& s,int& i,double &n);
    void parse(string& s, vector<poly>& p);
};

#endif // POLYS_H
