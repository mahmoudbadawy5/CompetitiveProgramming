/*
 Intersting problem, We can find for each number the nearest number which is coprime with it using binary search. To cheack we find the number of elements in this range that's divisible by at least one prime factor of the original number. That can be done by inclusion-exclusion.
 */
 #include <bits/stdc++.h>

using namespace std;

const int N=5e5+5;

int arr[N],r[N],btree[N];
vector<int> divi[N],pdiv[N],pos[N];
int cx[N];
int n,q;

void sieve()
{
	for(int i=2;i<N;i++)
	{
		if(pdiv[i].size()) continue;
		for(int j=i;j<N;j+=i)
			pdiv[j].push_back(i);
	}
	for(int i=1;i<N;i++)
	{
		for(int j=1;j*j<=i;j++)
		{
			if(i%j==0)
			{
				divi[i].push_back(j);
				if(j!=i/j) divi[i].push_back(i/j);
			}
		}
	}
}

int get(int x,int l,int r)
{
	int ll=cx[x];
	int rr=upper_bound(pos[x].begin(),pos[x].end(),r)-pos[x].begin();
	return max(rr-ll,0);
}

bool can(int l,int r)
{
	int x=arr[l];
	//cout << x << " : " << r << endl;
	vector<int> v=pdiv[x];
	int cur=0;
	for(int i=1;i<(1<<v.size());i++)
	{
		int sgn=(__builtin_popcount(i)%2?1:-1);
		int curn=1;
		for(int j=0;j<v.size();j++)
		{
			if((i&(1<<j))==0) continue;
			curn*=v[j];
		}
		cur+=sgn*get(curn,l,r);
	}
	return cur!=(r-l+1);
}

void build(int node,int a,int b)
{
	if(a==b)
	{
		btree[node]=r[a];
		return;
	}
	int mid=(a+b)/2;
	build(node*2,a,mid);
	build(node*2+1,mid+1,b);
	btree[node]=min(btree[node*2],btree[node*2+1]);
}

int query(int node,int a,int b,int ql,int qr)
{
	if(b<ql||qr<a) return n;
	if(ql<=a&&b<=qr) return btree[node];
	int mid=(a+b)/2;
	return min(query(node*2,a,mid,ql,qr),query(node*2+1,mid+1,b,ql,qr));
}

int main()
{
	sieve();
	scanf("%d %d",&n,&q);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
		for(int j:divi[arr[i]])
			pos[j].push_back(i);
	}
	for(int i=0;i<n;i++)
	{
		int st=i+1,en=n-1,ans=n;
		for(int x:divi[arr[i]])
		{
			cx[x]=lower_bound(pos[x].begin(),pos[x].end(),i)-pos[x].begin();
		}
		while(st<=en)
		{
			int mid=(st+en)/2;
			if(can(i,mid)){
				ans=mid;
				en=mid-1;
			}
			else st=mid+1;
		}
		r[i]=ans;
	}
	build(1,0,n-1);
	while(q--)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		a--; b--;
		int mn=query(1,0,n-1,a,b);
		if(mn<=b)
			puts("S");
		else
			puts("N");
	}
}
