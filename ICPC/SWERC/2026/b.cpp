#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pll = pair<ll,ll>;
#define FOR(i,a,b) for(int i = a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define deb(x) cerr<< #x << "=" << x << "\n";

void solve(){
    int n, l, r; cin >> n >> l >> r;
    vi a(n), state(n, 0);
    FOR(i,0,n) cin >> a[i];
    sort(all(a));

    int menos = 0, mais = 0;
    FOR(i,0,n){
        if(a[i] < l){
            menos++;
            state[i] = -1;
        }
        else if(a[i] > r) {
            mais++;
            state[i] = 1;
        }
    }

    if(menos > mais){
        int dif = menos - mais;
        for(int i = n-1; i >= 0; i--){
            if(state[i] == 0){
                state[i] = 1;
                dif--;
                mais++;
            }
            if(dif == 0) break;
        }
    }
    else if(menos < mais){
        int dif = mais - menos;
        FOR(i,0,n){
            if(state[i] == 0){
                state[i] = -1;
                dif--;
                menos++;
            }
            if(dif == 0) break;
        }
    }

    int e = menos, d = n-1-mais;
    while(e < d){
        state[e++] = -1;
        state[d--] = 1;
    }

    int p = r;
    if(menos > mais) p = l;

    ll ans = 0;
    FOR(i,0,n){
        if(state[i] == -1){
            if(p >= a[i]) ans += abs(p-a[i]);
            else ans -= abs(p-a[i]);
        }
        else if(state[i] == 1){
            if(p <= a[i]) ans += abs(p-a[i]);
            else ans -= abs(p-a[i]);
        }
    }

    cout << ans << "\n";

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1; 
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}