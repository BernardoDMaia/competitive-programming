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
    vector<tuple<ll,ll,ll>>cost(n);//custo, ncompr, nvend;
    ll buy = 0, sell = 0;
    FOR(i,0,n){
        double c; ll b, s; cin >> c >> b >> s;
        c*= 100.0;
        ll cc = c;
        cost[i] = {c,b,s};
        buy += b;
    }

    sort(all(cost));
    ll ans = 0, total = 0;
    FOR(i,0,n){
        auto [c,b,s] = cost[i];
        sell += s;
        ll curr = c*(min(sell,buy));
        if(curr > total){
            total = curr;
            ans = c;
        }
        buy -= b;
    }

    if(total == 0) cout << "impossible\n";
    else cout << ans/100 <<"."<<ans%100  << " " << total/100 <<"." <<total%100;

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}