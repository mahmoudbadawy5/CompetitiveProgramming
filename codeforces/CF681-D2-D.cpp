/*
You need to notice that you must want yourself or the one your parent wants or the one you wants will also be reachable by
your parent. So you can't satisfy your and your parent's wish at the same time.

The final answer can be get by sorting all the wish list by the decreasing order of height.
*/

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int pa[N],q[N];
int h[N];
int n,m;
vector<int> adj[N];

void go(int x)
{
	h[x]=h[pa[x]]+1;
	for(int i:adj[x])
		go(i);
}

bool cmp(int x,int y)
{
	return h[x]>h[y];
}

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=0;i<m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		pa[y]=x;
		adj[x].push_back(y);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&q[i]);
	for(int i=1;i<=n;i++)
	{
		if(!pa[i]) go(i);
		if(q[i]!=i&&q[i]!=q[pa[i]])
		{
			cout << -1 << endl;
			return 0;
		}
	}
	sort(q+1,q+n+1);
	n=unique(q+1,q+n+1)-(q+1);
	sort(q+1,q+n+1,cmp);
	cout << n << endl;
	for(int i=1;i<=n;i++)
		cout << q[i] << " ";
	cout << endl;
}
