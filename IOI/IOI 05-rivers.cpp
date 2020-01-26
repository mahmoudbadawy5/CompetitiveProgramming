/*
We can solve it using dp[node][res][las] where node is the last node, res is the number of nodes we can choose and las is the
last chosen node. Now to distribute las on the children of node we can solve it using knapsack dp as the constraints are small
enough.
*/

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

int mem[105][50][105];
int n,k;
vector< int > adj[105];
int dist[105][105];
int arr[105];

int mndp[105][105][105];

pair<int,int> ed[105*2];
int st[105],en[105];

int go(int node,int res,int las);

int gomn(int ind,int res,int las)
{
	int &ret=mndp[ind][res][las];
	if(ret!=-1) return ret;
	if(ind==en[ed[ind].F])
		return ret=go(ed[ind].S,res,las);
	ret=(1<<30);
	for(int i=0;i<=res;i++)
		ret=min(ret,go(ed[ind].S,i,las)+gomn(ind+1,res-i,las));
	return ret;
}

int go(int node,int res,int las)
{
	if(mem[node][res][las]!=-1) return mem[node][res][las];
	//cout << node << " " << res << " " << las << " " << dist[las][node] << endl;
	// won't take it
	mem[node][res][las]=dist[las][node]*arr[node]+(en[node]<st[node]?0:gomn(st[node],res,las));
	if(!res) return mem[node][res][las];
	return mem[node][res][las]=min(mem[node][res][las],(en[node]<st[node]?0:gomn(st[node],res-1,node)));
}

int main()
{
	memset(mem,-1,sizeof mem);
	memset(mndp,-1,sizeof mndp);
	memset(dist,'?',sizeof dist);
	cin >> n >> k;
	for(int i=0;i<=n;i++) dist[i][i]=0;
	for(int i=1;i<=n;i++)
	{
		cin >> arr[i];
		int x,y;
		cin >> x >> y;
		adj[x].push_back(i);
		dist[x][i]=y;
	}
	int cur=0;
	for(int i=0;i<=n;i++)
	{
		st[i]=cur;
		for(int j:adj[i])
		{
			ed[cur++]={i,j};
		}
		en[i]=cur-1;
	}
	for(int k=0;k<=n;k++)
		for(int i=0;i<=n;i++)
			for(int j=0;j<=n;j++)
				dist[i][j]=min(1LL*dist[i][j],1LL*dist[i][k]+dist[k][j]);
	/*for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			cout << dist[i][j] << " \n"[j==n];*/
	cout << go(0,k,0) << endl;
	
}
