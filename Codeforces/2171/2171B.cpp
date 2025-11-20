#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        vector<int>a(n);

        bool first_idx = false, last_idx = false;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            if(a[0] == -1) first_idx = true;
            if(a[n-1] == -1) last_idx = true;
            if(i != 0 && i != n-1 && a[i] == -1) a[i] = 0;
        }

        if(first_idx && last_idx){
            cout << 0 << endl;
            ll sum = 0;
            for(int i = 2; i < n-1; i++){
                sum += a[i] - a[i-1];
            }
            sum += a[1] - a[n-2];
            if(sum < 0){
                a[0] = 0;
                a[n-1] = abs(sum);
            }
            else if(sum > 0){
                a[0] = abs(sum);
                a[n-1] = 0;
            }
            else{
                a[0] = 0;
                a[n-1] = 0;
            }
            for(int i = 0; i < n; i++){
                cout << a[i] << " ";
            }
            cout << endl;
        }

        else if(first_idx && !last_idx){
            int sum = 0;
            for(int i = 2; i < n; i++){
                sum += a[i] - a[i-1];
            }
            sum += a[1];
            if(sum < 0) {
                a[0] = 0;
                cout << abs(sum) << endl;
            }
            else if(sum > 0){
                a[0] = abs(sum);
                cout << 0 << endl;
            }
            else {
                cout << 0 << endl;
                a[0] = 0;
            }
            for(int i = 0; i < n; i++){
                cout << a[i] << " ";
            }
            cout << endl;
        }

        else if(!first_idx && last_idx){
            
            int sum = 0;
            for(int i = 1; i < n-1; i++){
                sum += a[i] - a[i-1];
            }
            sum -= a[n-2]; 
            if(sum < 0){
                cout << 0 << endl;
                a[n-1] = abs(sum);
            }
            else if(sum > 0){
                cout << abs(sum) << endl;
                a[n-1] = 0;
            }
            else{
                cout << 0 << endl;
                a[n-1] = 0;
            }
            for(int i = 0; i < n; i++){
                cout << a[i] << " ";
            }
            cout << endl;
        }

        else{
            int sum = 0;
            for(int i = 1; i < n; i++){
                sum += a[i] - a[i-1];
            }

            cout << abs(sum) << endl;
            for(int i = 0; i < n; i++){
                cout << a[i] << " ";
            }
                cout << endl;
        }
    }
}