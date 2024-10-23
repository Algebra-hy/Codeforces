#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
const int S=200003;
int n,x,a[S];
priority_queue<int> pq;
int main()
{
	int T;scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d",&n,&x);
		for (int i=1;i<=n;++i)
			scanf("%d",&a[i]);
		int s=0,res=0;
		for (int i=1;i<=n;++i)
		{
			if (s>=a[i])
			{
				pq.push(a[i]);
				++res;
				s-=a[i];
			}
			else if (!pq.empty())
			{
				int o = pq.top();
				if (o > a[i])
				{
					s = s + o - a[i];
					pq.pop();
					pq.push(a[i]);
				}
			}
			s+=x;
		}
		while (!pq.empty()) pq.pop();
		printf("%d\n",res);
	}
	return 0;
}