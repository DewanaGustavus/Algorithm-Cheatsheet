#include <bits/stdc++.h>
using namespace std;
 
#define range(i,s,e)        for(int i=s;i<e;i++)
#define fastIO              ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define print(var)          cout<<(var)<<endl;

const int maxn = 2e5+5;
int n,q;
int arr[maxn];
 
struct node{
    int l, r;
    int val = 0;
    node *tl = nullptr, *tr = nullptr;
    node(int a, int b){
        l = a;
        r = b;
    }
    int sum(int ql, int qr){
        if(ql > r || qr < l)return 0;
        if(ql <= l && r <= qr)return val;
        int ans = 0;
        if(tl)ans += tl->sum(ql, qr);
        if(tr)ans += tr->sum(ql, qr);
        return ans;
    }
};

void build(node* root){
    int l = root->l;
    int r = root->r;
    if(l == r){
        root->val = arr[l];
        return;
    }
    int mid = (l + r)/2;
    root->tl = new node(l, mid);
    root->tr = new node(mid+1, r);
    build(root->tl);
    build(root->tr);
    root->val = root->tl->val + root->tr->val;
}
 
node* add_persistent(int idx, int val, node* root){
    int l = root->l;
    int r = root->r;
    node* new_node = new node(l, r);
    int mid = (l+r)/2;
    if(l == idx && r == idx){
        new_node->val = val;
        return new_node;
    }else if(l <= idx && idx <= mid){
        new_node->tr = root->tr;
        new_node->tl = add_persistent(idx, val, root->tl);
        new_node->val = new_node->tl->val + new_node->tr->val;
    }else{
        new_node->tl = root->tl;
        new_node->tr = add_persistent(idx, val, root->tr);
        new_node->val = new_node->tl->val + new_node->tr->val;
    }
    return new_node;
}
 
node* get_persistent(node* root){
    node* new_node = new node(root->l,root->r);
    new_node->tl = root->tl;
    new_node->tr = root->tr;
    new_node->val = root->val;
    return new_node;
}
 
// https://cses.fi/problemset/task/1737
vector<node*> roots;
int32_t main(){
    fastIO
    
    cin>>n>>q;
    range(i,0,n)cin>>arr[i];
    node* initial = new node(0, n-1);
    build(initial);
    roots.push_back(initial);
 
    range(i,0,q){
        int t, k, a, x;
        cin>>t;
        if(t == 1){
            cin>>k>>a>>x;
            k--;a--;
            node* new_node = add_persistent(a, x, roots[k]);
            roots[k] = new_node;
        }else if(t == 2){
            cin>>k>>a>>x;
            k--;a--;x--;
            print(roots[k]->sum(a,x));
        }else{
            cin>>k;
            node* new_node = get_persistent(roots[k-1]);
            roots.push_back(new_node);
        }
    }
 
    return 0;
}
