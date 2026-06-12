#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using pll = pair<ll,ll>;
#define FOR(i,a,b) for(int i = a;i<(b);i++)
#define all(x) x.begin(), x.end()

void solve(){
    int n, q; cin >> n >> q;
    vector<pll> freq(n+1, {0,0});
    string s; cin >> s;
    FOR(i,0,n){
        if(s[i]=='4'){
            pll ant = freq[i];
            freq[i+1] = {ant.first+1, ant.second};
        }
        else{
            pll ant = freq[i];
            freq[i+1] = {ant.first, ant.second+1};
        }
    }
    while(q--){
        ll l, r, x, y; cin >> l >> r >> x >> y;
        ll qtd4 = freq[r].first - freq[l-1].first;
        ll qtd8 = freq[r].second - freq[l-1].second;

        ll sum = qtd8+qtd4;
        ll target = abs(x)+abs(y);
        if(target > (sum*2)-qtd4 || abs(x) > sum || abs(y) > sum) cout << "NO\n";
        else cout << "YES\n";
    }

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
}