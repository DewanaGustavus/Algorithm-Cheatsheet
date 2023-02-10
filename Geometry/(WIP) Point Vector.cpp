#include <bits/stdc++.h>
using namespace std;


template<typename T> struct Point{
    T x,y;
    Point<T>(T x, T y){
        this->x = x;
        this->y = y;
    }
    Point<T>(const Point<T>& another){
        this->x = another.x;
        this->y = another.y;
    }

    Point<T> operator + (const Point<T>& p){return {x + p.x, y + p.y};}
    Point<T> operator + (int d){return {x+d, y+d};}
    Point<T> operator - (const Point<T>& p){return {x - p.x, y - p.y};}
    Point<T> operator - (int d){return {x-d, y-d};}
    Point<T> operator * (T d){return {x*d, y*d};}
    Point<T> operator / (T d){return {x/d, y/d};}
    bool operator == (const Point<T>& p){return x == p.x && y == p.y;}
    bool operator != (const Point<T>& p){return x != p.x || y != p.y;}

    double abs(){return sqrt(x*x + y*y);}
    Point<T> scale(const Point<T>& center, double factor){return center + Point<T>(x - center.x, y - center.y)*factor;}
    Point<T> rotate(double angle){return {x*cos(angle)-y*sin(angle), x*sin(angle)+y*sin(angle)};}
    
    double dot(const Point<T>& p){return x*p.x + y*p.y;}
    bool rightangle(const Point<T>& p){return dot(p) == 0;}
    double angle(const Point<T>& p){
        double costetha = dot(p)/p.abs()/abs();
        return acos(max(-1.0, min(1.0, costetha)));
    }
    double cross(const Point<T>& p){return x*p.y - y*p.x;}
};

ostream& operator << (ostream& os, Point<double> p){return os<<"{"<<p.x<<", "<<p.y<<"}";}
double orientation(Point<double> a, Point<double> b, Point<double> c){return (b-a).cross(c-a);}
double orientationangle(Point<double> a, Point<double> b, Point<double> c){
    double angle = (b-a).angle(c-a);
    if(orientation(a,b,c) >= 0)angle = 360-angle;
    return angle;
}
bool inangle(Point<double> a, Point<double> b, Point<double> c, Point<double> x){
    if(orientation(a,b,c) < 0)swap(b,c);
    return orientation(a,b,x) >= 0 && orientation(a,c,x);
}
bool convex(vector<Point<double>> p){
    bool pos = false, neg = false;
    int len = p.size();
    for(int i=0;i<len;i++){
        int orient = orientation(p[i], p[(i+1)%len], p[(i+2)%len]);
        if(orient > 0)pos = true;
        if(orient < 0)neg = true;
    }
    return !(pos && neg);
}
// double shoelace(vector<Point<double>> p){

// }
