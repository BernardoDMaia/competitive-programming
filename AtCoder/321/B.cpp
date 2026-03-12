#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    int n,x; cin >> n >> x;
    int soma = 0;

    vector<int>v(n-1);
    for(int i = 0; i < n-1; i++){
        cin >> v[i];
        soma += v[i];
    }

    for(int i = 0; i < 101; i++){
        vector<int>aux = v;
        aux.push_back(i);

        sort(aux.begin(), aux.end());
        int sum = 0;
        for(int j = 1; j < n-1; j++){
            sum += aux[j];
        }

        if(sum >= x) {
            cout << i << endl;
            return 0;
        }
    }

    cout << -1 << endl;
}
