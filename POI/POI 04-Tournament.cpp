/*
  Same as: https://github.com/thecodingwizard/competitive-programming/blob/master/POI/POI04-Tournament.cpp
  */
  
  #include <bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int vis[N],in[N];
vector<int> topo;
vector<int> adj[N];
int n;

void dfs(int x)
{
	if(vis[x]) return;
	vis[x]=1;
	for(int i:adj[x])
		dfs(i);
	topo.push_back(x);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int sz;
		scanf("%d",&sz);
		while(sz--)
		{
			int x;
			scanf("%d",&x);
			adj[i].push_back(x);
		}
	}
	for(int i=1;i<=n;i++) if(!vis[i]) dfs(i);
	vector<int> ans;
	reverse(topo.begin(),topo.end());
	int cured=0;
	for(int i:topo)
	{
		ans.push_back(i);
		vis[i]=2;
		cured-=in[i];
		for(int j:adj[i])
		{
			if(vis[j]==2) continue;
			cured++;
			in[j]++;
		}
		if(cured==1LL*ans.size()*(n-ans.size()))
		{
			break;
		}
	}
	sort(ans.begin(),ans.end());
	cout << ans.size();
	for(int i:ans) cout << " " << i;
	cout << endl;
}
