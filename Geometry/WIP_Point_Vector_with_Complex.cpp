#include <bits/stdc++.h>
using namespace std;

// macro
typedef complex<double> Point;
#define x   real()
#define y   imag()

// Transformation
Point scale(Point p, Point center, double factor){
    Point tmp = p - center;
    tmp *= factor; 
    return center + tmp;
}
void rotate(Point& p, double angle){p *= polar(1.0, angle);}

// angle
double dot(Point a, Point b){return a.x*b.x + a.y*b.y;}
double cross(Point a, Point b){return a.x*b.y - a.y*b.x;}
bool rightangle(Point a, Point b){return dot(a, b) == 0;}
double angle(Point a, Point b){
    double costetha = dot(a,b)/(abs(a) * abs(b));
    return acos(max(-1.0, min(1.0, costetha)));
}

// orientation
// orientation, 0 colinear, positive counter clockwise, negative clockwise
double orientation(Point a, Point b, Point c){return cross(b-a, c-a);}
double orientationangle(Point a, Point b, Point c){
    double tmpangle = angle(b-a, c-a);
    if(orientation(a,b,c) >= 0)tmpangle = 360 - tmpangle;
    return tmpangle;
}
double inangle(Point a, Point b, Point c, Point p){
    if(orientation(a,b,c) < 0)swap(b,c);
    return orientation(a,b,p) >= 0 && orientation(a,c,p);
}

// polygon
bool convex(vector<Point> vp){
    bool pos = false, neg = false;
    int len = vp.size();
    for(int i=0;i<len;i++){
        double orient = orientation(vp[i], vp[(i+1)%len], vp[(i+2)%len]);
        if(orient > 0)pos = true;
        if(orient < 0)neg = true;
    }
    return !(pos && neg);
}
double polygonarea(vector<Point> vp){
    double area = 0;
    int n = vp.size();
    for(int i=0;i<n;i++){
        area += cross(vp[i], vp[(i+1)%n]);
    }
    return abs(area)/2.0;
}
