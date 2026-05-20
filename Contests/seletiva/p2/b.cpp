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
    double x1, y1, r1, x2, y2, r2; cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    
    double distCentros = sqrt(((x1-x2)*(x1-x2)) + ((y1-y2)*(y1-y2)));
    double r = (r1+r2-distCentros)/2;

    double a = ((x2-x1)*(r1-r))/distCentros;
    double b = ((y2-y1)*(r1-r))/distCentros;

    cout << fixed << setprecision(15);
    cout << x1+a << " " << y1+b << " " << r <<"\n";
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