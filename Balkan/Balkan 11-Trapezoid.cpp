/*
First we can notice that the answer will be an increasing sequence of intervals on both lines at the same time. We can sort
by the intervals on the upper line and use dp to calculate the LIS on the lower line. To count the numeber of ways we can use
another dp with compressing.*/

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5,MOD=30013;

struct trap{
	int l1,r1,l2,r2;
} arr[N];

vector<int> cmp;
int btree[2*N*4],stree[2*N*4],dp[N],dpways[N];
int sortl[N],sortr[N];
int n;

bool cmp1(int a,int b)
{
	return arr[a].l1<arr[b].l1;
}

bool cmp2(int a,int b)
{
	return arr[a].r1<arr[b].r1;
}

int get(int x)
{
	return lower_bound(cmp.begin(),cmp.end(),x)-cmp.begin()+1;
}

inline int add(int x,int y)
{
	int res=x+y;
	if(res<0) res+=MOD;
	if(res>=MOD) res-=MOD;
	return res;
}

void update(int node,int l,int r,int ind,int val)
{
	if(l==r)
	{
		btree[node]=val;
		return;
	}
	int mid=(l+r)/2;
	if(ind<=mid)
		update(node*2,l,mid,ind,val);
	else
		update(node*2+1,mid+1,r,ind,val);
	btree[node]=max(btree[node*2],btree[node*2+1]);
}


void update2(int node,int l,int r,int ind,int val)
{
	if(l==r)
	{
		stree[node]=val;
		return;
	}
	int mid=(l+r)/2;
	if(ind<=mid)
		update2(node*2,l,mid,ind,val);
	else
		update2(node*2+1,mid+1,r,ind,val);
	stree[node]=add(stree[node*2],stree[node*2+1]);
}

int query(int node,int l,int r,int ql,int qr)
{
	if(r<ql||qr<l) return 0;
	if(ql<=l&&r<=qr) return btree[node];
	int mid=(l+r)/2;
	return max(query(node*2,l,mid,ql,qr),query(node*2+1,mid+1,r,ql,qr));
}

int query2(int node,int l,int r,int ql,int qr)
{
	if(r<ql||qr<l) return 0;
	if(ql<=l&&r<=qr) return stree[node];
	int mid=(l+r)/2;
	return add(query2(node*2,l,mid,ql,qr),query2(node*2+1,mid+1,r,ql,qr));
}
vector< pair<int,int> > v;

int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d %d %d %d",&arr[i].l1,&arr[i].r1,&arr[i].l2,&arr[i].r2);
		cmp.push_back(arr[i].l2); cmp.push_back(arr[i].r2);
	}
	sort(cmp.begin(),cmp.end());
	cmp.erase(unique(cmp.begin(),cmp.end()),cmp.end());
	for(int i=0;i<n;i++)
	{
		arr[i].l2=get(arr[i].l2); arr[i].r2=get(arr[i].r2);
	}
	int m=cmp.size();
	iota(sortl,sortl+n,0); iota(sortr,sortr+n,0);
	sort(sortl,sortl+n,cmp1); sort(sortr,sortr+n,cmp2);
	int y=0;
	for(int i=0;i<n;i++)
	{
		int x=sortl[i];
		while(y<n&&arr[sortr[y]].r1<arr[x].l1)
		{
			update(1,0,m,arr[sortr[y]].r2,dp[sortr[y]]);
			y++;
		}
		dp[x]=1+query(1,0,m,0,arr[x].l2);
	}
	int maxi=0;
	for(int i=0;i<n;i++)
		maxi=max(maxi,dp[i]);
	for(int i=0;i<n;i++)
	{
		v.push_back({dp[i],arr[i].r2});
	}
	sort(v.begin(),v.end());
	y=0;
	for(int i=0;i<n;i++)
	{
		int x=sortl[i];
		while(y<n&&arr[sortr[y]].r1<arr[x].l1)
		{
			int yy=sortr[y];
			int myind=lower_bound(v.begin(),v.end(),make_pair(dp[yy],arr[yy].r2))-v.begin();
			update2(1,0,n-1,myind,dpways[yy]);
			y++;
		}
		if(dp[x]==1)
		{
			dpways[x]=1;
			continue;
		}
		int myind=lower_bound(v.begin(),v.end(),make_pair(dp[x]-1,0))-v.begin();
		int rr=upper_bound(v.begin()+myind,v.end(),make_pair(dp[x]-1,arr[x].l2))-v.begin()-1;
		dpways[x]=query2(1,0,n-1,myind,rr);
	}
	int ans=0;
	for(int i=0;i<n;i++)
	{
		if(dp[i]==maxi) ans=add(ans,dpways[i]);
	}
	cout << maxi << " " << ans << endl;
}
