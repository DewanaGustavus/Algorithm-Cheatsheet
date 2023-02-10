#include <bits/stdc++.h>
using namespace std;

int maxsubarr(vector<int> array){ // kadane algorithm
    // finding maximum subarray sum from positive and negative array
    // Time Complexity : O(n)
    int length = array.size();
    int best = 0;
    int curr = 0;
    for(int i=0;i<length;i++){
        curr = max(array[i],curr+array[i]);
        best = max(best,curr);
    }
    return best;
}

int subarrsum(vector<int> array, int target){ // two pointer
    // counting how many subarray contain inside array that have sum equals to target
    // (algorithm works if there is no negative number in array)
    // Time Complexity : O(n)
    int length = array.size();

    int left = 0;
    int right = 0;
    int count = 0;
    int total = 0;
    
    while(right < length){
        total+=array[right++];
        while(total<target && right<length)total+=array[right++];
        while(total>target)total-=array[left++];
        if(total==target)count++;
    }

    return count;
}

int subarrasum2(vector<int> array, int target){ // memo
    // counting how many subarray contain inside array that have sum equals to target
    // (algorithm works in every input)
    // Time Complexity : O(n log(n)) + O(n) memory
    int count = 0;
    int total = 0;
    int search;
    map<int,int> lastprefix;
    lastprefix[0]++;
    
    for(int num:array){
        total += num;
        search = total-target;
        count += lastprefix[search];
        lastprefix[total]++;
    }

    return count;
}

void twosumsearch(vector<int> array, int target){
    // Time Complexity : O(n log(n))
    int length = array.size();
    map<int,int> memo;
    for(int i=0;i<length;i++){
        int num = array[i];
        int search = target-num;
        if(memo.find(search)!=memo.end()){
            printf("%d %d\n",memo[search], i+1);
            return;
        }

        memo[num] = i+1;
    }
    printf("IMPOSSIBLE");
}

int twosumcount(vector<int> array, int target){
    // Time Complexity : O(n log(n))
    int length = array.size();
    map<int,int> memo;
    memo[array[0]] = 1;
    int count = 0;
    for(int i=1;i<length;i++){
        int num = array[i];
        int search = target-num;
        if(memo.find(search)!=memo.end())
            count += memo[search];
        
        memo[num]++;
    }

    return count;
}

void threesum(vector<int> array, int target){
    // Time Complexity : O(n^2 log(n)) + O(n) space
    int length = array.size();
    vector<pair<int,int>> arr(length);
    for(int i=0;i<length;i++){
        arr[i] = {array[i], i + 1};
    }
    sort(arr.begin(), arr.end());

    for(int i=0;i<length;i++)
        for(int j=0;j<length;j++){
            int k = target - arr[i].first - arr[j].first;
            auto it = lower_bound(arr.begin(), arr.end(), make_pair(k, 0LL));
            while(it != arr.end() && (*it).first == target){
                int a = arr[i].second;
                int b = arr[j].second;
                int c = (*it).second;
                if(a != c && b != c){
                    printf("%d %d %d\n", a,b,c);
                    return;
                }
                it++;
            }
        
        }
    printf("IMPOSSIBLE\n");
}

void foursum(vector<int> array, int target){
    // Time Complexity : O(n^2 log(n)) + O(n^2) space
    int length = array.size();
    map<int, vector<pair<int,int>>> container;
    for(int i=0;i<length;i++)
        for(int j=i+1;j<length;j++)
            container[array[i]+array[j]].push_back({i+1,j+1});

    for(auto tmp:container){
        int search = target-tmp.first;
        for(auto p:tmp.second)
            for(auto pair:container[search]){
                int a,b,c,d;
                a=p.first;
                b=p.second;
                c=pair.first;
                d=pair.second;
                if(a!=c&&a!=d&&b!=c&&b!=d){printf("%d %d %d %d",a,b,c,d);return;}
            }
    }
    cout<<"IMPOSSIBLE";
}

vector<int> nearestsmallestvalue(vector<int> array){
    // for every index in the array find the index in the left that have the value smaller than current value
    // and return -1 if the value doesn't exist (no value smaller in the left) 
    // Time Complexity : O(n)
    int amount = array.size();
    stack<pair<int,int>> container;
    vector<int> answer(amount);
    
    for(int i=0;i<amount;i++){
        while(!container.empty() && container.top().first>=array[i])container.pop();
        if(container.empty())answer[i]=-1;
        else answer[i]=container.top().second;
        container.push({array[i],i});
    }

    return answer;
}

vector<int> slidingwindowminimum(vector<int> array, int size){
    // finding the minimum of all subarray with given size
    // Time Complexity : O(n)
    deque<int> container;
    vector<int> ret;
    for(int i=0;i<size;i++){
        while(!container.empty() && array[container.back()] > array[i]) container.pop_back();
        
        container.push_back(i);
    }

    for(int i=size-1;i<array.size();i++){
        if(container.front()==i-size)container.pop_front(); 
        while(!container.empty() && array[container.back()] > array[i]) container.pop_back();
        
        container.push_back(i);
        ret.push_back(array[container.front()]);
    }
    return ret;
}

int LIS(vector<int> array){
    // Time Complexity : O(n log(n))
    int length = array.size();
    vector<int> dp(length,0);
    dp[0] = array[0];
    int longest = 1;

    for(int i=1;i<length;i++){
        auto begin = dp.begin();
        auto end = begin+longest;
        auto it = lower_bound(begin,end,array[i]);

        if(it == end) 
            dp[longest++] = array[i];
        else
            *it = array[i];
    }

    return longest;
}

vector<float> runningmedian(vector<int> array){
    // Time Complexity : O(n log(n))
    
    priority_queue<int> low;
    priority_queue<int, vector<int>, greater<int>> high;

    vector<float> ret;
    ret.push_back(array[0]);
    low.push(array[0]);
    float median = array[0];

    for(int i=1;i<array.size();i++){
        int num = array[i];

        if(low.size() == high.size()){
            if(num < median) low.push(num);
            else high.push(num);
        }else if(low.size() > high.size()){
            if(num < median){
                high.push(low.top());
                low.pop();
                low.push(num);
            }else high.push(num);
        }else{
            if(num > median){
                low.push(high.top());
                high.pop();
                high.push(num);
            }else low.push(num);
        }

        if(low.size() == high.size()) 
            median = (low.top() + high.top())/2.0;
        else if(low.size() > high.size()) 
            median = (float)low.top();
        else 
            median = (float)high.top();
        ret.push_back(median);
    }
    return ret;
}

int longestuniquesubarr(vector<int> arr){
    // Time Complexity : O(n log(n))
    set<int> appear;
    queue<int> container;
    int ans = 0;
    for(int num:arr){
        if(appear.count(num))
            while(appear.count(num)){
                appear.erase(container.front());
                container.pop();
            }        
        container.push(num);
        appear.insert(num);
        ans = max(ans, appear.size());
    }
    return ans;
}

int subarrdivisibility(vector<int> arr, int k){
    // count how much subarr have sum divisible by k
    // Time Complexity : O(n log(n))
    map<int,int> count;
    for(int &num:arr){
        cin>>num;
        num = ((num%k)+k)%k;
    }

    int prevsum = 0;
    for(int num:arr){
        prevsum = (prevsum+num)%k;
        count[prevsum]++;
    }
    
    int mod = 0;
    prevsum = 0;
    int ans = 0;
    for(int num:arr){
        ans += count[mod];
        prevsum = (prevsum+num)%k;
        mod = (mod+num)%k;
        count[prevsum]--;
    }
    cout<<ans;
}


