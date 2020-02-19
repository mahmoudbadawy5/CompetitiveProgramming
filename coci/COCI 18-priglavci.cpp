/*
Let's calculate the minimum needed distance for a student i to reach a station that bus j passes by. Now binary search on the 
answer by only considering matching pairs (i,j) such that dist[i][j]<=mid. To check if it's possible we make find the maximum
matching and make sure it's exactly n.
*/

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int N=105;

int dis[N][N];
pair<int,int> a[N],b[N];
vector<int> bs[N],adj[N],cur[N];
int pa[N],vis[N];
int n,m,c,k;

int sqr(int x)
{
	return x*x;
}

int calc(int x,int y)
{
	return sqr(a[x].F-b[y].F)+sqr(a[x].S-b[y].S);
}

int go(int x)
{
	if(vis[x]) return 0;
	vis[x]=1;
	for(int i:adj[x])
	{
		if(cur[i].size()<c)
		{
			cur[i].push_back(x);
			pa[x]=i;
			return 1;
		}
	}
	for(int i:adj[x])
	{
		for(int &j:cur[i])
		{
			if(go(j))
			{
				j=x;
				pa[x]=i;
				return 1;
			}
		}
	}
	return 0;
}

int can(int x)
{
	for(int i=0;i<k;i++) cur[i].clear();
	for(int i=0;i<n;i++)
	{
		adj[i].clear();
		pa[i]=-1;
		for(int j=0;j<k;j++)
		{
			if(dis[i][j]<=x)
				adj[i].push_back(j);
		}
	}
	for(int i=0;i<n;i++)
	{
		memset(vis,0,sizeof vis);
		if(!go(i)) return 0;
	}
	return 1;
}

int main()
{
	scanf("%d %d %d %d",&n,&m,&c,&k);
	for(int i=0;i<n;i++)
		scanf("%d %d",&a[i].F,&a[i].S);
	for(int i=0;i<m;i++)
		scanf("%d %d",&b[i].F,&b[i].S);
	for(int i=0;i<k;i++)
	{
		int x;
		scanf("%d",&x);
		while(x--)
		{
			int y;
			scanf("%d",&y);
			bs[i].push_back(y-1);
		}
	}
	int INF=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<k;j++)
		{
			dis[i][j]=(1<<30);
			for(int x:bs[j])
				dis[i][j]=min(dis[i][j],calc(i,x));
			INF=max(INF,dis[i][j]);
		}
	}
	if(!can(INF))
	{
		cout << -1 << endl;
		return 0;
	}
	int st=0,en=INF,ans=INF;
	while(st<=en)
	{
		int mid=(st+en)/2;
		if(can(mid))
		{
			en=mid-1; ans=mid;
		}
		else st=mid+1;
	}
	printf("%d\n",ans);
	can(ans);
	for(int i=0;i<n;i++)
	{
		for(int j:bs[pa[i]])
		{
			if(dis[i][pa[i]]==calc(i,j))
			{
				printf("%d\n",j+1);
				break;
			}
		}
	}
}
