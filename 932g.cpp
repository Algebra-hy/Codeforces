#include <cstdio>
#include <cstring>
const int S=1000005,mod=1e9+7;
int len[S],ch[S][26],tot=0,trans[S],fail[S],cnt[S],now,top[S],f[S],g[S],diff[S];
int n,res=0;
char c[S],a[S];
inline int nnd(int x){len[++tot]=x;return tot;}
inline int getfail(int x,int pos){while (a[pos-len[x]-1]!=a[pos]) x=fail[x];return x;}
int main()
{
	fail[0]=1;tot=1;len[0]=0;len[1]=-1;
	scanf("%s",c+1);n=strlen(c+1);
    int _=0;
    for (int i=1,j=n;i<=j;++i,--j) {
        a[++_]=c[i];
        if (j!=i) a[++_]=c[j];
    }
//    puts(a+1);
    f[0]=1;
    for (int i=1;i<=n;++i)
    {
        int p=getfail(now,i);
        if (!ch[p][a[i]-'a'])
        {
            int o=nnd(len[p]+2);
            fail[o]=ch[getfail(fail[p],i)][a[i]-'a'];
            ch[p][a[i]-'a']=o;
            diff[o] = len[o] - len[fail[o]];
            if (diff[o] == diff[fail[o]]) {
                top[o] = top[fail[o]];
            } else top[o] = fail[o];
        }
        now=ch[p][a[i]-'a'];
        cnt[now]=cnt[fail[ch[p][a[i]-'a']]]+1;
        for (int j = now; j>1; j=top[j]) {
            g[j] = f[i-len[top[j]]-diff[j]];
            if (diff[j] == diff[fail[j]]) g[j] = (g[j] + g[fail[j]])%mod;
            //printf("%d %d %d\n",i,j,g[j]);
            if (i%2==0) f[i] = (f[i]+g[j])%mod;
        }
//        puts("c");
    }
    printf("%d\n",f[n]);
	return 0;
}