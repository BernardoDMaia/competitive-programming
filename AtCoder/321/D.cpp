#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    int n, m, p; cin >> n >> m >> p;
    vector<int>mainDish(n);
    vector<int>sideDish(m);
    vector<ll>sumSideDish(m + 1, 0);

    for(int i = 0; i < n; i++) cin >> mainDish[i];
    for(int j = 0;  j < m; j++) cin >> sideDish[j];
    
    sort(sideDish.begin(),sideDish.end());

    for(int k = 0; k < m; k++) sumSideDish[k+1] = sumSideDish[k] + sideDish[k];

    ll ans = 0;
    for(int i = 0; i < n; i++){
        int a = mainDish[i];
        int lb = lower_bound(sideDish.begin(), sideDish.end(), (p-a)) - sideDish.begin();
        ans += (ll) a*lb;
        ans += (ll) (m-lb)*p;
        ans += sumSideDish[lb];
    }

    cout << ans << endl;

}
