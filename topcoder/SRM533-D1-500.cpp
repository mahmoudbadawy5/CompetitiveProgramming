/*
Conseder there is n+m nodes in a graph. Each magical cell makes you go from a row to column or column to row so we can consider each magical cell as an edge from
its row to its column and the other way.
Now we want to visit each edge once we can chech it as hamiltonian cycle (starting from row) (or path that starts from row and goes to column)
also we need to check if the graph is connected or not
*/

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<int> adj[105];
int vis[105];

void go(int x)
{
	if(vis[x]) return;
	vis[x]=1;
	for(int i:adj[x])
		go(i);
}

class MagicBoard {
public:
	string ableToUnlock(vector <string> gr) {
		int n=gr.size(),m=gr[0].size();
		for(int i=0;i<n+m;i++)
		{
			vis[i]=0;
			adj[i].clear();
		}
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				if(gr[i][j]=='#')
				{
					adj[i].push_back(j+n);
					adj[j+n].push_back(i);
				}
			}
		}
		for(int i=0;i<n+m;i++)
		{
			if(adj[i].size()) {go(i);break;}
		}
		for(int i=0;i<n+m;i++)
		{
			if(adj[i].size()&&vis[i]==0) return "NO";
		}
		int a=0,b=0;
		for(int i=0;i<n;i++) a+=adj[i].size()%2;
		for(int i=n;i<n+m;i++) b+=adj[i].size()%2;
		if((a==1&&b==1) || (a==0&&b==0) || (a==0&&b==2)) return "YES";
		return "NO";
	}
};


<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
