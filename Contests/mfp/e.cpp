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
    ll n,p,s; cin >> n >> p >> s;
    vll t(3), d(3);
    FOR(i,0,3) cin >> t[i];
    FOR(i,0,3) cin >> d[i];
    ll ans = 1e18;

    auto recursao = [&](auto && self, ll time, ll laps, ll pits) -> void {
        if(pits > s) return;

        ll aux1 = laps, aux2 = time; 
        FOR(i,0,3){
            laps = aux1; time = aux2;
            if(laps + d[i] >= n){
                time += (n-laps)*t[i];
                ans = min(ans, time); 
            }
            else{
                laps += d[i];
                time += d[i]*t[i];
                time += p;
                self(self, time, laps, pits+1);
            }
        }

    };

    recursao(recursao,0,0,0);
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