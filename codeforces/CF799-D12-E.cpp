/*
Deciding how many common decoratins will they need decides the rest. We can try all possible. The rest is implementation details. I debugged for a long time to consider corner cases. The idea is easy but the implemntation was a nightmare for me.
*/

#include <bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,m,k;
vector< pair<int,int> > a,b,ab;
int arr[N],got[N],la[N];
int ord[N],plc[N];
long long btree[4*N],co[4*N];

bool cmp(int x,int y)
{
	return arr[x]<arr[y];
}

void update(int node,int l,int r,int ind,int aa,int bb)
{
	if(r<ind||l>ind) return;
	if(l==r)
	{
		btree[node]=aa;
		co[node]=bb;
		return;
	}
	int mid=(l+r)/2;
	if(ind<=mid) update(node*2,l,mid,ind,aa,bb);
	else update(node*2+1,mid+1,r,ind,aa,bb);
	btree[node]=btree[node*2]+btree[node*2+1];
	co[node]=co[node*2]+co[node*2+1];
}

long long query(int node,int l,int r,int x)
{
    //cout << node << " " << l << " " << r << " " << co[node] << " " << x << endl;
	if(x>co[node]) return (1LL<<60);
	if(x==co[node]) return btree[node];
	if(x==0) return 0;
	int mid=(l+r)/2;
	if(x<=co[node*2]) return query(node*2,l,mid,x);
	return btree[node*2]+query(node*2+1,mid+1,r,x-co[node*2]);
}

void add(int x)
{
    //cout << "Added " << arr[x] << endl;
	update(1,1,n,plc[x],arr[x],1);
}

void del(int x)
{
    //cout << "Deleted " << arr[x] << endl;
	update(1,1,n,plc[x],0,0);
}


int main()
{
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&arr[i]);
	int na,nb;
	scanf("%d",&na);
	for(int i=0;i<na;i++)
	{
		int x;
		scanf("%d",&x);
		a.push_back({arr[x],x});
		la[x]=1;
	}
	scanf("%d",&nb);
	for(int i=0;i<nb;i++)
	{
		int x;
		scanf("%d",&x);
		if(la[x]) {ab.push_back({arr[x],x}); la[x]=2;}
		else b.push_back({arr[x],x});
	}
	nb=b.size();
	for(int i=0;i<na;i++)
	{
		if(la[a[i].second]==2)
		{
			a[i].first=(1<<30);
		}
	}
	iota(ord,ord+n+1,0);
	sort(ord+1,ord+n+1,cmp);
	for(int i=1;i<=n;i++) plc[ord[i]]=i;
	for(int i=1;i<=n;i++)
		add(i);
	sort(a.begin(),a.end()); sort(b.begin(),b.end());
	sort(ab.begin(),ab.end());
	while(a.size() && a.back().first == (1<<30))
		a.pop_back();
	na=a.size();
	long long cans=0,ans=(1LL<<60);
	na=min(k,na); nb=min(k,nb);
	for(int i=0;i<na;i++)
	{
		del(a[i].second);
		cans+=a[i].first;
	}
	for(int i=0;i<nb;i++)
	{
		del(b[i].second);
		cans+=b[i].first;
	}
	int rem=m-2*k;
	if(rem>=0&&na==k&&nb==k)
	{
		ans=min(ans,cans+query(1,1,n,rem));
	}
	//cout << co[1] << endl;
	for(int i=0;i<ab.size();i++)
	{
		// will get i+1 in both
		// needs (k-(i+1)) a and (k-(i+1)) b
		del(ab[i].second);
		cans+=ab[i].first;
		int need=(k-(i+1));
		//if(need<0) continue;
		//if(i==4) cout << need << " " << co[1] << endl;
		if(min(a.size(),b.size())<need) continue;
		while(na&&na>need)
		{
			cans-=a[na-1].first;
			add(a[na-1].second); na--;
		}
		//cout << nb << " " << need << endl;
		while(nb&&nb>need)
		{
			cans-=b[nb-1].first;
			add(b[nb-1].second); nb--;
		}
		rem=m-(i+1+max(2*need,0));
		//cout << i+1 << " " << rem << " " << query(1,1,n,rem) << endl;
		if(rem>=0) ans=min(ans,cans+query(1,1,n,rem));
	}
	if(ans==(1LL<<60)) ans=-1;
	cout << ans << endl;
}
