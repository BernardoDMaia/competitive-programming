#include <bits/stdc++.h>
using namespace std;
using ll= long long;
using vi = vector<int>;
using vll =vector<ll>;
using vc =vector<char>;
using vpii =vector<pair<int,int>>;
#define FOR(i,a,b) for(int i=a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)x.size()

const int INF = 1e9+5;


template <typename T >
struct BIT {
    int n ;
    vector <T > a ;

    BIT ( int n_ = 0) {
        init ( n_ ) ;
    }

    void init ( int n_ ) {
        n = n_ ;
        a . assign (n , T {}) ;
    }

    void add ( int x , const T & v ) {
        for( int i = x + 1; i <= n ; i += i & -i ) {
            a [i -1] += v ;
        }
    }
    
    T sum ( int x ) {
        T ans {};
        for ( int i = x ; i > 0; i -= i & -i ) {
            ans += a [i -1];
        }
        return ans ;
    }

    T rangeSum ( int l , int r ) {
        return sum ( r ) - sum ( l ) ;
    }

    int select ( const T & k ) {
        int x = 0;
        T cur {};
        for ( int i = 1 << __lg ( n ) ; i; i /= 2) {
            if( x + i <= n && cur + a [ x + i - 1] <= k ){
                x += i ;
                cur += a [ x - 1];
            }
        }
        return x ;
    }
};

void solve(){
    int n, q; cin >> n >> q;
    BIT <ll> bit(n);
    vi state(n);
    string s; cin >> s;

    FOR(i,0,n-1){
        if(s[i+1] == s[i]){
            state[i] = 1;
            bit.add(i, 1);
        }
    }

    
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}