#include <bits/stdc++.h>
using namespace std;
#define int long long
using vi = vector<int>;
#define FOR(i,a,b) for(int i =a;i<b;i++)
#define all(x) x.begin(), x.end()
using pii = pair<int,int>;
#define pb push_back
#define sz(x) x.size()
#define deb(x) cerr << #x << "= " << x << "\n";
#define deb2(x,y) cerr << #x << "= " << x << ", "<< #y << "= " << y << "\n";

const int B = 53;
const int MOD = 1e9+7;

void solve(){
    string s; cin >> s;
    int n = sz(s);

    int found = 0, ans = 0, start = 0;
    while(found != -1){
        found = -1;
        int hshR = 0, hshL = 0, pw = 1;
        for(int l = start; l < n/2; l++){
            int x = (unsigned char)s[l] +1;
            int y = (unsigned char)s[n-l-1] +1;

            hshL = (hshL * B + x) % MOD;
            hshR = (hshR + pw*y) % MOD;
            if(hshR == hshL){
                found = l;
                l++;
                break;
            }
            pw = (pw*B) % MOD;
        }

        if(found != -1){
            start = found + 1; 
            ans += 2;
        }
    }

    if(start*2 == n) cout << ans << "\n";
    else cout << ans+1 << "\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--)
    solve();
    return 0;
}