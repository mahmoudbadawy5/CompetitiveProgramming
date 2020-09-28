/*
We will do a normal dijkstra with some tricks for the first type we will do the normal thing. For the second type from v -> [l,r] we can add a dummy node u
so it becomes v -> u -> [l,r] the edge u -> [l,r] is with cost = 0 so when we need to proccess the dummy node u we can proccess all nodes from [l,r] that aren't
proccessed yet. For the third type of queries [l,r] -> v we can notice that the first node from [l,r] that gets proccessed is the only one that needs that edge.
All other nodes will reach v with a cost that's not better than the first one wo we for each node we will iterate over all intervals that includes it.
*/

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int N=1e5+5;

int n,m,x;
vector< pair<int,int> > adj[N];
set<int> np;
vector<pair< pair<int,int>, int> > s2[N];
long long dis[2*N];
pair<pair<int,int>,long long>  nn[2*N];
set<pair<long long,int> > q;
int curnode;


set< pair<int,int> > s3[4*N];

void add(int node,int l,int r,int ql,int qr,int v,int val)
{
	if(r<ql||qr<l) return;
	if(ql<=l&&r<=qr)
	{
		s3[node].insert({val,v});
		return;
	}
	int mid=(l+r)>>1;
	add(node<<1,l,mid,ql,qr,v,val);
	add((node<<1)|1,mid+1,r,ql,qr,v,val);
}



void relax(int node,long long v)
{
	if(!np.count(node)) return;
	if(dis[node]!=-1&&dis[node]<v) return;
	dis[node]=v;
	q.insert({dis[node],node});
}


void doit(int node,int l,int r,int x)
{
	if(x<l||x>r) return;
	// x in range[l,r]
	for(auto i:s3[node])
	{
		relax(i.S,i.F+dis[x]);
	}
	s3[node].clear();
	if(l==r) return;
	int mid=(l+r)>>1;
	doit(node<<1,l,mid,x);
	doit((node<<1)|1,mid+1,r,x);
}

void proc(int x)
{
	np.erase(x);
	// T1
	for(auto i:adj[x])
	{
		int nx=i.F,v=i.S;
		relax(nx,v+dis[x]);
	}
	// T2
	for(auto i:s2[x])
	{
		nn[curnode]=i;
		nn[curnode].S+=dis[x];
		np.insert(curnode);
		relax(curnode,i.S+dis[x]);
		curnode++;
	}
	// T3
	doit(1,1,n,x);
}

int main()
{
	scanf("%d %d %d",&n,&m,&x);
	curnode=n+1;
	for(int i=0;i<m;i++)
	{
		int t;
		scanf("%d",&t);
		if(t==1)
		{
			int x,y,z;
			scanf("%d %d %d",&x,&y,&z);
			adj[x].push_back({y,z});
		}
		else if(t==2)
		{
			int v,l,r,z;
			scanf("%d %d %d %d",&v,&l,&r,&z);
			s2[v].push_back({{l,r},z});
		}
		else
		{
			int l,r,v,z;
			scanf("%d %d %d %d",&v,&l,&r,&z);
			add(1,1,n,l,r,v,z);
		}
	}
	for(int i=1;i<=n;i++)
		if(i!=x) np.insert(i);
	memset(dis,-1,sizeof dis);
	dis[x]=0;
	q.insert({0,x});
	while(q.size())
	{
		int cx=(*q.begin()).S; long long cv=(*q.begin()).F;
		q.erase(q.begin());
		if(dis[cx]!=cv) continue;
		if(cx>n)
		{
			int l=nn[cx].F.F,r=nn[cx].F.S;
			long long v=nn[cx].S;
			while(true)
			{
				auto nx=np.lower_bound(l);
				if(nx==np.end()) break;
				int z=*nx;
				if(z>r) break;
				dis[z]=v;
				proc(z);
			}
		}
		else proc(cx);
	}
	for(int i=1;i<=n;i++)
		printf("%lld ",dis[i]);
	puts("");
}
