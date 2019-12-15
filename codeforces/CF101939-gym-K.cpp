/*
There are two types of cuts we need to consider in each subtree of a node. The first is to make a cut an edge to split this subtree from your node then make another cut in the same subtree. The other is to cut two edges in two different subtrees. It can be proved than it's always optimal to make one of them in the subtree of the heavy child. To choose the optimal cut we can maintain a set for every child that has the sizes of subtrees of this child and buld them suing DSU on trees.
*/

#include <bits/stdc++.h>

using namespace std;

const int N=2e5+5;

vector<int> adj[N];
set<int> ss[N];
int sz[N];
int st[N],en[N],eul[N],dfstime;
int ans,n;

void pre(int node,int pa)
{
	st[node]=dfstime;
	eul[dfstime++]=node;
	sz[node]=1;
	for(int i:adj[node])
	{
		if(i==pa) continue;
		pre(i,node);
		sz[node]+=sz[i];
	}
	en[node]=dfstime-1;
}

int calc(int x,int y,int z,int node=-1)
{
	//cout << x << " " << y << "  " << z << " " << node << endl;
	return max(max(x,y),z)-min(min(x,y),z);
}

void dfs(int node,int pa)
{
	//cout << node << " : " << endl;
	int big=-1,szbig=0;
	for(int i:adj[node])
	{
		if(i==pa) continue;
		if(sz[i]>szbig) {szbig=sz[i]; big=i;}
	}
	for(int i:adj[node])
	{
		if(i==pa) continue;
		dfs(i,node);
		auto it=ss[i].lower_bound(sz[i]/2);
		// cut this edge , make another cut inside the subtree
		ans=min(ans,calc(*it,sz[i]-*it,n-sz[i]));
		if(it!=ss[i].begin())
		{
			it--;
			ans=min(ans,calc(*it,sz[i]-*it,n-sz[i]));
			it++;
		}
		if(it!=ss[i].end() && (++it!=ss[i].end()))
			ans=min(ans,calc(*it,sz[i]-*it,n-sz[i]));
		it--;
	}
	if(big!=-1)
	{
		ss[node].swap(ss[big]);
		//cut an edge in the big child + another edge
		for(int i:adj[node])
		{
			if(i==big || i==pa) continue;
			for(int j:ss[i])
			{
				int res=n-j;
				auto it=ss[node].lower_bound(res/2);
				if(it!=ss[node].end()) ans=min(ans,calc(*it,res-(*it),j));
				if(it!=ss[node].begin())
				{
					it--;
					ans=min(ans,calc(*it,res-*it,j));
					it++;
				}
				if(it!=ss[node].end() && (++it!=ss[node].end()))
					ans=min(ans,calc(*it,res-*(it),j));
				it--;
			}
		}
	}
	//if(big!=-1) dfs(big,1,node);
	for(int i:adj[node])
	{
		if(i==pa||i==big) continue;
		for(int j=st[i];j<=en[i];j++)
			ss[node].insert(sz[eul[j]]);
	}
	ss[node].insert(sz[node]);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	pre(1,-1);
	ans=n;
	dfs(1,-1);
	printf("%d\n",ans);
}
