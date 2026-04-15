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
    int n,x; cin >> n >> x;

    int curr; cin >> curr;
    cout << 0 << " " << curr << "\n";
    FOR(i,1,n+1){
        int k; cin >> k;
        if(abs(k-curr) >= x){
            curr = k;
            cout << i << " " << curr << "\n";
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}   