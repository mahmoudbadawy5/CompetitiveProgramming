/*
A very nice problem. I made every answer in the form c[node]-height[node]*m[node] and manipulated the queries such that : c[i] = x + height[i]*k[i] , m[i]=k[i] that doesn't change the value. Now each query modifies a subtree so I can flatten the tree and use lazy propagation to update/answer in O(n+qlogn)
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=3e5+5,MOD=1e9+7;

ll btree[2][4*N],lazy[2][4*N];
int st[N],en[N],eul[N],hi[N],dfstime;
int n,q;
vector<int> adj[N];

void dfs(int node)
{
	st[node]=dfstime;
	eul[dfstime++]=node;
	for(int i:adj[node])
	{
		hi[i]=hi[node]+1;
		dfs(i);
	}
	en[node]=dfstime-1;
}

void prop(int x,int node,int l,int r)
{
	btree[x][node]+=lazy[x][node];
	btree[x][node]%=MOD;
	if(l!=r)
	{
		lazy[x][node*2]+=lazy[x][node];
		lazy[x][node*2+1]+=lazy[x][node];
	}
	lazy[x][node]=0;
}

void update(int x,int node,int l,int r,int ql,int qr,ll v)
{
	if(lazy[x][node]) prop(x,node,l,r);
	if(r<ql||qr<l) return;
	if(ql<=l&&r<=qr)
	{
		lazy[x][node]+=v;
		prop(x,node,l,r);
		return;
	}
	int mid=(l+r)/2;
	update(x,node*2,l,mid,ql,qr,v);
	update(x,node*2+1,mid+1,r,ql,qr,v);
}

ll query(int x,int node,int l,int r,int ql,int qr)
{
	if(lazy[x][node]) prop(x,node,l,r);
	if(r<ql||qr<l) return 0;
	if(ql<=l&&r<=qr) return btree[x][node];
	int mid=(l+r)/2;
	return query(x,node*2,l,mid,ql,qr)+query(x,node*2+1,mid+1,r,ql,qr);
}

int main()
{
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		adj[x].push_back(i);
	}
	dfs(1);
	scanf("%d",&q);
	while(q--)
	{
		int t;
		scanf("%d",&t);
		if(t==1)
		{
			int v,x,k;
			scanf("%d %d %d",&v,&x,&k);
			x=(x+1LL*hi[v]*k)%MOD;
			update(0,1,0,n-1,st[v],en[v],x);
			update(1,1,0,n-1,st[v],en[v],k);
		}
		else
		{
			int v;
			scanf("%d",&v);
			//printf("%d %d\n",query(0,1,0,n-1,st[v],st[v]),query(1,1,0,n-1,st[v],st[v]));
			ll ans=query(0,1,0,n-1,st[v],st[v])-1LL*hi[v]*query(1,1,0,n-1,st[v],st[v]);
			ans%=MOD;
			if(ans<0) ans+=MOD;
			printf("%lld\n",ans);
		}
	}
}
