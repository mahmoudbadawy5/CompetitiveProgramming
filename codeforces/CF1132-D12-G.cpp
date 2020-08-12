/*
  -Same as editorial: https://codeforces.com/blog/entry/65752
*/

#include <bits/stdc++.h>

using namespace std;

const int N=1e6+6,LG=22;

int n,k;
int arr[N],nxt[N];
vector<int> adj[N];
int st[N],en[N],eul[N],dfstime;
int btree[4*N],lazy[4*N];

void dfs(int x)
{
	st[x]=dfstime;
	eul[dfstime++]=x;
	for(int i:adj[x])
		dfs(i);
	en[x]=dfstime-1;
}

void prob(int node,int l,int r)
{
	btree[node]+=lazy[node];
	if(l!=r)
	{
		lazy[node<<1]+=lazy[node];
		lazy[(node<<1)|1]+=lazy[node];
	}
	lazy[node]=0;
}

void update(int node,int l,int r,int ql,int qr,int val)
{
	if(lazy[node]) prob(node,l,r);
	if(r<ql||qr<l) return;
	if(ql<=l&&r<=qr)
	{
		lazy[node]+=val;
		prob(node,l,r);
		return;
	}
	int mid=(l+r)>>1;
	update(node<<1,l,mid,ql,qr,val);
	update((node<<1)|1,mid+1,r,ql,qr,val);
	btree[node]=max(btree[node<<1],btree[(node<<1)|1]);
}

int main()
{
	scanf("%d %d",&n,&k);
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	stack<int> stk;
	for(int i=n-1;i>=0;i--)
	{
		while(stk.size() && arr[stk.top()]<=arr[i]) stk.pop();
		if(stk.size()) nxt[i]=stk.top();
		else nxt[i]=n;
		adj[nxt[i]].push_back(i);
		stk.push(i);
	}
	dfs(n);
	for(int i=0;i<k;i++)
	{
		update(1,0,n,st[i],en[i],1);
	}
	printf("%d",btree[1]);
	for(int i=k;i<n;i++)
	{
		update(1,0,n,st[i-k],en[i-k],-1);
		update(1,0,n,st[i],en[i],1);
		printf(" %d",btree[1]);
	}
	puts("");
}
