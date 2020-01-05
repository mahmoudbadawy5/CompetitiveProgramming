/*
Instead of destroying edges we can add them in reversed order. When adding an edge let's add the smaller component to the larger one
We can keep the count of xors from nodes to the root. This gives an O(nlog^2(n)) solution.
*/

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int N=1e5+5;

int uni[N],sz[N],xr[N];
map<int,int> co[N];
pair<pair<int,int> ,int > arr[N];
int ord[N];
long long ans[N];
long long cur;
vector< pair<int,int> > adj[N];
int n; 

int uni_find(int x)
{
	return uni[x]=(uni[x]==x?x:uni_find(uni[x]));
}

void dfs(int node,int pa,int ot,int c)
{
	uni[node]=ot;
	sz[ot]++;
	if(pa==-1) xr[node]=0;
	// xr[node] ^ 
	cur+=co[ot][xr[node]^c];
	//co[ot][xr[node]^c]++;
	for(auto i:adj[node])
	{
		if(i.F==pa) continue;
		xr[i.first]=xr[node]^i.second;
		dfs(i.first,node,ot,c);
	}
}

void upd(int node,int pa,int ot,int c)
{
	xr[node]^=c;
	co[ot][xr[node]]++;
	for(auto i:adj[node])
	{
		if(i.F==pa) continue;
		upd(i.F,node,ot,c);
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d %d %d",&arr[i].F.F,&arr[i].F.S,&arr[i].S);
	}
	for(int i=0;i<n-1;i++)
		scanf("%d",&ord[i]);
	for(int i=1;i<=n;i++)
	{
		uni[i]=i; sz[i]=1;
		co[i][0]=1;
	}
	for(int i=n-2;i>=0;i--)
	{
		int x=arr[ord[i]].F.F,y=arr[ord[i]].F.S,z=arr[ord[i]].S;
		int a=uni_find(x),b=uni_find(y);
		if(sz[a]>sz[b])
		{
			swap(a,b);
			swap(x,y);
		}
		dfs(x,-1,b,z^xr[y]);
		upd(x,-1,b,z^xr[y]);
		adj[x].push_back({y,z});
		adj[y].push_back({x,z});
		ans[i]=cur;
	}
	for(int i=0;i<n-1;i++)
		printf("%lld\n",ans[i]);
	puts("0");
}
