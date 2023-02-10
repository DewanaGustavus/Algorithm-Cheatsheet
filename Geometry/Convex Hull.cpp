#include <bits/stdc++.h>
using namespace std;

// macro
typedef complex<int> Point;
#define x   real()
#define y   imag()

int cross(Point a, Point b){return a.x*b.y - a.y*b.x;}
int orientation(Point a, Point b, Point c){return cross(b-a, c-a);}
bool cw(Point a, Point b, Point c, bool include_collinear){
    int o = orientation(a,b,c);
    return o < 0 || (include_collinear && o == 0);
}
bool collinear(Point a, Point b, Point c){return orientation(a,b,c) == 0;}

void ConvexHull(vector<Point>& vp, bool include_collinear = false){
    Point p0 = *min_element(vp.begin(), vp.end(), [](Point a, Point b){
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    sort(vp.begin(), vp.end(), [&p0](Point a, Point b){
        int o = orientation(p0,a,b);
        if(o != 0)return o < 0;
        int dista = (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y);
        int distb = (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
        return dista < distb;
    });
    if(include_collinear){
        int i = vp.size() - 1;
        while(i >= 0 && collinear(p0, vp[i], vp.back()))i--;
        reverse(vp.begin() + i + 1, vp.end());
    }

    vector<Point> st;
    for(int i=0;i<vp.size();i++){
        while(st.size() > 1 && !cw(st[st.size()-2], st.back(), vp[i], include_collinear))
            st.pop_back();
        st.push_back(vp[i]);
    }

    vp = st;
}

