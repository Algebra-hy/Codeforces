//
// Created by THINKPAD on 2024/10/7.
//
#include <cstdio>
const int S=2000005;
int n,phi[S],p[S];
bool pp[S];
long long w,h,x[S],y[S];
long long k;
char a[S];
inline long long ksm(long long  a,long long  x,long long  mod) {
    long long s=1;
    while (x) {
        if (x&1) s=1ll*s*a%mod;
        a=1ll*a*a%mod;
        x>>=1;
    }
    return s;
}
inline long long gcd(long long a,long long b) {
    if (!b) return a;
    return gcd(b,a%b);
}
int main() {
    int T;scanf("%d",&T);
    phi[1]=1;
    for (int i=2;i<S;i++)
    {
        if (!pp[i])
        {
            p[++p[0]]=i;
            phi[i] = i-1;
        }
        for (int j=1;j<=p[0] && i*p[j]<S;j++)
        {
            pp[i*p[j]]=true;
            if (i%p[j]==0)
            {
                phi[i*p[j]]=phi[i]*p[j];
                break;
            }
            else phi[i*p[j]]=phi[i]*phi[p[j]];
        }
    }
    while (T--) {
        scanf("%d%lld%lld%lld%s",&n,&k,&w,&h,a);
        long long xn=0,yn=0;
        for (int i=0;i<n;++i) {
            switch (a[i]) {
                case 'L':
                    --xn;
                    break;
                case 'R':
                    ++xn;
                    break;
                case 'U':
                    ++yn;
                    break;
                case 'D':
                    --yn;
                    break;
            }
            xn = (xn % (2 * w) + 2 * w) % (2 * w);
            yn = (yn % (2 * h) + 2 * h) % (2 * h);
            x[i]=xn;y[i]=yn;
        }
        long long gw = gcd(xn,2*w), gh = gcd(yn, 2*h);
        long long W=2*w/gw,H=2*h/gh,cx,cy;
        long long inv_xn = ksm(xn/gw, phi[W]-1, W);
        long long inv_yn = ksm(yn/gh, phi[H]-1, H);
        //puts("c");
        long long gg = gcd(W,H);
        long long hh = H/gg;
        long long inv_W = ksm(W/gg, phi[hh]-1, hh);
        long long res=0;
        --k;
        for (int i=0;i<n;++i) {
            if ((2*w-x[i])%gw) continue;
            if ((2*h-y[i])%gh) continue;
            cx = 1ll*((2*w-x[i])/gw)*inv_xn%W;
            cy = 1ll*((2*h-y[i])/gh)*inv_yn%H;
            //printf("i = %d (mod %d)\n",cx,W);
            //printf("i = %d (mod %d)\n",cy,H);
            if ((cy-cx)%gg) continue;
            long long o = 1ll*(((cy-cx)/gg%hh+hh)%hh)*inv_W%hh;
            if (k-cx-o*W>=0)
                res+=(k-cx-o*W)/(W*hh) + 1;
        }
        printf("%lld\n",res);
    }
    return 0;
}