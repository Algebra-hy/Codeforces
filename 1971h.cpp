#include <cstdio>
const int S=20008;
int n,h[S],nx[S<<1],v[S<<1],eg=1,dfn[S],_=0,low[S],st[S],is[S],cl[S],tot=0;
int a[3][S];
inline void egadd(int uu,int vv)
{
	nx[++eg]=h[uu];h[uu]=eg;
	v[eg]=vv;
}
inline int mi(int a,int b){return a<b?a:b;}
void tarjan(int x)
{
	dfn[x]=low[x]=++_;
	st[++st[0]]=x;
	is[x]=st[0];
	for (int i=h[x];i;i=nx[i])
		if (!dfn[v[i]])
		{
			tarjan(v[i]);
			low[x]=mi(low[x],low[v[i]]);
		}
		else if (is[v[i]])
			low[x]=mi(low[x],dfn[v[i]]);
	if (dfn[x]==low[x])
	{
		int bk=is[x];
		++tot;
		for (int i=bk;i<=st[0];++i)
		{
			cl[st[i]]=tot;
			is[st[i]]=0;
		}
		st[0]=bk-1;
	}
}
int an(int x)
{
	if (x>n) return x-n;
	return x+n;
}
int main()
{
	int T;scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		st[0]=0;_=0;eg=1;tot=0;
		for (int i=1;i<=n+n;++i)
			h[i]=is[i]=cl[i]=dfn[i]=low[i]=0;
		for (int j=0;j<3;++j)
			for (int i=1;i<=n;++i)
			{
				scanf("%d",a[j]+i);
				a[j][i]=a[j][i]>0?a[j][i]+n:-a[j][i];
			}
		for (int i=1;i<=n;++i)
		{
			for (int j=0;j<3;++j)
				for (int k=0;k<3;++k)
					if (j!=k)
						egadd(an(a[j][i]),a[k][i]);
		}
		for (int i=1;i<=n+n;++i)
			if (!dfn[i]) tarjan(i);
		bool fg=true;
		for (int i=1;i<=n;++i)
		{
			//printf("cl %d %d\n",cl[i],cl[i+n]);
			if (cl[i]==cl[i+n])
			{
				fg=false;
				break;
			}
		}
		puts(fg?"Yes":"No");
	}
		
	return 0;
}