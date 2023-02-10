#include <bits/stdc++.h>
using namespace std;

int lettervalue(char ch){return ch-'A';}
char numtoletter(int num){return (char)(num+'0');}
int is_number(char ch){return (int)ch-(int)'0'<10;}
int chartonumber(char ch){return ch-'0';}
int is_upper(char ch){int temp=ch-'A';return temp>=0 && temp<26;}
int is_lower(char ch){int temp=ch-'a';return temp>=0 && temp<26;}
int lsb(int num){return log2(num&-num)+1;}

int digitsum(long long num){
    // only positive number
    int sum = 0;
    for(char ch:to_string(num))sum+=ch-'0';
    return sum;
}

long long change_base(long long num,long long base){
    // change base from 10 to base in [1..10]
    // need binpow function
    long long power=0,ans=0,temp,bintemp;
    while(binarypower(base,power+1)<=num)power++;
    while((power+1)){
        ans*=10;
        bintemp=binarypower(base,power);
        temp=num/bintemp;
        ans+=temp;
        num-=temp*bintemp;
        power--;
    }
    return ans;
}

char flipcase(char ch){
    // need is_upper, is_lower
    if(is_lower(ch))return toupper(ch);
    if(is_upper(ch))return tolower(ch);
    return ch;
}

int palindrome_check(string strings){
    int length = strings.size();
    for(int i=0;i<=length/2;i++)if(strings[i]!=strings[length-1-i])return 0;
    return 1;
}

string operator*(string& s, string::size_type n){
    string result;

    result.resize(s.size() * n);

    for (string::size_type idx = 0; idx != n; ++idx)
        result += s;
    
    return result;
}

int onebit(long long num){
    int count = 0;
    while(num>0){
        if(num%2==0)num/=2;
        else {count++;num--;}
    }
    return count;
}

int toBinary(int num){
    int res = 0;
    int add = 1;
    while(num > 0){
        if(num%2)res+=add;
        num/=2;
        add*=10;
    }
    return res;
}

int randomeuy(){
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int ret=1;
    range(i,0,9)
        ret = (ret*(rng()%1000+1))%MOD;
    
    return ret;
}
