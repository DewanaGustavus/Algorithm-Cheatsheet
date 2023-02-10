#include <bits/stdc++.h>
using namespace std;

vector<int> KMP(string str, string pattern){
    // return how many pattern matching occurence in string 
    // Time Complexity : O(|n| + |m|)
    int n = str.size();
    int m = pattern.size();

    vector<int> pi(n + m + 1);

    string kmpstr = pattern + "#" + str;
    for(int i=1;i<n+m+1;i++){
        int j = pi[i-1];
        while(j > 0 && kmpstr[j] != kmpstr[i]){
            j = pi[j-1];
        }
        if(kmpstr[j] == kmpstr[i])j++;
        pi[i] = j;
    }

    vector<int> matching_idx;
    for(int i=0;i<n;i++){
        if(pi[i+m+1] == m){
            matching_idx.push_back(i-m);
        }
    }
    return matching_idx;
}
