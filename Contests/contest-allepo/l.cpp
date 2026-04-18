#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using vpii = vector<pair<int,int>>;
#define FOR(i,a,b) for(int i = a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)(x).size()

void solve(){
    int n, m; cin >> n >> m;
    vi a(n), need(30, 0);
    int mask = 0;
    
    bool equals = true;
    FOR(i,0,n){
        cin >> a[i];
        if(i != 0 && a[i] != a[i-1]) equals = false;
        mask = a[i] | mask;
    }
    bitset<30> maskk = mask;

    FOR(i,0,n){
        bitset<30> b= a[i];
        FOR(j,0,30){
            if(b[j] != maskk[j]) need[j] = 1;
        }
    }

    int q; cin >> q;
    int ans = 0;
    FOR(i,0,n){
        if((a[i] | mask) != a[i]){
            ans++;
            i+=m-1;
        } 
    }
    while(q--){
        bool ok = true;
        int x; cin >> x;
        bitset<30> qq = x;
        FOR(i,0,30){
            if(need[i]){
                if(qq[i] == 0){
                    ok = false;
                }
            }
        }
        
        if(equals) cout << 0 << "\n";
        else if(ok){
            if(x | mask == mask) cout << ans << "\n";
            else cout << (n+m-1)/m << "\n";
        }
        else cout << -1 << "\n";

    }
  
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}


