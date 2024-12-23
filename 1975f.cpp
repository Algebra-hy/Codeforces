//
// Created by Yang Hang on 2024/10/26.
//
#include <cstdio>
int n,f[21][1<<20],a[1<<20],lim,ans[2000000];
void dfs(int step, int st) {
    if (step==n) {
        if (f[step][0] & 1) {
            ans[++ans[0]]=st;
        }
        return;
    }
    int up = 1<<(n-step-1);
    for (int i=0;i<up;++i)
        f[step+1][i] = f[step][i] & f[step][i|up];
    dfs(step+1, st<<1);
    for (int i=0;i<up;++i)
        f[step+1][i] = f[step][i] & (f[step][i|up]>>1);
    dfs(step+1, st<<1|1);
}
int main() {
    scanf("%d",&n);
    lim = 1<<n;
    f[0][0]=1;
    for (int i=1;i<lim;++i) {
        scanf("%d",a+i);//puts("c");
        f[0][i] = a[i];
    }
    dfs(0,0);
    for (int i=0;i<=ans[0];++i)
        printf("%d\n",ans[i]);
    return 0;
}