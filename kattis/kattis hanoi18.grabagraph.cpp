/*
For the second graph we start with a chain (each edge is connected with the previous one) of all nodes except 2 then add an edge between each node and the previous
to its previous. Now each node i can be reached in fib(i) ways (if we didn't consider only sortest paths we will deal wit that later).
Accrding to https://en.wikipedia.org/wiki/Zeckendorf%27s_theorem we can represent all numbers as sum of fibonacci numbers so node 2 can be connected to the correspnding
fibonacci numbers needed. We need about 2n+(number of fibonacci needed) edges which is enough to pass.

For the secon graph we can apply the same but making each fibonacci sum the last 3 numbers before it (not sure why is this correct). this will need fewer nodes but
more edges which is enough to pass.

To deal with not all paths are minimum paths we can weigh the edge between node (x,y) to be |x - y| so that all paths from (1,2) will be of length (n-1)
*/

#include <bits/stdc++.h>

using namespace std;

const int N=90,A=72,B=88;

vector<int> adj[2][N];
long long ans[2][N];
int n;

void gen(int n,int c,int t)
{
	ans[t][1]=1;
	for(int i=2;i<n;i++)
	{
		for(int j=1;j<=c;j++)
		{
			if(i-j<=0) break;
			ans[t][i]+=ans[t][i-j];
			adj[t][i].push_back(i-j);
		}
		//cout << t << " " << i << " " << ans[t][i] << endl;
	}
}

int main()
{
	gen(A,3,0);
	gen(B,2,1);
	long long a;
	while(1)
	{
		cin >> a;
		if(a==-1) break;
		adj[0][A].clear();
		adj[1][B].clear();
		long long aa=a;
		for(int i=A-1;i>=1;i--)
		{
			if(aa>=ans[0][i])
			{
				aa-=ans[0][i];
				adj[0][A].push_back(i);
			}
		}
		assert(aa==0);
		aa=a;
		for(int i=B-1;i>=1;i--)
		{
			if(aa>=ans[1][i])
			{
				aa-=ans[1][i];
				adj[1][B].push_back(i);
			}
		}
		int suma=0,sumb=0;
		for(int i=1;i<=A;i++)
			suma+=adj[0][i].size();
		for(int i=1;i<=B;i++)
			sumb+=adj[1][i].size();
		assert(aa==0);
		puts("YES");
		printf("%d %d\n",A,suma);
		assert(suma<=2525);
		for(int i=1;i<=A;i++)
		{
			int x=(i==A?2:i==2?A:i);
			for(int j:adj[0][i])
			{
				int y=(j==A?2:j==2?A:j);
				printf("%d %d %d\n",x,y,i-j);
			}
		}
		puts("YES");
		printf("%d %d\n",B,sumb);
		assert(sumb<=214);
		for(int i=1;i<=B;i++)
		{
			int x=(i==B?2:i==2?B:i);
			for(int j:adj[1][i])
			{
				int y=(j==B?2:j==2?B:j);
				printf("%d %d %d\n",x,y,i-j);
			}
		}
	}
}
