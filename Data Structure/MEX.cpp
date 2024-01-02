#include <bits/stdc++.h>
using namespace std;

struct Mex {
    map<int, int> freq;
    set<int> missing;
    vector<int> arr;
    Mex(int size) {
        for(int i=0;i<=size;i++) {
            missing.insert(i);
        }
    }
    Mex(vector<int> &array) : Mex(array.size()){
        for(int x : array) {
            insert(x);
        }
    }
    int mex() {
        return *missing.begin();
    }
    void insert(int value) {
        freq[value]++;
        arr.push_back(value);
        missing.erase(value);
    }
    void update(int idx, int val) {
        if (--freq[arr[idx]] == 0)
            missing.insert(arr[idx]);
        arr[idx] = val;
        freq[val]++;
        missing.erase(val);
    }
};
