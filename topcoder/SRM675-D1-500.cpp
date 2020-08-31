/*
Consider answering one query we can do it using binary search. If we searched for the x-th number (1-based) we need to find the smallest number with at least x
numbers smaller than or equal to it. This gives O(n*q*logn)
To reduce the q factor we can do parallel binary search by answering all binary searches with one sweep over the array
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

vector<int> get(int n,int x0,int a,int b,vector<pair<int,int> > q)
{
	sort(q.begin(),q.end());
	vector<int> ans(q.size()),cur(q.size()+1);
	for(int i=0;i<n;i++)
	{
		int x=lower_bound(q.begin(),q.end(),make_pair(x0,-1))-q.begin();
		cur[x]++;
		int mod=1e9+7;
		x0=(1LL*x0*a+b)%mod;
	}
	for(int i=1;i<q.size();i++) cur[i]+=cur[i-1];
	for(int i=0;i<q.size();i++)
	{
		ans[i]=cur[i];
	}
	return ans;
} 

class LimitedMemorySeries1 {
public:
	long long getSum(int n, int x0, int a, int b, vector <int> query) {
		vector<pair<int,int> > bs;
		for(int i=0;i<query.size();i++)
		{
			query[i]++;
			bs.push_back({0,(int)1e9+7});
		}
		vector<int> ans(bs.size(),(1<<30));
		while(true)
		{
			int ok=0;
			vector<pair<int,int> > v;
			int cnt=0;
			for(int i=0;i<bs.size();i++)
			{
				if(bs[i].first<=bs[i].second)
				{
					v.push_back({(bs[i].first+bs[i].second)/2,i});
					ok=1;
				}
			}
			if(!ok) break;
			auto res=get(n,x0,a,b,v,query.size());
			sort(v.begin(),v.end());
			for(int i=0;i<res.size();i++)
			{
				if(res[i]>=query[v[i].second])
				{
					//cout << res[i] << " " << v[i].first << " " << v[i].second << "  " << bs[v[i].second].first << " " << bs[v[i].second].second << endl;
					ans[v[i].second]=v[i].first;
					bs[v[i].second].second=v[i].first-1;
				}
				else
					bs[v[i].second].first=v[i].first+1;
			}
		}
		long long res=0;
		for(auto i:ans) res+=i;
		return res;
	}
};


<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
