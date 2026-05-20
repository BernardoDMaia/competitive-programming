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
    //freopen("balancing.in", "r",stdin);
    //freopen("balancing.out", "w",stdout);

    int n, b; cin >> n >> b;
    set<int>x, y;
    vector<pii> cows(n);
    FOR(i,0,n){
        int xx,yy; cin >> xx >> yy;
        cows[i] = {xx,yy};
        x.insert(xx+1);
        x.insert(xx-1);
        y.insert(yy+1);
        y.insert(yy-1);
    }

    int ans = 1e9;
    for(int cx : x){
        for(int cy : y){
            int ld = 0, lt = 0, rd = 0, rt = 0;
            FOR(i,0,n){
                if(cows[i].first < cx && cows[i].second < cy) ld++;
                else if(cows[i].first < cx && cows[i].second > cy) lt++;
                else if(cows[i].first > cx && cows[i].second < cy) rd++;
                else if(cows[i].first > cx && cows[i].second > cy) rt++;
            }

            ans = min(ans, max({ld,lt,rd,rt}));
        }
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