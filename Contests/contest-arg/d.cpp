#include<bits/stdc++.h>
using namespace std;
#define ll long long 

const int MAX = 1e5+7;
vector<ll>problems(MAX), proposals(MAX);

bool pode(int x, int k){
    vector<ll>aux = proposals;
    for(int i = 0; i < k;i++){
        if(aux[i] < ((ll)problems[i]*x)) return false;
        if(i+1 < k) aux[i+1] += (ll)(aux[i] - ((ll)problems[i]*x));
    } 
    return true;
}

int buscabin(int k){
    int l = 0, r = 1e9+7;
    int ans = 0;
    while(l<=r){
        int mid = (l+r)/2;
        if(pode(mid,k)){
            ans = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }

    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int k; cin >> k;
    for(int i = 0; i < k; i++) cin >> problems[i];
    for(int i = 0; i < k; i++) cin >> proposals[i];

    cout << buscabin(k) << endl;
}