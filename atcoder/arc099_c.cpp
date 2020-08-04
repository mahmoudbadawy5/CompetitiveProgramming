/*
Any two cities with no edg between them must belong to different groups. So we can work on the inverse graph and try to color nodes with two colors. Now for each
component we need to add nodes with the same color to a group and the others to the other group. To minimize the number of roads in each group we can calculate
for each number x if we can make a group with exactly x cities or not and minimize over all answers.
*/

#include <bits/stdc++.h>

using namespace std;

const int N=707;

int adj[N][N];
int mem[N][N],col[N];
int n,m;
vector<pair<int,int> > got;
int co[2];

int go(int node,int c)
{
	if(col[node]!=-1) return col[node]==c;
	col[node]=c;
	co[c]++;
	int ans=1;
	for(int i=1;i<=n;i++)
	{
		if(adj[node][i]||node==i) continue;
		ans&=go(i,c^1);
	}
	return ans;
}

int can(int x,int y)
{
	if(y<0) return 0;
	if(x==got.size()) return (y==0?1:0);
	if(mem[x][y]!=-1) return mem[x][y];
	return mem[x][y]=can(x+1,y-got[x].first)|can(x+1,y-got[x].second);
}

int main()
{
	scanf("%d %d",&n,&m);
	while(m--)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		adj[x][y]=adj[y][x]=1;
	}
	memset(col,-1,sizeof col);
	for(int i=1;i<=n;i++)
	{
		if(col[i]==-1)
		{
			co[0]=co[1]=0;
			if(!go(i,0))
			{
				printf("-1\n");
				return 0;
			}
			got.push_back({co[0],co[1]});
		}
	}
	int ans=(1<<30);
	for(int i=0;i<=n;i++)
	{
		int y=n-i;
		memset(mem,-1,sizeof mem);
		if(can(0,i)) ans=min(ans,i*(i-1)/2+y*(y-1)/2);
	}
	assert(ans!=(1<<30));
	printf("%d\n",ans);
}
