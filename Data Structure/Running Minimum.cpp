#include <bits/stdc++.h>
using namespace std;

struct StackMinimum{
    stack<pair<int,int>> container;
    void push(int value){ // O(1)
        int newmin = container.empty()?value:min(value, container.top().second);
        container.push({value, newmin});
    }

    int top(){ // O(1)
        return container.top().first;
    }

    void pop(){ // O(1)
        container.pop();
    }

    int current_minimum(){ // O(1)
        return container.top().second;
    }
};

class QueueMinimum{
public:
    stack<pair<int,int>> s1,s2;
    void push(int value){ // O(1)
        int newmin = s1.empty()?value:min(value, s1.top().second);
        s1.push({value, newmin});
    }

    int front(){ // O(1)
        invertstack();
        return s2.top().first;
    }

    void pop(){ // O(1)
        invertstack();
        s2.pop();
    }

    int current_minimum(){ // O(1)
        if(s1.empty())return s2.top().second;
        if(s2.empty())return s1.top().second;
        return min(s1.top().second, s2.top().second);
    }
private:
    void invertstack(){ // O(1)
        if(s2.empty()) while(!s1.empty()){
            int element = s1.top().first;
            s1.pop();
            int minimum = s2.empty() ? element : min(element, s2.top().second);
            s2.push({element, minimum});
        }   
    }
};
