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
    int n; cin >> n;
    int cont0 = 0, cont2 = 0, cont1 = 0;
    FOR(i,0,n){
        int x; cin >> x;
        if(x == 0) cont0++;
        else if(x==1) cont1++;
        else cont2++;
    }

    int ans = 0;
    ans += cont0;
    int duo = min(cont1,cont2);
    ans += duo;
    cont1 -= duo;
    cont2 -= duo;
    ans += cont1/3;
    ans += cont2/3;

    cout << ans << "\n";
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