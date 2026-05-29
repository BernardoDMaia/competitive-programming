    #include <bits/stdc++.h>
    using namespace std;
    using ll = long long;
    using vi = vector<int>;
    #define FOR(i,a,b) for(int i =a;i<(b);i++)
    #define all(x) x.begin(), x.end()
    #define pb push_back

    void solve(){
        int n; cin >> n;
        vi a(51, 0);

        FOR(i,0,(n*10)){
            FOR(j,0,5){
                int x; cin >> x;
                a[x]++;
            }
        }

        bool ok = true;
        FOR(i,0,51){
            if(a[i] > 2*n) {
                cout << i << " ";
                ok = false;
            }
        } 
        if(ok) cout << -1;
        cout << "\n";
    }

    int main(){
        ios::sync_with_stdio(false);
        cin.tie(0);
        solve();

        return 0;
    }