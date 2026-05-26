#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i =a;i<(b);i++)
#define all(x) x.begin(), x.end()

void solve(){
    int n; cin >> n;
    int ans = 0;
    int time = 0;
    vector<pair<int,int>> curr, espera;
    FOR(i,0,n){
        int x,y; cin >> x >> y;
        if(curr.empty()){
            curr.push_back({x+10,y});
            ans = max(ans,x+10);
            //cout << curr.back().first << "-----\n";
            continue;
        }
        if(y==curr.back().second){
            if(x< curr.back().first || espera.empty()){
                curr.pop_back();
                curr.push_back({x+10,y});
                ans = max(ans,x+10);
            }else{
                int v = curr.back().first;
                curr.pop_back();
                curr.push_back({v+10, espera.back().second});
                ans = max(ans,curr.back().first);
                while(!espera.empty()){
                    espera.pop_back();
                }
                espera.push_back({x+10,y});
            }
        }else{
            if(x>=curr.back().first){
                curr.pop_back();
                curr.push_back({x+10,y});
            }else{
                espera.push_back({x,y});
            }
        }
        ans = max(ans,curr.back().first);
      //  cout << curr.back().first << "----\n";
    }
   // cout << "ans: " << ans << "\n";
    if(espera.size()>0){
       // cout << "curr: " << curr.back().first << " esp: "<< espera.back().first << "\n";
        if(espera.back().first<=curr.back().first) ans += 10;
        //ans = espera.back().first;
    }
    cout << ans << "\n";
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}