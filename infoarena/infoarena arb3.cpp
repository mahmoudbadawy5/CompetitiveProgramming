/*
Let's get the number of times my parent needs to be intered to be passed y times. when node x is passed by y times then it'll
have the value (arr[x]-y) and all values larger than it will also be (arr[x]-y). What about values that's smaller than it?
If this value was already less than or equal (arr[x]-y) we don't need to consider them. Otherwise they will become (arr[x]-y+1)
We can use accumulative sum to calculate the number of operations each value needs to reach its goal.
Then use the number of operations needed from the parent again to calculate the total number of operations needed
*/

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
vector<int> adj[N];
vector<int> sums[N];
int pa[N],arr[N];

int get(int node,int l,int r,int to)
{
	if(l>r||l>=adj[node].size()) return 0;
	return sums[node][r]-(l?sums[node][l-1]:0)-to*(r-l+1);
}

int solve(int node,int val)
{
	if(!pa[node]) return val;
	int x=arr[node]-val,p=pa[node];
	int myind=lower_bound(adj[p].begin(),adj[p].end(),arr[node])-adj[p].begin();
	int lasind=lower_bound(adj[p].begin(),adj[p].end(),x+1)-adj[p].begin();
	return solve(p,get(p,myind,adj[p].size()-1,x)+get(p,lasind,myind-1,x+1));

}

int main()
{
	freopen("arb3.in","r",stdin); freopen("arb3.out","w",stdout);
	scanf("%d %d",&n,&q);
	for(int i=2;i<=n;i++)
		scanf("%d",&pa[i]);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&arr[i]);
		adj[pa[i]].push_back(arr[i]);
	}
	for(int i=1;i<=n;i++)
	{
		if(!adj[i].size()) continue;
		sort(adj[i].begin(),adj[i].end());
		sums[i].push_back(adj[i][0]);
		for(int j=1;j<adj[i].size();j++)
			sums[i].push_back(sums[i].back()+adj[i][j]);
	}
	while(q--)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		printf("%d\n",solve(x,y));
	}
}
