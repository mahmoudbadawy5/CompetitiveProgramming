/*
  - https://github.com/mostafa-saad/MyCompetitiveProgramming/tree/master/Olympiad/CEOI/official/2005
 */
 
 #include <bits/stdc++.h>

using namespace std;

const int N=405;

int n,m;
int arr[N][N];
vector<int> pos[N][N];
vector< pair<int,int> > adj[2*N];
vector<int> vis[2*N];
vector<int> st;

void go(int x)
{
	for(int i=0;i<adj[x].size();i++)
	{
		if(vis[x][i]) continue;
		vis[x][i]=1;
		go(adj[x][i].first);
		if(adj[x][i].second) st.push_back(adj[x][i].second);
	}
}

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=0;i<n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&arr[i][j]);
			pos[i][arr[i][j]].push_back(i*m+j);
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(pos[i][j].size()==0)
			{
				adj[i].push_back({n+j-1,0});
				vis[i].push_back(0);
			}
			else
			{
				for(int k=1;k<pos[i][j].size();k++)
				{
					adj[n+j-1].push_back({i,pos[i][j][k]});
					vis[n+j-1].push_back(0);
				}
			}
		}
	}
	vector< pair<int,int> > ans;
	for(int i=0;i<n+m;i++)
	{
		st.clear();
		go(i);
		if(st.size())
		{
			reverse(st.begin(),st.end());
			ans.push_back({st[0],n*m+1});
			for(int j=1;j<st.size();j++)
				ans.push_back({st[j],st[j-1]});
			ans.push_back({n*m+1,st.back()});
		}
	}
	cout << ans.size() << endl;
	for(auto i:ans)
		cout << i.first << " " << i.second << endl;
}
