#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i = a; i<(b);i++)

void solve(){
    int n; cin >> n;
    for(int i = n/2; i >= 0; i--){
        if(gcd(i,n) == 1){
            cout << i << "\n";
            return;
        }
    }

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}