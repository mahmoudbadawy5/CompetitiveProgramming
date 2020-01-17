/*
You are given n equations and n variables that you need th get thier values. So if m > n there are infinite number solutions.
If m==n-1 You are given a tree you can start solving from leaves.
Otherwiese there's exactly one cycle you can solve it using dfs.
*/

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int M=5e5+5;
const int N=1e5+5;

int n,m;
int ans[M],arr[N],co[N];
vector<pair<int,int> > adj[N];
int cur;
vector<pair<int,int> > adj2[M];
int vis[N];

int dfs1(int node,int p,int co,int pa)
{
	if(co==cur) return 0;
	for(auto i:adj2[node])
	{
		if(i.F==pa) continue;
		return i.S*p+dfs1(i.F,-1*p,co+1,node);
	}
}

void dfs2(int node,int co,int pa)
{
	if(co==cur) return;
	for(auto i:adj2[node])
	{
		if(i.F==pa) continue;
		ans[i.F]=i.S-ans[node];
		dfs2(i.F,co+1,node);
	}
}

int main()
{
	cin >> n >> m;
	if(m>n)
	{
		cout << 0 << endl;
		return 0;
	}
	for(int i=1;i<=n;i++)
		cin >> arr[i];
	for(int i=0;i<m;i++)
	{
		int x,y;
		cin >> x >> y;
		adj[x].emplace_back(y,i);
		adj[y].emplace_back(x,i);
		co[x]++; co[y]++;
	}
	queue<int> q;
	for(int i=1;i<=n;i++)
	{
		if(adj[i].size()==1) q.push(i);
	}
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		vis[x]=1;
		int to=-1,ed=-1;
		for(int i=0;i<adj[x].size();i++)
		{
			co[adj[x][i].F]--;
			if(!vis[adj[x][i].F])
			{
				to=adj[x][i].F; ed=adj[x][i].S;
			}
			arr[adj[x][i].F]-=arr[x];
		}
		if(to!=-1)
		{
			ans[ed]=2*arr[x];
			if(co[to]==1)
				q.push(to);
		}
	}
	int mn=-1;
	for(int i=1;i<=n;i++)
	{
		if(vis[i]) continue;
		vector<int> te;
		for(auto x:adj[i])
		{
			if(!vis[x.F]) te.push_back(x.S);
		}
		assert(te.size()==2);
		//eq.push_back({{min(te[0],te[1]),max(te[0],te[1])},arr[i]});
		adj2[te[0]].emplace_back(te[1],2*arr[i]);
		adj2[te[1]].emplace_back(te[0],2*arr[i]);
		if(mn==-1) mn=te[0];
		cur++;
	}
	if(cur%2==0&&cur)
	{
		cout << 0 << endl;
		return 0;
	}
	if(cur){
		int a=dfs1(mn,1,0,-1);
		a/=2;
		ans[mn]=a;
		dfs2(mn,0,-1);
	}
	for(int i=0;i<m;i++)
		printf("%d\n",ans[i]);
}
