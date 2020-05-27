/*
Let's calculate the minimum length of a string using BFS. We will start from the mid of the string and the only state we need
to store is [start node,end node] and we are sure the current string is a palindrome. We can make a transition to another
state by adding a character to the beginning and the end of the current string but that leads to O(n^2 * n^2) time.
To improve it we can add a charcter to the begin of the string then add the same character to the end.

We can make 26*n dummy nodes that can be the current end of the string that represents (x,c) where x is a node and c is a character.
That means we are currently at node x and we need to add an edge with character c (because we already added one at the begin).

Now the time is O(n^3*26) which is enough to pass. To consider the odd case palindrome we can add each edge as a starting point
in the bfs.
*/

#include <bits/stdc++.h>

using namespace std;

const int N=405;

vector<int> adj[N][26];
vector<int> iadj[N][26];
int dis[N][N+N*26];
pair<pair<int,int>,char> pa[N][N+N*26];
queue< pair<int,int> > q;
int n,m;

void bfs()
{
	while(!q.empty())
	{
		auto p=q.front(); q.pop();
		//cout << p.first << " "<< p.second << endl;
		if(p.second>n)
		{
			// need to fix
			int x=p.first,y=(p.second-n)/26,c=(p.second-n)%26;
			for(int i:adj[y][c])
			{
				if(dis[x][i]==(1<<30))
				{
					pa[x][i]={{x,p.second},'0'};
					dis[x][i]=dis[x][p.second]+1;
					q.push({x,i});
				}
			}
		}
		else
		{
			int x=p.first,y=p.second;
			for(int i=0;i<26;i++)
			{
				for(int j:iadj[x][i])
				{
					int nx=j,ny=n+y*26+i;
					if(dis[nx][ny]==(1<<30))
					{
						pa[nx][ny]={{x,y},i+'a'};
						dis[nx][ny]=dis[x][y]+1;
						q.push({nx,ny});
					}
				}
			}
		}
	}
}

string build(int x,int y)
{
	string ans="";
	while(x!=-1)
	{
		char z=pa[x][y].second;
		if(z!='0') ans+=z;
		int ox=x,oy=y;
		x=pa[ox][oy].first.first;
		y=pa[ox][oy].first.second;
	}
	string ans2=ans;
	if(y!=-1)
		ans2.pop_back();
	reverse(ans2.begin(),ans2.end());
	return ans+ans2;
}

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		dis[i][i]=0;
		q.push({i,i});
		pa[i][i]={{-1,-1},'0'};
		for(int j=1;j<=n+26*(n+1);j++)
		{
			if(i!=j) dis[i][j]=(1<<30);
		}
	}
	for(int i=0;i<m;i++)
	{
		int x,y;
		char c;
		scanf("%d %d %c ",&x,&y,&c);
		adj[x][c-'a'].push_back(y);
		iadj[y][c-'a'].push_back(x);
		dis[x][y]=1;
		pa[x][y]={{-1,1},c};
		q.push({x,y});
	}
	bfs();
	int qu;
	scanf("%d",&qu);
	int las; scanf("%d",&las);
	for(int i=1;i<qu;i++)
	{
		int cur;
		scanf("%d",&cur);
		if(dis[las][cur]==(1<<30))
			puts("-1");
		else
			printf("%d %s\n",dis[las][cur],build(las,cur).c_str());
		las=cur;
	}
}
