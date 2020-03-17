/*
We need to know the pairs of containers that can't be on the same area. If we can build this graph then if all components are
bipartite then the answer is 2^number of components, otherwise it's 0.

We can notice that if two intervals intersects (and one isn't inside the other) they can't be in the same area. 

We can sort the events of opening and ending an interval and if we reached the end of an interval then we add an edge between
this interval and all intervals that started after it and didn't end. As all of them must be in opposite area than the current
interval we know that all of them must be in the same area so we can union all of them. We union all intervals until we reach
the group that contains the current interval and we have to erase it from the group. If there are intervals in this group started
after the current interval then it's a contradicition (They have to be on the same area and opposite areas at the same time).

We can use a deque and smaller to larger to keep the order of intervals in each group.
*/

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int N=1e6+6,MOD=1e9+7;

pair<int,int> arr[N];
int n;
stack<int> st;
int uni[N],sz[N];
deque<int> lst[N];
vector< pair<int,int> > ev,ed;
vector<int> adj[N];
int vis[N],col[N];

int uni_find(int x)
{
	return uni[x]=(uni[x]==x?x:uni_find(uni[x]));
}

void unio(int x,int y)
{
	int a=uni_find(x),b=uni_find(y);
	if(sz[a]>sz[b])
	{
		while(lst[b].size())
		{
			lst[a].push_back(lst[b].front()); lst[b].pop_front();
		}
		uni[b]=a;
		sz[a]+=sz[b];
	}
	else
	{
		while(lst[a].size())
		{
			lst[b].push_front(lst[a].back()); lst[a].pop_back();
		}
		uni[a]=b;
		sz[b]+=sz[a];
	}
}

bool go(int x,int c)
{
	if(vis[x])
		return col[x]==c;
	vis[x]=1; col[x]=c;
	bool ans=1;
	for(int i:adj[x])
		ans&=go(i,c^1);
	return ans;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		uni[i]=i; sz[i]=1; lst[i].push_back(i);
		scanf("%d %d",&arr[i].F,&arr[i].S);
		ev.push_back({arr[i].F,i});
		ev.push_back({arr[i].S,-i});
	}
	sort(ev.begin(),ev.end());
	for(int i=0;i<ev.size();i++)
	{
		//cout << ev[i].S << endl;
		if(ev[i].S>0)
		{
			int x=uni_find(ev[i].S);
			st.push(x);
		}
		else
		{
			int x=uni_find(-ev[i].S);
			int z=uni_find(st.top()); st.pop();
			if(z==x)
			{
				if(lst[z].back()!=-ev[i].S)
				{
					cout << 0 << endl;
					return 0;
				}
				sz[z]--;
				lst[z].pop_back();
				if(sz[z]) st.push(z);
				continue;
			}
			int y=uni_find(st.top()); st.pop();
			while(y!=x)
			{
				unio(y,z);
				y=uni_find(st.top()); st.pop();
			}
			if(lst[y].back()!=-ev[i].S)
			{
				cout << 0 << endl;
				return 0;
			}
			lst[y].pop_back();
			sz[y]--;
			if(sz[y]) st.push(y);
			st.push(z);
			ed.push_back({y,z});
		}
	}
	for(auto i:ed)
	{
		int x=uni_find(i.F),y=uni_find(i.S);
		//cout << x << " " << y << endl;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int x=uni_find(i);
		if(!vis[x])
		{
			ans++;
			if(!go(x,0))
			{
				cout << 0 << endl;
				return 0;
			}
		}
	}
	int cur=1;
	while(ans--) cur=(cur*2)%MOD;
	cout << cur << endl;
	return 0;
}
