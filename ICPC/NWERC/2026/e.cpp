#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i = a; i<(b);i++)

void solve(){
    int n; cin >> n;
    string s; cin >> s;
    vi freq(3);
    FOR(i,0,n){
        if(s[i] == 'r') freq[0]++;
        if(s[i] == 'g') freq[1]++;
        if(s[i] == 'b') freq[2]++;
    }

    int fmaior = 0, fmenor =  1e6;
    FOR(i,0,3){
        fmaior = max(fmaior, freq[i]);
        fmenor = min(fmenor, freq[i]);
    }

    int nmaiores = 0;
    FOR(i,0,3){
        if(freq[i] == fmaior) nmaiores++;
    }

    cout << fixed << setprecision(10);
    if(fmaior == n){
        cout << "0\n";
        return;
    }
    if(nmaiores == 1 || fmenor == 0){
        double ans = 3*(n-fmaior);
        cout << ans << "\n";
        return;
    }
    if(nmaiores == 2){
        double ans = 1.5 + (3*(fmaior+fmenor-1));
        cout << ans << "\n";
        return;
    }
    if(nmaiores == 3){
        double ans = 1.5 + (3*((2*fmaior)-1));
        cout << ans << "\n";
        return;
    }

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}