/*
We will construct the answer from the beginning as pairs then delete the pair and solve the problem on the small array.
For each pair we need to get the smallest possible pair. The pair is valid only if the first one is in even index and the second element is after the first and
in an odd index. to keep the smallest element in even and odd indices we can use segment tree.
*/

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int N=2e5+5;

pair<int,int> btree[4*N];
int lazy[4*N];
int arr[N],pos[N];
set<int> ss;
int n;

pair<int,int> merge(pair<int,int> a,pair<int,int> b)
{
	return {min(a.F,b.F),min(a.S,b.S)};
}

void build(int node,int l,int r)
{
	if(l==r)
	{
		if(l%2==0)
			btree[node]={arr[l],(1<<30)};
		else
			btree[node]={(1<<30),arr[l]};
		return;
	}
	int mid=(l+r)>>1;
	build(node<<1,l,mid);
	build((node<<1)|1,mid+1,r);
	btree[node]=merge(btree[node<<1],btree[(node<<1)|1]);
}

void push(int node,int l,int r)
{
	if(!lazy[node]) return;
	swap(btree[node].F,btree[node].S);
	if(l!=r)
	{
		lazy[node<<1]^=1;
		lazy[(node<<1)|1]^=1;
	}
	lazy[node]=0;
}

void update(int node,int l,int r,int ind)
{
	if(lazy[node]) push(node,l,r);
	if(ind<l||ind>r) return;
	if(l==r)
	{
		btree[node]={(1<<30),(1<<30)};
		return;
	}
	int mid=(l+r)>>1;
	update(node<<1,l,mid,ind);
	update((node<<1)|1,mid+1,r,ind);
	btree[node]=merge(btree[node<<1],btree[(node<<1)|1]);
}

void update(int node,int l,int r,int ql,int qr)
{
	if(lazy[node]) push(node,l,r);
	if(r<ql||qr<l) return;
	if(ql<=l&&r<=qr)
	{
		lazy[node]=1; push(node,l,r); return;
	}
	int mid=(l+r)>>1;
	update(node<<1,l,mid,ql,qr);
	update((node<<1)|1,mid+1,r,ql,qr);
	btree[node]=merge(btree[node<<1],btree[(node<<1)|1]);
}

pair<int,int> query(int node,int l,int r,int ql,int qr)
{
	if(lazy[node]) push(node,l,r);
	if(r<ql||qr<l) return {(1<<30),(1<<30)};
	if(ql<=l&&r<=qr) return btree[node];
	int mid=(l+r)>>1;
	return merge(query(node<<1,l,mid,ql,qr),query((node<<1)|1,mid+1,r,ql,qr));
}

int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
		pos[arr[i]]=i;
	}
	build(1,0,n-1);
	ss.insert(n);
	for(int i=0;i<n;i+=2)
	{
		int x=query(1,0,n-1,0,n-1).F;
		int e=*ss.lower_bound(pos[x]);
		int y=query(1,0,n-1,pos[x],e-1).S;
		update(1,0,n-1,pos[x]); update(1,0,n-1,pos[y]);
		update(1,0,n-1,pos[x],pos[y]);
		ss.insert(pos[x]); ss.insert(pos[y]);
		printf("%d %d ",x,y);
	}
	puts("");
}
