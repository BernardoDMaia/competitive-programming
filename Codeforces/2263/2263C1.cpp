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

void solve(){
    int n; cin >> n;
    vi ans(n, 1);
    
    FOR(i,1,n+1){
        int x; cin >> x;
        if(i == 1 && x <= n-1) ans[x] = 0;
        else{
            int l = (x*i);
            int r = (x+1)*i;
            FOR(j,l,r){
                if(j > n-1) break;
                ans[j] = 0;
            }
        }
    }

    int cont = 0;
    FOR(i,0,n) if(ans[i]) cont++;
    cout << cont << "\n";
    FOR(i,0,n) if(ans[i]) cout << i << " ";
    cout << "\n";
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