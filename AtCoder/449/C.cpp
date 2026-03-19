#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, l, r; cin >> n >> l >> r;
    string s; cin >> s;
    r++;

    vector<int>freq(26);

    ll ans = 0;
    for(int j = 0; j < n;j++){
        if(j >= l) freq[s[j-l] - 'a']++;
        if(j >= r) freq[s[j-r] - 'a']--;
        ans += (ll) freq[s[j] - 'a'];
    }
    cout << ans << endl;
}