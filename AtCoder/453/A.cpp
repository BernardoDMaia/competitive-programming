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
    string s, ans = ""; cin >> s;

    int aux = 0;
    if(s[0] == 'o'){
        FOR(i,0,n){
            if(s[i] == 'o') aux = i+1;
            else break;
        }
        for(aux; aux < n; aux++){
            ans += s[aux];
        }
        cout << ans << "\n";
    }

    else cout << s << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}