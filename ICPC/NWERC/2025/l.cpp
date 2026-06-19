#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
#define FOR(i,a,b) for(int i = a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define deb(x) cerr<< #x << "=" << x << "\n";
#define sz(x) x.size()
#define pb push_back

void solve(){
    int n,m,x,y; cin >> n >> m >> x >> y;
    vi h(n); FOR(i,0,n) cin >> h[i];
    vi b(m); FOR(i,0,m) cin >> b[i];

    sort(all(h));
    sort(all(b));

    auto pode = [&](int k) -> bool {
        vi qtd(n, 0);
        int i = 0, j = 0;
        while(i < n && j < m){
            if(b[j] > h[i]) i++;
            else{
                if(i <= k-1){
                    if(qtd[i] < y){
                        qtd[i]++;
                        j++;
                    }
                    else i++;
                }
                else{
                    if(qtd[i] == x){
                        i++;
                    }
                    else{
                        qtd[i]++;
                        j++;
                    }
                }
            }
        }

        return j == m;
    };

    int ans = -1;
    int l = 0, r = n;
    while(l <= r){
        int mid = (l+r)/2;
        if(pode(mid)){
            l = mid+1;
            ans = mid;
        }
        else r = mid-1;
    }

    if(ans == -1){
        cout << "impossible\n";
        return;
    }
    cout << ans << "\n";

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();    
    }
    return 0;
}