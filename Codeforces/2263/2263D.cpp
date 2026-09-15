    #include <bits/stdc++.h>
    using namespace std;
    #define int long long
    using vi = vector<int>;
    #define FOR(i,a,b) for(int i =a;i<b;i++)
    #define all(x) x.begin(), x.end()
    using pii = pair<int,int>;
    #define pb push_back
    #define sz(x) x.size()
    #define deb(x) cerr << #x << "= " << x << "\n";
    #define deb2(x,y) cerr << #x << "= " << x << ", "<< #y << "= " << y << "\n";
    //ctrl+alt+a p/ accepted

    template<typename T> 
    struct BIT{
        int n;
        vector<T>a;
        
        BIT(int n_ = 0){ init(n_); }
        void init(int n_){
            n = n_;
            a.assign(n, T{});
        }

        void add(int idx, const T &v){
            for(int i = idx+1; i <= n; i += i & -i) a[i-1] += v;
        }

        T sum(int x){
            T ans{};
            for(int i = x; i > 0; i -= i & -i) ans += a[i-1];
            return ans;
        }

        T rangeSum(int l, int r) {return sum(r) - sum(l);}

    };

    void solve(){
        int n; cin >> n;
        vi a(n), removed(n);
        FOR(i,0,n) cin >> a[i];
        FOR(i,0,n) cin >> removed[i];

        BIT<int> bit(n);
        
        set<int> champs;
        vi ans;
        for(int i = n-1; i >= 0; i--){
            int idx = removed[i]-1;

            auto it = champs.upper_bound(idx);

            int prevChamp = -1;
            if(it != champs.begin()) prevChamp = *prev(it);

            if(prevChamp != -1){
                int acc = bit.rangeSum(prevChamp, idx);
                if(acc < a[idx]){
                    champs.insert(idx);
                    prevChamp = idx;
                }
            }
            else{
                champs.insert(idx);
                prevChamp = idx;
            }
            bit.add(idx, a[idx]);
            
            //percorrer para a direita
            //it está em prevChamp
            while(true){
                it = champs.upper_bound(idx);//atualizo para saber se o proximo perde
                
                if(it == champs.end()) break;

                if(bit.rangeSum(prevChamp,*it) >= a[*it]){
                    champs.erase(*it);
                }

                else break;
            }

            ans.pb(sz(champs)-1);
        }

        reverse(all(ans));
        for(int x : ans) cout << x << " ";
        cout << "\n";
    }

    signed main(){
        ios::sync_with_stdio(false);
        cin.tie(0);
        int t = 1;
        cin >> t;
        while(t--){
            solve();
        }
        return 0;
    }
