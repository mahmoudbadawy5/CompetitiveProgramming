/*
The problem asks for the number of triplets of nodes (a,b,c) such that dist(a,b) = dist(b,c) = dist(c,a) = d

An observation is that such triplet exists only when there is a center node x where dist(x,a) = dist(x,b) = dist(x,c) = d/2
So when d is odd the answer is 0

So we need now to count for each node x the number of nodes at distance d/2 from them and choose three of them in different subtrees
We can use centroid decomposition to count the number of such nodes and store them as a pair (node,subtree)

Then for each node we calculate the number of ways to choose 3 different subtrees and chose one node from each one
*/

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int h[N],sz[N],del[N];
map<int,int> co;
map<int,int> ans[N];
vector<int> adj[N];
int n,d,nn;

void dfs0(int x,int pa)
{
	sz[x]=1; nn++;
	for(int i:adj[x])
	{
		if(i==pa||del[i]) continue;
		dfs0(i,x);
		sz[x]+=sz[i];
	}
}

int getcentroid(int x,int pa)
{
	for(int i:adj[x])
	{
		if(i==pa||del[i]) continue;
		if(sz[i]>nn/2) return getcentroid(i,x);
	}
	return x;
}

void dfs(int x,int pa)
{
	h[x]=h[pa]+1;
	co[h[x]]++;
	for(int i:adj[x])
	{
		if(i==pa||del[i]) continue;
		dfs(i,x);
	}
}

void dfsadd(int x,int pa,int v)
{
	co[h[x]]+=v;
	for(int i:adj[x])
	{
		if(i==pa||del[i]) continue;
		dfsadd(i,x,v);
	}
}

void calc(int x,int pa)
{
	if(h[x]<=d) ans[x][pa]+=co[d-h[x]];
	for(int i:adj[x])
	{
		if(i==pa||del[i]) continue;
		calc(i,x);
	}
}

void centroid(int x)
{
	co.clear();
	nn=0;
	dfs0(x,0);
	int c=getcentroid(x,0);
	dfs(c,0);
	for(int i:adj[c])
	{
		if(del[i]) continue;
		dfsadd(i,c,-1);
		calc(i,c);
		dfsadd(i,c,1);
	}
	co.clear();
	for(int i:adj[c])
	{
		if(del[i]) continue;
		dfsadd(i,c,1);
		ans[c][i]+=co[d];
		dfsadd(i,c,-1);
	}
	del[c]=1;
	for(int i:adj[c])
		if(!del[i]) centroid(i);
}


int main()
{
	freopen("capitals.in","r",stdin); freopen("capitals.out","w",stdout); 
	scanf("%d %d",&n,&d);
	for(int i=0;i<n-1;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	h[0]=-1;
	if(d%2)
	{
		cout << 0 << endl;
		return 0;
	}
	d/=2;
	centroid(1);
	long long tot=0;
	for(int i=1;i<=n;i++)
	{
		if(ans[i].size()<3) continue;
		long long sq=0,sum=0;
		for(auto j:ans[i])
			sum+=j.second;
		for(auto j:ans[i])
			sq+=1LL*j.second*(sum-j.second);
		sq/=2;
		for(auto j:ans[i])
			tot+=1LL*j.second*(sq-1LL*j.second*(sum-j.second));
	}
	cout << tot/3 << endl;
}
