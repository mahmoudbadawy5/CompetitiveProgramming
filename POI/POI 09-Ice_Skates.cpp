/*
Let's denote the number needed of shoes needed from the range [i,i+d] to be dp[i] (and can't be done with size i-1)
we can deduce that dp[i]=max(dp[i-1]-k,0) + need[i]
We need to make sure that max(dp[i]) <= k*(d+1)
We can notice that this is like calculating the maximum subarray sum if arr[i]=need[i]-k
and we need to make sure that this value is <= k*d
We can maintain the maximum subarray sum updates with segment tree (See GSS family problems on spoj for a similiar problem)
*/

#include <bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,m,k,d;

struct seg{
	long long sum,mxl,mxr,bst;
} btree[4*N];

seg add(seg a,seg b)
{
	seg ret;
	ret.sum=a.sum+b.sum;
	ret.mxl=max(a.mxl,a.sum+b.mxl);
	ret.mxr=max(b.mxr,b.sum+a.mxr);
	ret.bst=max(max(max(ret.mxl,ret.mxr),max(a.bst,b.bst)),max(ret.sum,a.mxr+b.mxl));
	return ret;
}

void build(int node,int l,int r)
{
	if(l==r)
	{
		btree[node]={-k,-k,-k,-k};
		return;
	}
	int mid=(l+r)>>1;
	build(node<<1,l,mid);
	build((node<<1)|1,mid+1,r);
	btree[node]=add(btree[node<<1],btree[(node<<1)|1]);
}

void update(int node,int l,int r,int ind,int v)
{
	if(ind<l||ind>r) return;
	if(l==r)
	{
		btree[node].sum+=v;
		btree[node].mxl+=v;
		btree[node].mxr+=v;
		btree[node].bst+=v;
		return;
	}
	int mid=(l+r)>>1;
	update(node<<1,l,mid,ind,v);
	update((node<<1)|1,mid+1,r,ind,v);
	btree[node]=add(btree[node<<1],btree[(node<<1)|1]);
}

int main()
{
	scanf("%d %d %d %d",&n,&m,&k,&d);
	build(1,1,n);
	while(m--)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		update(1,1,n,x,y);
		/*for(int i=1;i<=4;i++)
			cout << btree[i].bst << " " << btree[i].sum << " " << btree[i].mxl << " " << btree[i].mxr << endl;*/
		puts(btree[1].bst<=1LL*k*d?"TAK":"NIE");
	}
}
