#include <bits/stdc++.h>
using namespace std;
#define ll long long

map<ll,ll>primes;

void prime(ll val){
    for(int i = 2; i*i < val; i++){
        if(val == 1) break;
        if(val%i == 0){
            while(val%i == 0){
                val /= i;
                primes[i]++;
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    string s, t; cin >> s;
    
    for(int i = 0; i < 10; i++){
        if(i < s.size())t += s[i];
    }

    ll val = stoll(t);
    ll count = 0;
    
    for(auto[l,r] : primes){
        count++;
    }

    cout << count << endl;
    for(auto[l,r] : primes){
        cout << l << " " << r << endl;
    }
}
