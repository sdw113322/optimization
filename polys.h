#ifndef POLYS_H
#define POLYS_H
#include <vector>
#include <string>

using namespace std;

struct poly{
double c,x,y,z;
};

class Polys
{
public:
    Polys(string input);
    ~Polys();
private:
    vector<poly> p;
    void pop(string& s,int& i,int &n);
    void parse(string& s, vector<poly>& p, int& n);
};

#endif // POLYS_H
