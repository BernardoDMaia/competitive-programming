#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int n, l; cin >> n >> l;
    map<int,int>freq;
    freq[0]++;
    int idx_anterior = 0;

    for(int i = 0; i < n-1; i++){
        int x; cin >> x;
        idx_anterior = (idx_anterior+x)%l;
        freq[idx_anterior]++;
    }

    if(l%3 != 0) cout << 0 << endl;
    else{
        ll ans = 0;
        for(int i = 0; i < l/3; i++){
            ans += (ll)freq[i]*freq[i+(l/3)]*freq[i+(2*(l/3))];
        }
        cout << ans << endl;
    }

}