#include <bits/stdc++.h>
using namespace std;

int coinsumneed(vector<int> coin, int target){
    // Time Complexity : O(n*m)
    const int inf = 1e9;
    int dp[target+1];
    for(int&num:dp)num=inf;
    dp[0] = 0;

    for(int i=0;i<=target;i++)
        for(int num:coin)
            if(num+i<=target)
                dp[num+i] = min(dp[num+i], dp[i] + 1);

    if(dp[target]==inf)dp[target]=-1;
    return dp[target];
}

int coinsumcount(vector<int> coin, int target){
    // Time Complexity : O(n*m)
    int dp[target+1]={};
    dp[0] = 1;

    for(int i=0;i<=target;i++)
        for(int num:coin)
            if(i-num>=0)
                dp[i] += dp[i-num];

    return dp[target];
}

int pathsum(vector<vector<int>> maze){
    // Time Complexity : O(n^2)
    int n = maze.size();
    int m = maze[0].size();

    int shortest[n][m]={};
    shortest[0][0]=maze[0][0];
    for(int i=1;i<n;i++)shortest[i][0]=shortest[i-1][0]+maze[i][0];
    for(int j=1;j<m;j++)shortest[0][j]=shortest[0][j-1]+maze[0][j];

    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++)
            shortest[i][j] = maze[i][j] + min(shortest[i-1][j], shortest[i][j-1]);
    

    return shortest[n-1][m-1];
}

int knapsack(vector<int> bag, int target){
    // Time Complexity : O(n*m)
    int dp[target+1]={};
    dp[0] = 1;
    
    for(int weight:bag)
        for(int i=target;i>=0;i--)
            if(dp[i] && i+weight<=target)dp[i+weight]=1;
    

    return dp[target];
}

int stringedit(string word, string target){
    // calculating the number of string editing we should do to change word into the target word
    // with just insert, remove, and modify operation
    // Time Complexity : O(n^2)
    const int inf = 1e9;
    int n = word.size() + 1;
    int m = target.size() + 1;
    int dp[n][m]={};
    for(int i=1;i<n;i++)dp[i][0]=dp[i-1][0]+1;
    for(int j=1;j<m;j++)dp[0][j]=dp[0][j-1]+1;
    
    for(int i=1;i<n;i++)for(int j=1;j<m;j++){
        dp[i][j] = min({dp[i][j-1] + 1,
                        dp[i-1][j] + 1,
                        dp[i-1][j-1] + (word[i-1] != target[j-1])});
    }
    
    return dp[n-1][m-1];
}

int steponedp(vector<int> array){
    const int maxn = 1e5+2;
    
    int dp[maxn][2]={};
    dp[1][1] = array[1];

    for(int i=2;i<maxn;i++){
        dp[i][0] = max(dp[i-1][1], dp[i-1][0]);
        dp[i][1] = max(dp[i-1][0], dp[i-2][1]) + array[i];
    }

    return max(dp[maxn-1][0], dp[maxn-1][1]);
}

const int maxsz = 1e5 + 5;
bitset<maxsz> subsetsum(vector<int> array){
    // Time Complexity : O(N)
    bitset<maxsz> dp;
    dp[0] = 1;
    for(int x : array)
        dp |= (dp << x);
    return dp;
}
