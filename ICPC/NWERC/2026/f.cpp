#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i = a; i<(b);i++)


void solve(){
    ll n; cin >> n;
    vi a(n), b(n); 

    int suma = 0, sumb = 0;
    FOR(i,0,n){
        cin >> a[i] >> b[i];
        suma += a[i];
        sumb += b[i];
    }

    int s = sumb - suma;
    FOR(i,0,n){
        if(s <= b[i] - a[i]){
            cout << i+1 << "\n";
            return;
        }
    }

    cout << "impossible\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}