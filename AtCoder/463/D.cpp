#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
#define FOR(i,a,b) for(int i = a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define deb(x) cerr<< #x << "=" << x << "\n";

void solve(){
    int n, k; cin >> n >> k;
    vector<pii> v(n);
    FOR(i,0,n){
        int l, r; cin >> l >> r;
        v[i] = {l,r};
    }
    sort(all(v));
    vi bestr(n);
    bestr[n-1] = v[n-1].second;
    for(int i = n-2; i >= 0; i--){
        bestr[i] = min(bestr[i+1], v[i].second);
    }

    auto pode = [&](int x) -> bool {
        int cont = 1;
        int idx = 0;
        while(cont < k){
            pii alvo = {(bestr[idx]+x),0};
            idx = lower_bound(all(v), alvo) - v.begin();
            if(idx >= v.size()) break;
            cont++;
        }
        return cont >= k;
    };

    int l = 1;
    int r = 1e9+7;
    int resp = 0;
    while(l <= r){
        int mid = (r+l)/2;
        if(pode(mid)){
            l = mid + 1;
            resp = mid;
        }
        else r = mid-1;
    }

    if(resp == 0){
        cout << -1 << "\n";
        return;
    }

    cout << resp << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1; 
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}