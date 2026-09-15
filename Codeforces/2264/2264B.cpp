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
    int n, m; cin >> n >> m;
    vi a(n);
    FOR(i,0,n) cin >> a[i];

    int sum = 0, ans = -1e18+7;
    priority_queue <int> pq;
    FOR(i,0,n){
        if(i < m-1){
            sum -= a[i];
            pq.push(a[i]);
        }
        else{
            int curr = m*a[i];
            //deb2(sum, curr);
            ans = max(ans, curr+sum);
            if(m == 1) continue;

            int x = -1e18+7;
            x = pq.top();
            if(x > a[i]){
                pq.pop();
                pq.push(a[i]);
                sum += x;
                sum -= a[i];
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