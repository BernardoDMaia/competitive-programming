#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i = a; i<(b);i++)

void solve(){
    int n; cin >> n;
    ll p = 1;
    vi ans;

    FOR(i,1,n){
        if(gcd(i,n) == 1){
            ans.push_back(i);
            p = (p*i) % n;
        }
    }

    if(p%n != 1){
        ans.erase(find(ans.begin(), ans.end(),(p%n)));
    }

    cout << ans.size() << "\n";
    for(int v : ans) cout << v << " ";
    cout << "\n";

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}