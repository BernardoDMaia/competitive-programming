#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        vector<int>a(n);

        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        
        int maior = 0, menor = 1e9;
        for (int i = 0; i < n; i++){
            if(a[i]>maior){
                maior = a[i];
                
            }
        }
        
    }
}