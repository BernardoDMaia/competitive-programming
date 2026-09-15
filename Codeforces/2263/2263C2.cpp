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
//ctrl+alt+a p/ accepted
const int MOD = 1e9+7;

void solve(){
    int n; cin >> n;
    vi need(n, -1), dp(n, 0), diff(n+1,0);
    FOR(i,1,n+1){
        int mex; cin >> mex;
        int l = min(n,mex*i);
        int r = min(n,(mex+1)*i);
        diff[l]--;diff[r]++;
        
        FOR(j,0,mex){//preciso de um cara que y/i = j
            //preciso de alguem entre i*j e (i*(j+1))-1
            //quando chego em i*(j+1)-1, preciso ter escolhido alguém >= x*j
            int ll = min(n-1, i*j), rr = min(n-1, (i*(j+1)) - 1);
            need[rr] = max(need[rr], ll);
        }
    }

    FOR(i,1,n+1) diff[i] += diff[i-1];

    int last = -1;
    int ans = 1;

    FOR(i,0,n){
        if(!diff[i]){
            dp[i] = ans;
            ans = (ans*2) % MOD;
        }
        if(need[i] != -1){//preciso escolher quem termina em need[i]
            if(last == -1){
                last = 0;
                ans = (ans-1+MOD) % MOD;
            }
            while(last < need[i]){
                ans = (ans-dp[last]+MOD) % MOD;
                last++;
            }
        }
    }

    cout << ans << "\n";
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