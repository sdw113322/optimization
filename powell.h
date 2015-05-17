#ifndef POWELL
#define POWELL

#include "polys.h"
#include <deque>
#include <array>
#include <vector>
#include <math.h>
#include <stdio.h>

using namespace std;

vector<array<double,8> > powell(Polys& p,double x,double y,double x_max,double x_min,double y_max,double y_min,double tau);
double goldenp(Polys& p,double a, double b, double c, double tau);

vector<array<double,8> > powell(Polys& p,double x,double y,double x_max,double x_min,double y_max,double y_min,double tau){
    //record
    vector<array<double,8> > record;
    //direction
    deque<array<double,2> > u;
    //initialization
    array<double,2> e1 = {1,0};
    array<double,2> e2 = {0,1};
    u.push_back(e1);
    u.push_back(e2);

    //evaluation
    double fv = p.eval(x,y,0);
    double a[3];

    {
        array<double,8> record_tmp;
        record_tmp[0] = 0;
        record_tmp[1] = 0;
        record_tmp[2] = 0;
        record_tmp[3] = 0;
        record_tmp[4] = 0;
        record_tmp[5] = x;
        record_tmp[6] = y;
        record_tmp[7] = fv;
        record.push_back(record_tmp);
    }

    int i=0;
    double before[3];

    do{
        before[0] = fv;
        before[1] = x;
        before[2] = y;
        for(int j=0;j<3;j++){
            if(j==2){
                array<double,2> u3;
                u3[0] = a[0]*u[0][0]+a[1]*u[0][1];
                u3[1] = a[0]*u[1][0]+a[1]*u[1][1];
                u.push_back(u3);
            }
            //record
            array<double,8> record_tmp;
            record_tmp[0] = i;
            record_tmp[1] = j;
            record_tmp[2] = u[j][0];
            record_tmp[3] = u[j][1];
            //bound
            double acand[4];
            deque<double> acand2;
            double amax,amin;
            acand[0] = (x_max - x)/u[j][0]; //a_x_max
            acand[1] = (x_min - x)/u[j][0]; //a_x_min
            acand[2] = (y_max - y)/u[j][1]; //a_y_max
            acand[3] = (y_min - y)/u[j][1]; //a_y_min
            for(int k=0;k<2;k++){
                if(y+acand[k]*u[j][1]<y_max && y+acand[k]*u[j][1]>y_min){
                    acand2.push_back(acand[k]);
                }
                if(x+acand[k+2]*u[j][0]<x_max && x+acand[k+2]*u[j][0]>x_min){
                    acand2.push_back(acand[k+2]);
                }
            }
            if(acand2[0] < acand2[1]){
                amax = acand2[1];
                amin = acand2[0];
            }else{
                amax = acand2[0];
                amin = acand2[1];
            }
            //search
            p.createSuber(x,u[j][0],y,u[j][1]);
            a[j] = goldenp(p,amin,(amin+amax)/2,amax,tau);
            //iteration
            x = x+a[j]*u[j][0];
            y = y+a[j]*u[j][1];
            //evaluation
            fv = p.eval(x,y,0);
            //record
            record_tmp[4] = a[j];
            record_tmp[5] = x;
            record_tmp[6] = y;
            record_tmp[7] = fv;
            record.push_back(record_tmp);
        }
        u.pop_front();
        i++;
    }while((fabs(fv-before[0])>tau || fabs(pow(x-before[1],2)+pow(y-before[2],2))>tau) && i<200);
    return record;
}

double goldenp(Polys& p,double a, double b, double c, double tau){//a跟c是左右bound,b是中間的一個值, tau應該是區間誤差
    double x;
    const double phi = (1+(double)sqrt((double)5))/2;
    const double resphi = 2-phi;//(3-根號5)/2
    if(c-b>b-a){//右側較多
        x = b + resphi*(c-b);
    }else{//左側較多
        x = b - resphi*(b-a);
    }
    if(abs(c-a) < tau*abs(b) + abs(x))
        return (c+a)/2;
    if(p.evalSuber(x) < p.evalSuber(b)){
        if(c-b > b-a)return goldenp(p,b,x,c,tau);
        else return goldenp(p,a,x,b,tau);
    }else{
        if(c-b > b-a)return goldenp(p,a,b,x,tau);
        else return goldenp(p,x,b,c,tau);
    }
}

#endif // POWELL

