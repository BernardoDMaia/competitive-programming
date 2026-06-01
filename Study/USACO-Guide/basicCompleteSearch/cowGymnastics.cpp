#include <bits/stdc++.h>
using namespace std;
using ll = long long ;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
#define FOR(i, a, b) for(int i = a; i < b; i++)
#define all(x) x.begin() , x.end()
#define pb push_back

void solve(){
    int n; cin >> n;
    vector<tuple<int,int,int,int>> a(n);
    FOR(i,0,n){
        int tp, tt, pos, qtd; cin >> tp >> tt >> pos >> qtd;
        a[i] = {pos-tt, pos+tt, qtd, tp};
    }
    sort(all(a), [&](auto A, auto B){
        auto [v1,u1,q1,tp1] = A;
        auto [v2,u2,q2,tp2] = B;
        if(v1 != v2) return v1 > v2;
        if(tp1!=tp2) return tp1<tp2;
        return u1>u2;
    });
    map<ll, ll> mp;
    ll ans = 0;
    FOR(i,0,n){
        auto [v,u,qtd,tp] = a[i];
        if(tp==1){
            mp[u] += qtd;
        }else{
            ll aux = qtd;
            while(aux>0 && !mp.empty()){
                auto it = mp.upper_bound(u);
                if(it==mp.begin()) break;
                it = prev(it);
                ll disp = min(aux, it->second);
                ans += disp;
                aux -= disp;
                it->second -= disp;
                if(it->second==0){
                    mp.erase(it);
                }
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; 
    //cin >> t;
    while(t--){
        solve();
    }
}