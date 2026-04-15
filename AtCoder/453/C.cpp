#include <bits/stdc++.h>
using namespace std;
using ll= long long;
using vi = vector<int>;
using vll =vector<ll>;
using vc =vector<char>;
using vpii =vector<pair<int,int>>;
#define FOR(i,a,b) for(int i=a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)x.size()

void solve(){
    int n; cin >> n;
    vll v(n);

    FOR(i,0,n){
        ll x; cin >> x;
        v[i] = x*(ll)10;
    }

    ll ans = 0;
    auto rec = [&](auto &&self,int i, ll curr, ll count) -> void {
        if(i == n+1) return;
        ans = max(ans, count);
        
        ll l = count, r = count;
        if(curr > 0 && curr - v[i] < 0) l++;
        if(curr < 0 && curr + v[i] > 0) r++;
        //esq
        self(self,i+1, curr-v[i], l);
        //dir
        self(self,i+1, curr+v[i], r);


    };

    rec(rec, 0 , 5 , 0);

    cout << ans << endl;

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}   