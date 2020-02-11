/*
same as : https://github.com/tmwilliamlin168/CompetitiveProgramming/blob/master/IOI/04-Empodia.cpp
*/
#include <bits/stdc++.h>

using namespace std;

const int N=2e6+6;
int arr[N];
int l[N],r[N],del[N];
int n;
vector<int> grp[N*2];

int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	stack<int> ss;
	for(int i=0;i<n;i++)
	{
		while(ss.size()&&arr[ss.top()]<arr[i]) ss.pop();
		if(ss.size()) l[i]=ss.top();
		else l[i]=-1;
		ss.push(i);
	}
	while(ss.size()) ss.pop();
	for(int i=n-1;i>=0;i--)
	{
		while(ss.size()&&arr[ss.top()]>arr[i]) ss.pop();
		if(ss.size()) r[i]=ss.top();
		else r[i]=n;
		ss.push(i);
	}
	for(int i=0;i<n;i++)
	{
		grp[arr[i]-i+n].push_back(i);
	}
	vector< pair<int,int> > res;
	for(int i=0;i<=2*n;i++)
	{
		if(!grp[i].size()) continue;
		while(ss.size()) ss.pop();
		for(int j=grp[i].size()-1;j>=0;j--)
		{
			int x=grp[i][j];
			while(ss.size()&&l[ss.top()]>x) ss.pop();
			if(ss.size())
			{
				int y=ss.top();
				if(r[x]>=y)
					res.push_back({x,y});
			}
			while(ss.size()&&l[ss.top()]>l[x])
				ss.pop();
			ss.push(x);
		}
	}
	sort(res.begin(),res.end());
	vector< pair<int,int> > ev;
	for(int i=0;i<res.size();i++)
	{
		ev.push_back({res[i].first,(i+1)});
		ev.push_back({res[i].second,-(i+1)});
	}
	sort(ev.begin(),ev.end());
	set<int> cur; int deld=0;
	for(int i=0;i<ev.size();i++)
	{
		if(ev[i].second<0)
		{
			cur.erase(-ev[i].second);
			continue;
		}
		for(int j:cur)
		{
			del[j]=1;
			deld++;
		}
		cur.clear();
		cur.insert(ev[i].second);
	}
	printf("%d\n",(int)res.size()-deld);
	for(int i=0;i<res.size();i++)
		if(!del[i+1])
			printf("%d %d\n",res[i].first+1,res[i].second+1);
}
