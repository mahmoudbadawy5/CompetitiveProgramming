/*
It can be solved as normal LIS problem but we need only to consider the edges in that has ending point equal to the current
edge's start point. You can group all edges with the same end point to be consecutive in a segment tree and compress
the values.
*/

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int N=1e5+5;

vector<int> adj[N];
pair< pair<int,int> , int > ed[N];
int st[N];
int n,m;
int btree[4*N*2];

int query(int node,int l,int r,int ql,int qr)
{
	if(qr<ql) return 0;
	if(r<ql||qr<l) return 0;
	if(ql<=l&&r<=qr) return btree[node];
	int mid=(l+r)/2;
	return max(query(node*2,l,mid,ql,qr),query(node*2+1,mid+1,r,ql,qr));
}

void update(int node,int l,int r,int ind,int val)
{
	if(ind<l||ind>r) return;
	if(l==r)
	{
		btree[node]=max(btree[node],val);
		return;
	}
	int mid=(l+r)/2;
	update(node*2,l,mid,ind,val);
	update(node*2+1,mid+1,r,ind,val);
	btree[node]=max(btree[node*2],btree[node*2+1]);
}

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=0;i<m;i++)
	{
		scanf("%d %d %d",&ed[i].F.F,&ed[i].F.S,&ed[i].S);
		adj[ed[i].F.F].push_back(ed[i].S);
		adj[ed[i].F.S].push_back(ed[i].S);
	}
	int nn=0;
	for(int i=1;i<=n;i++)
	{
		sort(adj[i].begin(),adj[i].end());
		adj[i].erase(unique(adj[i].begin(),adj[i].end()),adj[i].end());
		st[i]=nn;
		nn+=adj[i].size();
	}
	int mx=0;
	for(int i=0;i<m;i++)
	{
		int x=ed[i].F.F,y=ed[i].F.S,z=ed[i].S;
		int l=lower_bound(adj[x].begin(),adj[x].end(),z)-adj[x].begin();
		int ans=query(1,0,nn-1,st[x],st[x]+l-1)+1;
		l=lower_bound(adj[y].begin(),adj[y].end(),z)-adj[y].begin();
		update(1,0,nn-1,st[y]+l,ans);
		mx=max(mx,ans);
	}
	cout << mx << endl;
}
