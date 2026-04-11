#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
    
    ll n; cin >> n;
    string c; cin >> c;
    ll total = 0;

    char t = c.back();
    c.pop_back();
    ll sti = stoll(c);

    if(t == 'M'){
        total = sti;
    }else if(t == 'G'){
        total = 1024 * sti;
    }else{
        total = 1024 * 1024 * sti; 
    }


    vector<ll> pref(n);
    for(int i = 0; i < n; i++) cin >> pref[i];

    for(int i = 1; i < n; i++){
        pref[i] += pref[i-1];
    }

    auto f = [&](ll mid, ll lst){
        return pref[mid] - lst <= total;  
    };

    vector<ll> ans(n);
    for(int i = 0; i < n; i++){
        ll lst = 0;
        if(i != 0) lst = pref[i-1];

        int l = i-1, r = n;
        while(r-l > 1){
            int mid = (r+l)/2;
            if(f(mid, lst)){
                l = mid;
            }else{
                r = mid;
            }
        }   

        ans[i] = r-i;
    }

//    for(auto a : ans) cout << a << " ";
//    cout <<"\n";


    const ll inf = 1e18;
    ll R = inf;
    for(int i = 0; i < n; i++){
        if(i + ans[i]-1 < n-1) R = min(R, ans[i]);
    }
    cout << R << " ";

    if(ans[0] == n){
        cout << -1 << "\n";
        return;
    }

    for(int i = 0; i < n-R+1; i++){
        if(ans[i] < R+1){
            cout << i + 1 << "\n";
            return;
        }
    }

    assert(0);


}

int main(){
    cin.tie(0), ios_base::sync_with_stdio(false);
    int t; t = 1;
    while(t--){
        solve();
    }
}