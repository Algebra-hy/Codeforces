//
// Created by THINKPAD on 2024/10/7.
//
#include <cstdio>
#include <cmath>
#include "vector"
using namespace std;
const int mod=1000000007;
int T,n,k,d;
const int N=4000005;
int fact[N],ifact[N];
inline int binom(int n,int m) {
    if (m>n || n<0 || m<0) return 0;
    return 1ll*fact[n]*ifact[m]%mod*ifact[n-m]%mod;
}
long long ksm(long long a,long long x) {
    long long s=1;
    while (x) {
        if (x&1) s=1ll*s*a%mod;
        a=1ll*a*a%mod;x>>=1;
    }
    return s;
}
const int INF = 2e9;
const long long INFLL = 4e18;
const int small_lim = 1e6+1;
const int big_lim = 1e3+1;
long long primes_till_i[small_lim];
long long primes_till_bigger_i[big_lim];
vector<long long> sieved_primes[small_lim];
vector<long long> sieved_primes_big[big_lim];
vector<long long> prime;
vector<int> lpf(small_lim);
void get(){
    long long pw;
    for(int i = 2; i < small_lim; i++){
        if(! lpf[i]){
            prime.push_back(i);
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
long long count_primes(long long x, int ind){
    if(ind < 0) return x - 1;
    if(1ll*prime[ind]*prime[ind] > x){
        if(x < small_lim) return primes_till_i[x];
        if(primes_till_bigger_i[n / x]) return primes_till_bigger_i[n / x];
        int l = -1, r = ind;
        while(r-l > 1){
            int mid = (l+r)>>1;
            if(1ll*prime[mid]*prime[mid] > x) r = mid;
            else l = mid;
        }
        return primes_till_bigger_i[n / x] = count_primes(x, l);
    }
    int sz;
    if(x < small_lim) sz = sieved_primes[x].size();
    else sz = sieved_primes_big[n / x].size();
    long long ans;
    if(sz <= ind){
        ans = count_primes(x, ind - 1);
        ans -= count_primes(x / prime[ind], ind - 1);
        ans += ind;
        if(x < small_lim) sieved_primes[x].push_back(ans);
        else sieved_primes_big[n / x].push_back(ans);
    }
    if(x < small_lim) return sieved_primes[x][ind];
    else return sieved_primes_big[n / x][ind];
}
long long count_primes(long long x){
    //printf("x = %lld\n",prime.size()-1);
    if(x < small_lim) return primes_till_i[x];
    if(primes_till_bigger_i[n/x]) return primes_till_bigger_i[n/x];
    //puts("c");
    return count_primes(x,prime.size()-1);
}
inline long long calc(long long n,int ind)
{
    //printf("%d %d\n",n,prime[ind]);
    if (n==0) return 0;
    if (prime[ind]>n) return 1;
    if (1ll*prime[ind]*prime[ind] > n){

    }
    long long ret = 0;
    long long gg = 1;
    long long mult = d;
    while (gg <= n) {
        ret = (ret+ 1ll*calc(n/gg,ind+1)*binom(mult,d))%mod;
        mult += k;
        gg *= prime[ind];
    }
    return ret;
}

int main()
{
    get();
/*    for (int i=0;i<100;++i)
        if (count_primes(i) - count_primes(i-1))
            printf("%d ",i);puts("pr");*/
    fact[0]=1;
    for (int i=1;i<N;++i)
        fact[i]=1ll*fact[i-1]*i%mod;
    ifact[N-1]=ksm(fact[N-1],mod-2);
    for (int i=N-2;i>=0;--i)
        ifact[i]=(i+1ll)*ifact[i+1]%mod;
    scanf("%d",&T);
    while (T--)
    {
        scanf("%d%d%d",&n,&k,&d);
        printf("%lld\n",calc(n,0));
        for(int i = 1; i < big_lim; i++){
            primes_till_bigger_i[i] = 0;
            sieved_primes_big[i].clear();
        }
    }
    return 0;
}