/*
Let's assume that each city is asked 0 or 1 time only, as 2 times will have the same impact as 0 times. now If the i-th road
is already paved we need the total number of times its end points are entered to be an even number otherwise we need it to be
an odd number. That means if c[i] = 1 then num[a[i]]^num[b[i]] = 0 and 1 otherwise.
That can be solved with 2-sat
*/

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int N=105;

int col[N];
vector< pair<int,int> > adj[N];
int n,m;

int go(int x,int y)
{
	if(~col[x]) return (col[x]==y);
	col[x]=y;
	int ans=1;
	for(auto i:adj[x])
	{
		ans&=(go(i.F,i.S^y^1));
	}
	return ans;
}

int main()
{
	cin >> n >> m;
	for(int i=0;i<m;i++)
	{
		int a,b,c;
		cin >> a >> b >> c;
		adj[a].push_back({b,c});
		adj[b].push_back({a,c});
	}
	memset(col,-1,sizeof col);
	for(int i=1;i<=n;i++)
	{
		if(~col[i]) continue;
		if(!go(i,0))
		{
			cout << "Impossible" << endl;
			return 0;
		}
	}
	int z=count(col+1,col+1+n,1);
	cout << z << endl;
	for(int i=1;i<=n;i++)
		if(col[i]) cout << i << " ";
	cout << endl;
}
