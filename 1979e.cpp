#include <cstdio>
#include <utility>
#include <map>
using namespace std;
const int S=200003,dx[]={1,1,-1,-1},dy[]={1,-1,1,-1};
map<pair<int,int>, int> mp;
int n,d;
struct node {
    int x,y;
}a[S];
int main() {
    int T;scanf("%d",&T);
    while (T--) {
        mp.clear();
        scanf("%d%d",&n,&d);
        for (int x,y,i=1;i<=n;++i) {
            scanf("%d%d",&x,&y);
            a[i] = (node){x,y};
            mp[make_pair(x,y)] = i;
        }
        bool flag = false;
        int id1=1,id2=2,id3=3;
        for (int i=1;i<=n && !flag;++i) {
            int xx,yy,x,y;
            id1=i;
            for (int j=0;j<4 && !flag;++j) {
                xx=a[i].x+dx[j]*(d/2);
                yy=a[i].y+dy[j]*(d/2);
                id2=mp[make_pair(xx,yy)];
                if (id2) {
                    if (!(d&3)) {
                        x = a[i].x - dx[j] * (d / 4);
                        y = a[i].y + dy[j] * (d / 4 * 3);
                        id3 = mp[make_pair(x, y)];
                        if (id3) {
                            flag = true;
                            break;
                        }
                        x = a[i].x + dx[j] * (d / 4 * 3);
                        y = a[i].y - dy[j] * (d / 4);
                        id3 = mp[make_pair(x, y)];
                        if (id3) {
                            flag = true;
                            break;
                        }
                    }
                    x = a[i].x + dx[j]*d;
                    y = a[i].y;
                    id3 = mp[make_pair(x, y)];
                    if (id3) {
                        flag = true;
                        break;
                    }

                    x = a[i].x;
                    y = a[i].y + dy[j]*d;
                    id3 = mp[make_pair(x, y)];
                    if (id3) {
                        flag = true;
                        break;
                    }
                }
            }
        }
        if (flag) printf("%d %d %d\n",id1,id2,id3);
        else puts("0 0 0");
    }
    return 0;
}