/*
For each free cell we can notice that it connects two segments (a segment of row and a segment of column). Let's consider these
segments nodes and the cells as edges between them. The resultant graph will be a bipartite graph. We can place at most one
guard for each node in this graph and each edge represents adding a guard in the segments this cell in. So we can run maximum
matching and it will be a valid placement of guards.
*/

#include <bits/stdc++.h>
#define FREE 0
#define PIT 1
#define WALL 2

using namespace std;

const int N=205;

int arr[N][N];
int cid[N][N],rid[N][N];
vector<int> adj[N*N];
int vis[N*N];
int ml[N*N],mr[N*N];
int n,m;

int row[N*N],col[N*N];

int can(int x)
{
	if(vis[x]) return 0;
	vis[x]=1;
	for(int i:adj[x])
	{
		if(mr[i]==-1)
		{
			ml[x]=i; mr[i]=x; return 1;
		}
	}
	for(int i:adj[x])
	{
		if(can(mr[i]))
		{
			ml[x]=i; mr[i]=x; return 1;
		}
	}
	return 0;
}

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
			scanf("%d",&arr[i][j]);
	}
	int id=1;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(arr[i][j]==WALL) continue;
			for(;j<m;j++)
			{
				if(arr[i][j]==WALL) break;
				cid[i][j]=id;
			}
			row[id]=i+1;
			id++;
		}
	}
	int mxid=id-1;
	id=1;
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(arr[j][i]==WALL) continue;
			for(;j<n;j++)
			{
				if(arr[j][i]==WALL) break;
				rid[j][i]=id;
			}
			col[id]=i+1;
			id++;
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(arr[i][j]==FREE)
			{
				adj[cid[i][j]].push_back(rid[i][j]);
			}
		}
	}
	memset(ml,-1,sizeof ml);
	memset(mr,-1,sizeof mr);
	int ans=0;
	for(int i=1;i<=mxid;i++)
	{
		for(int j=1;j<=mxid;j++)
			vis[j]=0;
		if(can(i)) ans++;
	}
	cout << ans << endl;
	for(int i=1;i<=mxid;i++)
	{
		if(ml[i]==-1) continue;
		cout << row[i] << " " << col[ml[i]] << endl;
	}
}
