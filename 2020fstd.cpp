#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pcc pair<char,char>
#define vi vector <int>
#define vl vector <ll>
#define sd(x) scanf("%d",&x)
#define slld(x) scanf("%lld",&x)
#define pd(x) printf("%d",x)
#define plld(x) printf("%lld",x)
#define pds(x) printf("%d ",x)
#define pllds(x) printf("%lld ",x)
#define pdn(x) printf("%d\n",x)
#define plldn(x) printf("%lld\n",x)
using namespace std;
ll powmod(ll base,ll exponent,ll mod){
    ll ans=1;
    if(base<0) base+=mod;
    while(exponent){
        if(exponent&1)ans=(ans*base)%mod;
        base=(base*base)%mod;
        exponent/=2;
    }
    return ans;
}
ll gcd(ll a, ll b){
    if(b==0) return a;
    else return gcd(b,a%b);
}
const int INF = 2e9;
const ll INFLL = 4e18;
const int small_lim = 1e6+1;
const int mod = 1e9+7;
const int big_lim = 1e3+1;
ll primes_till_i[small_lim];
ll primes_till_bigger_i[big_lim];
vl sieved_primes[small_lim];
vl sieved_primes_big[big_lim];
vi prime;
int N,k,d;
void sieve(){
    vi lpf(small_lim);
    ll pw;
    for(int i = 2; i < small_lim; i++){
        if(! lpf[i]){
            prime.pb(i);
            lpf[i] = i;
        }
        for(int j : prime){
            if((j > lpf[i]) || (j*i >= small_lim)) break;
            lpf[j*i] = j;
        }
    }
    for(int i = 2; i < small_lim; i++){
        primes_till_i[i] = primes_till_i[i-1] + (lpf[i] == i);
    }
}
ll count_primes(ll n, int ind){
    if(ind < 0) return n-1;
    if(1ll*prime[ind]*prime[ind] > n){
        if(n < small_lim) return primes_till_i[n];
        if(primes_till_bigger_i[N/n]) return primes_till_bigger_i[N/n];
        int l = -1, r = ind;
        while(r-l > 1){
            int mid = (l+r)>>1;
            if(1ll*prime[mid]*prime[mid] > n) r = mid;
            else l = mid;
        }
        return primes_till_bigger_i[N/n] = count_primes(n,l);
    }
    int sz;
    if(n < small_lim) sz = sieved_primes[n].size();
    else sz = sieved_primes_big[N/n].size();
    ll ans;
    if(sz <= ind){
        ans = count_primes(n,ind-1);
        ans -= count_primes(n/prime[ind],ind-1);
        ans += ind;
        if(n < small_lim) sieved_primes[n].pb(ans);
        else sieved_primes_big[N/n].pb(ans);
    }
    if(n < small_lim) return sieved_primes[n][ind];
    else return sieved_primes_big[N/n][ind];
}
ll count_primes(ll n){
    printf("x = %lld\n",N/n);
    if(n < small_lim) return primes_till_i[n];
    if(primes_till_bigger_i[N/n]) return primes_till_bigger_i[N/n];
    return count_primes(n,prime.size()-1);
}

const int ncrlim = 3.5e6;

int fact[ncrlim];
int invfact[ncrlim];

void init_fact(){
    fact[0] = 1;
    for(int i = 1; i < ncrlim; i++) fact[i] = (1ll*fact[i-1]*i)%mod;
    invfact[ncrlim-1] = powmod(fact[ncrlim-1], mod-2, mod);
    for(int i = ncrlim-1; i > 0; i--) invfact[i-1] = (1ll*invfact[i]*i)%mod;
}

int ncr(int n, int r){
    if(r > n || r < 0) return 0;
    int ans = fact[n];
    ans = (1ll*ans*invfact[n-r]) % mod;
    ans = (1ll*ans*invfact[r]) % mod;
    return ans;
}

ll calculate_dp(ll n, int ind){
    if(n == 0) return 0;
    if(prime[ind] > n) return 1;
    ll ans = 1,temp;
    if(1ll*prime[ind]*prime[ind] > n){
        temp = ncr(k+d,d);
        temp *= count_primes(n)-ind;
        ans+=temp; ans %= mod;
        return ans;
    }
    ans = 0;
    ll gg = 1;
    ll mult = d;
    while(gg <= n){
        temp = calculate_dp(n/gg,ind+1);
        temp *= ncr(mult,d);
        ans += temp;
        ans %= mod;
        mult += k;
        gg *= prime[ind];
    }
    return ans;
}
int main(){
    sieve();
    init_fact();
    int t;
    sd(t);
    while(t--){
        sd(N);sd(k);sd(d);
        plldn(calculate_dp(N,0));
        for(int i = 1; i < big_lim; i++){
            primes_till_bigger_i[i] = 0;
            sieved_primes_big[i].clear();
        }
    }
    return 0;
}