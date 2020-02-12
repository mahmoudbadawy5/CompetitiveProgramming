/*
First, we will sort the songs by thier index.
We can use dp[index] that's the minimum number of points we need to cover the songs starting from index by grouping them into some groups. 
We can cover any song in the interval [arr[index],arr[index]+k-1] for the same cost which is k and after that if we want to add a song at
index x to the current group we have to pay x-arr[index]+1. So we have two types of costs ahead of us we can get the minimum dp
in front of dp for each type of costs using a segment tree.
*/

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int N=3e5+5;

pair<int,int> mem[N];
pair<int,int> btree[2][4*N];
pair<int,int> arr[N];
int n,k,m;

void update(int v,int node,int l,int r,int ind,pair<int,int> val)
{
	if(ind<l||ind>r) return;
	if(l==r)
	{
		btree[v][node]=val;
		return;
	}
	int mid=(l+r)/2;
	update(v,node*2,l,mid,ind,val);
	update(v,node*2+1,mid+1,r,ind,val);
	btree[v][node]=min(btree[v][node*2],btree[v][node*2+1]);
}

pair<int,int> query(int v,int node,int l,int r,int ql,int qr)
{
	if(r<ql||qr<l||qr<ql) return {(1<<30),0};
	if(ql<=l&&r<=qr)
		return btree[v][node];
	int mid=(l+r)/2;
	return min(query(v,node*2,l,mid,ql,qr),query(v,node*2+1,mid+1,r,ql,qr));
}

int l[N],r[N];

int main()
{
	scanf("%d%d%d",&n,&k,&m);
	for(int i=0;i<m;i++)
	{
		scanf("%d",&arr[i].F);
		arr[i].S=i;
	}
	for(int i=0;i<4*m;i++)
		btree[0][i]=btree[1][i]={(1<<30),0};
	sort(arr,arr+m);
	update(0,1,0,m,m,make_pair(0,m)); update(1,1,0,m,m,make_pair(arr[m-1].F,m));
	for(int i=m-1;i>=0;i--)
	{
		int ind=lower_bound(arr+i,arr+m,make_pair(arr[i].F+k,-1))-arr;
		auto a1=query(0,1,0,m,i+1,ind),a2=query(1,1,0,m,ind+1,m);
		mem[i]=min(make_pair(a1.F+k,a1.S),make_pair(a2.F-arr[i].F+1,a2.S));
		//cout << arr[i].F << " : " << mem[i].F << " " << mem[i].S << " " << a1.F << " " << a2.F << " " << arr[ind].F << endl;
		if(i)
		{
			update(0,1,0,m,i,make_pair(mem[i].F,i));
			update(1,1,0,m,i,make_pair(mem[i].F+arr[i-1].F,i));
		}
	}
	printf("%d\n",mem[0].F);
	for(int i=0;i<m;i++)
	{
		for(int j=i;j<mem[i].S;j++)
		{
			l[arr[j].S]=max(arr[j].F-k+1,arr[i].F);
			l[arr[j].S]=min(l[arr[j].S],n-k+1);
			r[arr[j].S]=l[arr[j].S]+k-1;
		}
		i=mem[i].S-1;
	}
	for(int i=0;i<m;i++)
		printf("%d %d\n",l[i],r[i]);
}
