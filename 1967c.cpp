#include <cstdio>
const int S=400005,mod=998244353;
int n,a[S],b[S],k,inv[S];
int ksm(int a,int x) {
    int s=1;
    while (x) {
        if (x&1) s=1ll*s*a%mod;
        a=1ll*a*a%mod;x>>=1;
    }
    return s;
}
int main() {
    inv[0]=inv[1]=1;
    for (int i=2;i<S;++i)
        inv[i]=(1ll*mod-mod/i)*inv[mod%i]%mod;
    int T;scanf("%d",&T);
    while (T--) {
        scanf("%d%d", &n, &k);
        int ik = ksm(k, mod-2);
        for (int i = 1; i <= n; ++i) scanf("%d", b + i);
        for (int i = 1; i <= n; ++i) {
            int s = 0, co = 1;
            a[i]=b[i];
            for (int j = i+(i&-i); j <= n; j += j & -j) {
                ++s;
                co = 1ll * co * (s + k - 1) % mod * inv[s] % mod;
                //printf("%d %d\n",co,s);
                // b[j]-=a[i]*C(s+k-1,s)
                b[j] = (b[j] - (1ll * co * a[i]) % mod + mod) % mod;
            }
        }
        for (int i = 1; i <= n; ++i) printf("%d ", a[i]);
        puts("");
    }
    return 0;
}