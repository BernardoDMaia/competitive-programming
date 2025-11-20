#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        int ans = 1;
        if(n%2 != 0) {
            cout << 0 << endl;
            continue;
        }
        else{
            int galinhas = n/2;
            
            for(int i = 0; i < 30;i++){
                if(galinhas == 0 || galinhas == 1) break;
                else{
                    galinhas -= 2;
                    ans++;
                }
            }
        }
        cout <<ans << endl;
    }
}

// x-2 + 7-x + 1-7 = y

// 2 - x + 4 - 2 + z - 4 = y
//-x + z = y
// x - 2 + 1 - x + 4 + 6 + 1 -11 + z - 1 = y
// z - 2 = y
// -1 7 5 3 