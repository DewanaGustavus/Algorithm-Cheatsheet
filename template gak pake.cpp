#include <bits/stdc++.h>
using namespace std;



// Math
const long double PI = acos(-1);
#define intlen(num)         to_string(num).size()
#define updatemax(var,val)  var=max(var,val);
#define updatemin(var,val)  var=min(var,val);
// Data Structure and Algorithm
#define member(DS,val)      (DS.find(val)!=DS.end())
#define mapcount(mp,arr)    map<int,int>mp;for(auto tmp:arr)mp[tmp]++;
#define len(vec)            (int)((vec).size())
// Input Output Manage
#define testfile            freopen("test_input.txt","r",stdin);
#define fileout             freopen("output.txt","w",stdout);
#define inputline(var)      getline(cin,var);
#define len(arr)            arr.size()
// Macro
#define mp make_pair
#define tup tuple<int,int,int>
// Oneliner Function
ll lsb(ll x){return log2(x&-x)+1;}

#define print2(var1,var2)   cout<<var1<<" "<<var2<<" ";
#define printp(paired)      cout<<paired.first<<" "<<paired.second<<" ";

template<typename C, 
         typename T = decay_t<decltype(*begin(declval<C>()))>,
         typename enable_if<!is_same<C, string>::value>::type* = nullptr
         >
ostream &operator<<(ostream &os, const C &container){
    bool first = true;
    stringstream ss; 
    ss << '[';
    for(const auto &x : container){
        if (!first){
        ss << ", ";
        }
        first = false;
        ss << x;
    }
    ss << ']';
    return os << ss.str();
}

template<class T1, class T2> ostream &operator<<(ostream &os, const pair<T1,T2> &p){
    os << '{' << p.first << ", " << p.second << '}';
    return os;
}

// interactive ask
int ask(int a, int b){
    printf("? %d %d\n", a, b);
    fflush(stdout);
    int x;cin>>x;
    return x;
}
