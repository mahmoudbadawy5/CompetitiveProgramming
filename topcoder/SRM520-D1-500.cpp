/*
We can do dp[index][points] = number of ways such than participiant index gets exactly numbe of points
then dp[index][points] = sum (dp[index+1][p < points]) * number of ways to get points in problems
number of ways to get points in problems can be calculated using another dp

dp1[mask of solvable problems][index of problem][current score]
to calculate both dp faster we can use cummulative sum
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

const int MOD=1e9+7,MX=2e5+5;

int dp1[(1<<3)][4][MX];
int dp[22][MX];
int sc[3];

void calc(int mas)
{
	dp1[mas][3][0]=1;
	for(int i=1;i<MX;i++)
		dp1[mas][3][i]=1;
	for(int i=2;i>=0;i--)
	{
		for(int j=0;j<MX;j++)
		{
			//cout << i << " " << j << endl;
			// [j-sc[i],j-1]
			int l,r;
			if(mas&(1<<i))
				l=max(0,j-sc[i]),r=j-1;
			else
				l=j,r=j;
			if(r==-1)
				continue;
			dp1[mas][i][j]=(dp1[mas][i+1][r]-(l?dp1[mas][i+1][l-1]:0)+MOD)%MOD;
		}
		if(i)
			for(int j=1;j<MX;j++)
				dp1[mas][i][j]=(dp1[mas][i][j]+dp1[mas][i][j-1])%MOD;
	}
}


class SRMIntermissionPhase {
public:
	int countWays(vector <int> points, vector <string> desc) {
		for(int i=0;i<3;i++) sc[i]=points[i];
		for(int i=0;i<(1<<3);i++)
			calc(i);
		int n=desc.size();
		for(int i=0;i<MX;i++) dp[n][i]=1;
		//cout << dp1[1][1][0] << " " << dp1[1][1][1] << " " << dp1[1][1][2] << endl;
		for(int i=n-1;i>=0;i--)
		{
			int curm=0;
			for(int j=0;j<3;j++)
				if(desc[i][j]=='Y')
					curm|=(1<<j);
			for(int j=0;j<MX;j++)
			{
				dp[i][j]=(1LL*dp1[curm][0][j]*(j==0?(i==n-1):dp[i+1][j-1]))%MOD;
			}
			/*for(int j=0;j<10;j++)
				cout << dp[i][j] << " ";
			cout << endl;*/
			for(int j=1;j<MX;j++) dp[i][j]=(dp[i][j]+dp[i][j-1])%MOD;
		}
		return dp[0][MX-1];
	}
};


<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
