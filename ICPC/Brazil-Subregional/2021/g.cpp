#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i =a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define deb(x) cerr << #x << "=" <<  x << "\n";

void solve(){
    ll n; cin >> n;

    vector<pair<ll, string>> fib;
    fib.pb({(ll)1, ""});
    fib.pb({(ll)1, ""});
    int tam = 2;

    string s = "B";
    while(true){
        ll aux = fib[tam-2].first + fib[tam-1].first;
        string aux1 = "A";
        string t = aux1 + s;
        s = t;
        if(aux > 1e15) break;
        fib.pb({aux, t});
        tam++;
    }

    string ans = "";
    vector<ll> a;
    bool ok = true;

    auto recursao = [&](auto && self,int idx, ll x, vector<ll> &v) -> void {
        if(x == 1){
            if(ok){
                a = v;
                ok = false;
            }
            return;
        }
        if(!ok) return;
        for(int i = idx; i >= 2; i--){
            if(x % fib[i].first == 0){
                v.pb(fib[i].first);
                self(self, i, (x/fib[i].first), v);
                v.pop_back();
            }
        }
    };

    vector<ll> aux = {};
    recursao(recursao, fib.size() - 1, n, aux);
    map<ll,int> freq;

    for(ll v : a) freq[v]++;

    for(int i = fib.size()-1; i >= 2; i--){
        if(freq.count(fib[i].first)){
            FOR(j,0,freq[fib[i].first]){
                ans += fib[i].second;
            }
        }
    }

    if(ans == "") cout << "IMPOSSIBLE\n";
    else cout <<  ans << "\n";
        
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
} 