#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9+7;

ll fastexp(ll b, ll e){
    ll res = 1;
    while(e){
        if(e & 1) res = res*b%mod;
        b = b*b%mod;
        e/= 2;
    }
    return res;
}

void solve(){

    ll k; cin >> k;

    vector<int> divisors;
    for(ll i = 1; i < k; i++){
        if(k%i == 0) divisors.push_back(i);
    }   

    vector<ll> ans(divisors.size());

    for(int i = 0; i < divisors.size(); i++){
        ans[i] = fastexp(2, divisors[i]);
        for(int j = 0; j < i; j++){
            if(divisors[i]%divisors[j] == 0) {
                ans[i] -= ans[j];
                ans[i] %= mod;
                ans[i] += mod;
                ans[i] %= mod;
            }
        }   
    }

    ll res = 0;
    for(int i = 0; i < divisors.size(); i++){
        res += ans[i];
        res %= mod;
    }

    cout << res << "\n";



}

int main(){
    cin.tie(0), ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) solve();
}