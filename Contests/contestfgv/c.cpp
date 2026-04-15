#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


void solve(){

    string s; cin >> s;

    int cont = 0, minor = 1e9+7, ans = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == 'B') cont++;
        else cont--;
        if(cont < minor){
            minor = cont;
            ans = i+1;
        }
    }

    if(minor == 0) cout << 0 << "\n";
    else cout << ans << "\n";

}

int main(){
    cin.tie(0), ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) solve();
}