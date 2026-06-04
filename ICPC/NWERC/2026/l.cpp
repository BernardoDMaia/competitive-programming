#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i = a; i<(b);i++)
#define all(x) x.begin(), x.end()

void solve(){
    int n; cin >> n;
    map<string, array<int,11>> artists;
    
    int max_f = 0;
    FOR(i,0,n){
        FOR(j,1,11){
            string s; cin >> s;
            artists[s][j]++;
            artists[s][0]++;
            max_f = max(max_f, artists[s][0]);
        }
    }

    string ans = "";
    array<int,11> curr{};
    curr.fill(0);
    int tie = 0;

    for(auto [s,v] : artists){
        if(v[0] == max_f){
            if(v > curr){
                curr = v;
                ans = s;
                tie = 0;
            }
            else if(v == curr) tie = 1;
        }
    }

    if(tie){
        cout << "tie\n";
        return;
    }
    cout << ans << "\n";

}

int main(){
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    solve();

    return 0;
}