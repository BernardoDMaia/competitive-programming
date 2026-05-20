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
    int n; cin >> n;

    int sum = 0;
    vi a(n); 
    FOR(i,0,n){
        cin >> a[i];
        sum += a[i];
    }

    if(sum == 0){ 
        cout << 0 << "\n";
        return;
    }
    auto pode = [&](int x) -> int {
        int curr = 0, cont = 0;
        FOR(i,0,n){
            if(curr == x){
                curr = a[i];
            }
            else if(curr < x){
                curr += a[i];
                cont++;
            }
            else return 0;
        }
        return cont;
    };

    int ans = 0;
    FOR(i,1,sum+1){
        if(sum % i == 0){
            ans = pode(i);
            if(ans) break;
        }
    }

    cout << ans-1 << "\n";


}

int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}