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
    ll n, w; cin >> n >> w;
    vll a(n),b(n);

    FOR(i,0,n) cin >> a[i];
    FOR(i,0,n) cin >> b[i];

    ll mx = n*w;

    auto pode = [&](ll val) -> bool {
        ll need = 0;
        FOR(i,0,n){
            if(a[i] > b[i]){ //ir pra aula
                ll classes = min(w,((val+a[i]-1)/a[i]));
                need += classes;
                if((classes*a[i]) < val){
                    ll aux = val - (classes*a[i]);
                    need += (aux + b[i]-1)/b[i];
                }
            }
            else{
                need += (val + b[i]-1)/b[i];
            }
            if(need > mx) return false;
        }

        return true;
    };

    ll l = 0, r = 1e18, ans = 0;
    while(l<=r){
        ll mid = l + (r-l)/2;
        if(pode(mid)){
            ans = mid;
            l = mid+1;
        }
        else r = mid-1;
    }

    cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}