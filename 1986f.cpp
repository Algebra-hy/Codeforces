#include <cstdio>
const int S=200002;
int n,m,h[S],nx[S],v[S],k=0,d[S],l[S],tm=0,t[S],f[S]={0},su=0,rt,sz[S];
long long res;
void add(int uu,int vv)
{
	nx[++k]=h[uu];h[uu]=k;v[k]=vv;
	return;
}
void init()
{
	scanf("%d%d",&n,&m);int uu,vv;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&uu,&vv);
		add(uu,vv);add(vv,uu);
	}
	return;
}
int mi(int a,int b){return a<b?a:b;}
void tj(int x,int fa)
{
	d[x]=l[x]=++tm;sz[x]=1;
	for (int i=h[x];i;i=nx[i])
	{
		if (!d[v[i]])
		{
			tj(v[i],x);
			sz[x]+=sz[v[i]];
			l[x]=mi(l[x],l[v[i]]);
			if (l[v[i]]>=d[v[i]])
			{
				//puts("c");
				long long o = (sz[v[i]]-1ll)*sz[v[i]]/2 + (n-sz[v[i]]-1ll)*(n-sz[v[i]])/2;
				if (res > o) res = o;
			}
		}
		else if (v[i]!=fa) l[x]=mi(l[x],d[v[i]]);
	}
	if (f[x]) su++;
	return;
}
void work()
{
	res=n*(n-1ll)/2;
	for (int i=1;i<=n;i++)
		if (!d[i]) rt=i,tj(i,-1);
	printf("%lld\n",res);
	for (int i=0;i<=n;++i) h[i]=d[i]=0;
	k=0;
	tm=0;
	return;
}
int main()
{
	int T;scanf("%d",&T);
	while (T--)
	{
		init();work();
	}
	return 0;
}