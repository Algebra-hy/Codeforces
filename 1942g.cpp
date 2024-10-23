#include <cstdio>
const int S=1000004,mod=998244353;
int n,fact[S],ifact[S];
inline int ksm(int a,int b) {
    int s=1;
    while (b) {
        if (b&1) s=1ll*s*a%mod;
        a=1ll*a*a%mod;b>>=1;
    }
    return s;
}
inline int binom(int n,int m) {
    if (m>n || m<0) return 0;
    return 1ll*fact[n]*ifact[m]%mod*ifact[n-m]%mod;
}
int main() {
    fact[0]=1;
    for (int i=1;i<S;++i) fact[i]=1ll*fact[i-1]*i%mod;
    ifact[S-1]=ksm(fact[S-1],mod-2);
    for (int i=S-2;i>=0;--i)
        ifact[i]=(i+1ll)*ifact[i+1]%mod;
    int T;scanf("%d",&T);
    int a,b,c;
    while (T--) {
        scanf("%d%d%d",&a,&b,&c);
        a+=5;
        int res=0;
        for (int i=4;i<=a-1 && i-4 <= c;++i) {
            res = (res + 1ll*(binom(2*i-4,i) - 1ll*binom(2*i-4,i+1))*binom(i+1,5)%mod*binom(a+c-(2*i-4)-1, c-(i-4))%mod + mod)%mod;
        }
        if (5+c-a>0) {
            res = (res + 1ll*(binom(a+c,a) - binom(a+c,c+5))*binom(a,5)%mod + mod)%mod;
        }
        int base = binom(a+c,a)*1ll*binom(a,5)%mod;
        res=1ll*res*ksm(base,mod-2)%mod;
        printf("%d\n",res);
    }
    return 0;
}