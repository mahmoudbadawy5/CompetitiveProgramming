/*
Let's make a dp that puts the caracters one by one where dp[a][b][c][las] means we already place a Rs, b Gs and c Ys, last character
was las.
Now how to calculate the number of moves? Let's assume that the original place for the next character we will put is X.
and from one of the other types we placed a characters while upto X we have b characters of it. then the a characters will remain
and we need to make max(a-b,0) swaps to move the unwanted characters forward. We can calculate the cost using accumolative sum
*/

#include <bits/stdc++.h>

using namespace std;

vector<int> pos[3];
int mem[404][404][404][3];
int vis[404][404][404][3];
int sum[404][3];
int n;
string s;

int go(int x,int y,int z,int las)
{
	if(x+y+z==n) return 0;
	int &ret=mem[x][y][z][las];
	if(vis[x][y][z][las]) return ret;
	vis[x][y][z][las]=1;
	ret=(1<<30);
	int cpos=x+y+z;
	if(x<pos[0].size()&&(las!=0||cpos==0))
	{
		int dif=0;
		dif+=max(sum[pos[0][x]][1]-y,0);
		dif+=max(sum[pos[0][x]][2]-z,0);
		ret=min(ret,go(x+1,y,z,0)+dif);
	}
	if(y<pos[1].size()&&(las!=1||cpos==0))
	{
		int dif=0;
		dif+=max(sum[pos[1][y]][0]-x,0);
		dif+=max(sum[pos[1][y]][2]-z,0);
		ret=min(ret,go(x,y+1,z,1)+dif);
	}
	if(z<pos[2].size()&&(las!=2||cpos==0))
	{
		int dif=0;
		dif+=max(sum[pos[2][z]][0]-x,0);
		dif+=max(sum[pos[2][z]][1]-y,0);
		ret=min(ret,go(x,y,z+1,2)+dif);
	}
	return ret;
}

int main()
{
	cin >> n >> s;
	for(int i=0;i<n;i++)
	{
		if(s[i]=='R'){sum[i][0]++; pos[0].push_back(i);}
		else if(s[i]=='G') {sum[i][1]++; pos[1].push_back(i);}
		else {sum[i][2]++; pos[2].push_back(i);}
		if(i) for(int j=0;j<3;j++) sum[i][j]+=sum[i-1][j];
	}
	int ans=go(0,0,0,0);
	if(ans>=(1<<30)) ans=-1;
	cout << ans << endl;
}
