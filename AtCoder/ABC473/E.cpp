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

void solve(){
    int n, k; cin >> n >> k;
    vi a(n);
    FOR(i,0,n) cin >> a[i];

    int i = 0, ans = 0;
    while(i < n){
        unordered_map<int,int> m;
        m[0] = 1;

        int j = i, sum = 0;
        while(j < n){
            sum = (sum + a[j]) % k;
            if(m[sum]){
                ans++;
                break;
            }
            else{
                m[sum] = 1;
            }
            j++;
        }
        i = j+1;
    }

    cout << ans << "\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--)
    solve();
    return 0;
}