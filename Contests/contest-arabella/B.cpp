#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int t; cin >> t;
    while(t--){
        int n, k; cin >> n >> k;
        if(n-k > 1){
            cout << "Kilani" << endl;
        }
        else{
            if(n % 2 == 0) cout << "Ayoub" << endl;
            else cout << "Kilani" << endl;
        }
    }
}
