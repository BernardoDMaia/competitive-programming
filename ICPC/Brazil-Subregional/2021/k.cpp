    #include <bits/stdc++.h>
    using namespace std;
    using ll = long long;
    using vi = vector<int>;
    #define FOR(i,a,b) for(int i =a;i<(b);i++)
    #define all(x) x.begin(), x.end()
    #define pb push_back

    void solve(){
        queue<int>dir0, dir1;
        int n; cin >> n;

        FOR(i,0,n){
            int x, y; cin >> x >>  y;
            if(y == 1) dir1.push(x);
            else dir0.push(x);
        }

        int time = 0;
        while(!dir0.empty() || !dir1.empty()){
            int v = 1e9+7;
            int u = 1e9+7;
            if(!dir0.empty()){
                v = dir0.front();
            }
            if(!dir1.empty()){
                u = dir1.front();
            }

            if(v < u){//v entra primeiro
                while(!dir0.empty() && dir0.front() < time){
                    // apaga todos ate time(entra junto)
                    dir0.pop();
                }
                time += 10;
                while(!dir0.empty() && dir0.front() < time){
                    // ve se alguem entra
                    time = dir0.front() + 10;
                    dir0.pop();
                }
            }
            else{
                while(!dir1.empty() && dir1.front() < time){
                    dir1.pop();
                }
                time += 10;
                while(!dir1.empty() && dir1.front() < time){
                    time = dir1.front() + 10;
                    dir1.pop();
                }
            }
            
        }

        cout << time << "\n";
    }

    int main(){
        ios::sync_with_stdio(false);
        cin.tie(0);
        solve();

        return 0;
    }