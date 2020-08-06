/*
You can go from any city x to y that's in a distance 2 from it if there's another city z between them that's connected to them with the same color.
So let's consider a new graph that has an edge between x and y. To add the edges quickly we need for each node to add edges between all nodes connected to it with
the same color so we can use a DSU to maintain the new graph.

Now that solves the case where k is odd. what about when there is an extra edge at the end of the path? We can split the nodes into two types: big and small where
small nodes are nodes with less than SQRT negibours (as the queries are online all nodes start as small and change to big when they exceed SQRT negibours).

When we are asked about whether we can go from x to y and y is a small node we can just check all negibours of y if x can reach them. If y is a big node we can store
all componenets of nodes connected directly to y and update them with each merge operation (as the number of big nodes can't exceed sqrt).
*/

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5,SQ=400;

int n,m,c,q;
vector<int> adj[N];
int uni[N];
set<int> cmp[N];
map<int,int> col[N];
vector<int> big;


int uni_find(int x)
{
	return uni[x]=(uni[x]==x?x:uni_find(uni[x]));
}

void unio(int x,int y)
{
	x=uni_find(x); y=uni_find(y);
	if(x==y) return;
	uni[x]=y;
	for(int i:big)
	{
		if(cmp[i].find(x)!=cmp[i].end())
		{
			cmp[i].erase(x);
			cmp[i].insert(y);
		}
	}
}

void makebig(int x)
{
	big.push_back(x);
	cmp[x].clear();
	for(int i:adj[x])
		cmp[x].insert(uni_find(i));
}

void addedge(int x,int y,int c)
{
	adj[x].push_back(y);
	int &r=col[x][c];
	if(r) unio(y,r);
	else r=uni_find(y);
	cmp[x].insert(uni_find(r));
	if(adj[x].size()==SQ)
		makebig(x);
}

int okbig(int x,int y)
{
	x=uni_find(x);
	return cmp[y].find(x)!=cmp[y].end();
}

int oksmall(int x,int y)
{
	x=uni_find(x);
	for(int i:adj[y])
	{
		if(uni_find(i)==x) return 1;
	}
	return 0;
}

int main()
{
	scanf("%d %d %d %d",&n,&m,&c,&q);
	iota(uni+1,uni+n+1,1);
	while(m--)
	{
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		addedge(a,b,c); addedge(b,a,c);
	}
	while(q--)
	{
		char t;
		int x,y;
		scanf(" %c %d %d",&t,&x,&y);
		if(t=='?')
		{
			int ok=uni_find(x)==uni_find(y);
			if(adj[y].size()>=SQ)
				ok|=okbig(x,y);
			else
				ok|=oksmall(x,y);
			puts(ok?"Yes":"No");
		}
		else
		{
			int z;
			scanf("%d",&z);
			addedge(x,y,z); addedge(y,x,z);
		}
	}
}
