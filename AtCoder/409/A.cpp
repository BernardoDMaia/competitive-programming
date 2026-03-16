#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int n; cin >> n;
    string t, a; cin >> t >> a;

    bool ans = false;

    for(int i = 0; i < n; i++){
        if(t[i] == a[i] && t[i] == 'o') ans = true;
    }

    if(ans) cout << "Yes" << endl;
    else cout << "No" << endl;
}