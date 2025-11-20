#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        vector<int>a(n+1), b(n+1);

        int qtd1_a = 0; int qtd1_b = 0;

        for(int i = 1; i <= n; i++){
            cin >> a[i];
            if(a[i] == 1) qtd1_a++;
        }
        for(int i = 1; i <= n; i++){
            cin >> b[i];
            if(b[i] == 1) qtd1_b++;
        }

        
        
        if((qtd1_a%2) == (qtd1_b%2)) cout << "Tie" << endl;
        else{
            bool trocas_a = false, trocas_b = false;
            for(int i = 1; i <= n; i++){
                if(a[i] != b[i]){
                    if(i%2 == 0){
                        trocas_b=true;
                        trocas_a=false;
                    }
                    else{
                        trocas_a=true;
                        trocas_b=false;
                    }
                }
            }
            
            if(trocas_a) cout << "Ajisai" << endl;
            else cout << "Mai" << endl;
        }


    }
}