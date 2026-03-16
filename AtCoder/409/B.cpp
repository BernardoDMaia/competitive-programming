#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int n; cin >> n;
    vector<int>v(n);

    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    sort(v.begin(),v.end());

    int ans = 0;
    for(int i = 0; i <= 100; i++){
        for(int j = 0;  j < n; j++){
            if(v[j] >= i){
                if((n-j) >= i){
                    ans = i;
                }
            }
        }
    }

    cout << ans << endl;

}