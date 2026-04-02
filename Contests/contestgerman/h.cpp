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
    int n, s1, s2; cin >> n >> s1 >> s2;
    vi v1(s1), v2(s2), v;

    int idx = 0;
    FOR(i,0,s1){
        cin >> v1[i];
        v.pb(v1[i]);
        if(v1[i] == 0) idx = i;
    }
    FOR(i,0,s2) cin >> v2[i];

    reverse(all(v2));
    FOR(i,0,s2){
        v.pb(v2[i]);
        if(v2[i] == 0) idx = i+s1;
    }

    int i = idx, j = idx;
    int maior = 0;
    int ans = 0;
    while(i>0){
        if(v[i-1]>maior){
            maior = v[i-1];
            ans++;
        }
        i--;
    }

    maior = 0;
    while(j<n){
        if(v[j+1]>maior){
            maior = v[j+1];
            ans++;
        }
        j++;
    }

    cout << ans << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}