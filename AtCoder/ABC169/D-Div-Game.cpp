#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i = a; i<(b);i++)

void solve(){
    ll n; cin >> n;
    map<ll,int> freq;

    for(ll i = 2; i*i < n; i++){
        while(n % i == 0){
            freq[i]++;
            n /= i;
        }
    }

    if(n > 1) freq[n]++;
    
    int op = 0;
    for(auto [d, f] : freq){
        int cont = f;
        int usando = 1;
        while(cont >= usando){
            op++;
            cont -= usando;
            usando++;
        }
    }

    cout << op << "\n";

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}