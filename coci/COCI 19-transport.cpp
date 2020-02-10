/*
Let's solve it for paths that passes through a node v. How? We can root the tree at the node v and see for each node the minimum
fuel in the car's tank during going to the node v and if it's >=0 we can go to node v with fuel sum(nodes on the path)-sum(edges).
Also for each node we need to calculate the minimum amount of fuel in the car on the path from v to it. now with BIT we can
calculate for each valid starting point the number of valid ending points.

We can erase v from the tree then calculate for each subtree individually but how to do it in O(nlogn) time? We can use 
centroid decomposition
*/


#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int N=1e5+5;

vector< pair<int,int> > adj[N];
int arr[N],sz[N],del[N];
long long up[N],down[N],bit[N];
long long ans;
int n,nn;

void upd(int x,int v)
{
	for(;x<N;x+=x&(-x))
		bit[x]+=v;
}

int query(int x)
{
	int ans=0;
	for(;x>0;x-=x&(-x))
		ans+=bit[x];
	return ans;
}

void dfs(int node,int pa)
{
	sz[node]=1; nn++;
	for(auto i:adj[node])
	{
		if(del[i.F]||i.F==pa) continue;
		dfs(i.F,node);
		sz[node]+=sz[i.F];
	}
}

vector<int> cmp;

int getcent(int node,int pa)
{
	for(auto i:adj[node])
	{
		if(del[i.F]||i.F==pa) continue;
		if(sz[i.F]>nn/2)
			return getcent(i.F,node);
	}
	return node;
}

int curc;

void calc(int node,int pa,long long a,long long bb,long long b,long long c)
{
	if(min(arr[node]-c,arr[node]-c+a)>=0) up[node]=b-c+arr[node]+(node==curc?0:arr[curc]);
	else up[node]=-1;
	down[node]=min(bb,b-c);
	//cout << node << " " << up[node] << " " << down[node] << " " << pa << endl;
	//cout << node << " " << up[node] << " " << down[node] << endl;
	if(up[node]!=-1) cmp.push_back(-up[node]); cmp.push_back(down[node]);
	for(auto i:adj[node])
	{
		if(del[i.F]||pa==i.F) continue;
		calc(i.F,node,min(arr[node]-c,arr[node]-c+a),min(down[node],b-c),b+arr[node]-c-(pa==-1?arr[node]:0),i.S);
	}
}

void add(int node,int pa,int v,int rep=0)
{
	if(rep)
	{
		up[node]=lower_bound(cmp.begin(),cmp.end(),-up[node])-cmp.begin();
		down[node]=lower_bound(cmp.begin(),cmp.end(),down[node])-cmp.begin();
	}
	upd(cmp.size()-down[node],v);
	for(auto i:adj[node])
	{
		if(del[i.F]||i.F==pa) continue;
		add(i.F,node,v,rep);
	}
}

void calcAns(int node,int pa)
{
	ans+=query(cmp.size()-up[node]);
	for(auto i:adj[node])
	{
		if(del[i.F]||i.F==pa) continue;
		calcAns(i.F,node);
	}
}

void solve(int x)
{
	nn=0;
	dfs(x,-1);
	int c=getcent(x,-1);
	cmp.clear();
	curc=c;
	calc(c,-1,0,0,0,0);
	sort(cmp.begin(),cmp.end()); cmp.erase(unique(cmp.begin(),cmp.end()),cmp.end());
	for(int i=1;i<=cmp.size();i++) bit[i]=0;
	add(c,-1,1,1);
	for(auto i:adj[c])
	{
		if(del[i.F]) continue;
		add(i.F,c,-1);
		calcAns(i.F,c);
		add(i.F,c,1);
	}
	del[c]=1;
	ans+=query(cmp.size()-up[c]); ans--;
	for(auto i:adj[c])
	{
		if(del[i.F]) continue;
		solve(i.F);
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&arr[i]);
	for(int i=1;i<n;i++)
	{
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		adj[x].push_back({y,z});
		adj[y].push_back({x,z});
	}
	solve(1);
	printf("%lld\n",ans);
}
