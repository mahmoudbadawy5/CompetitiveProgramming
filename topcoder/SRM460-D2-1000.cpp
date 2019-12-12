/*
Backtracking with some optimizations
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
#include <bits/stdc++.h>

using namespace std;

vector< pair<int,int> > ed;
pair<int,int> cur[9];
int got[39];
int n;
int uni[10];
int ans;

int uni_find(int x)
{
	return (uni[x]==x?x:uni_find(uni[x]));
}

int check()
{
	for(int i=0;i<n-1;i++)
	{
		int a=uni_find(cur[i].first),b=uni_find(cur[i].second);
		if(a==b) return 0;
		uni[a]=b;
	}
	return 1;
}

void go(int ind,int res)
{
	if(res<0) return;
	if(res==0)
	{
		iota(uni,uni+n,0);
		ans+=check();
		return;
	}
	if(ind>=ed.size()) return;
	if(got[ind]==2) return go(ind+1,res);
	cur[res-1]=ed[ind];
	go(ind+1,res-1);
	got[ind]=0;
	go(ind+1,res);
}

class TheCitiesAndRoadsDivTwo {
public:
	int find(vector <string> m) {
		n=m.size();
		ed.clear();
		int curc=0;
		for(int i=0;i<n;i++)
		{
			for(int j=i+1;j<n;j++)
			{
				ed.push_back({i,j});
				if(m[i][j]=='Y') {cur[n-curc-2]={i,j}; curc++; got[ed.size()-1]=2;}
				else got[ed.size()-1]=0;
			}
		}
		ans=0;
		go(0,n-1-curc);
		return ans;
	}
};


<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
