/*
  -Same as: https://github.com/stefdasca/CompetitiveProgramming/blob/master/IZhO/IZhO%2019-segments.cpp
*/

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int N=5e5+5;

int arr[N];
set<pair<int,int> > cur[N];
long long sum[N];
int n;

int get(long long s,int i)
{
	int st=i,en=n,ans=n+1;
	while(st<=en)
	{
		int mid=(st+en)/2;
		if(sum[mid]-sum[i]>=s)
		{
			ans=mid;
			en=mid-1;
		}
		else
			st=mid+1;
	}
	return ans;
}

int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
		sum[i+1]=sum[i]+arr[i];
	}
	for(int i=1;i<n;i++)
	{
		int las=-1;
		cur[i].insert({1,1});
		while(cur[i].size())
		{
			auto x=*cur[i].rbegin();
			cur[i].erase(x);
			if(x.F==las)
				continue;
			cur[i+1].insert(x);
			int z=get(sum[i]-sum[x.S-1],i);
			cur[z].insert({x.F+1,i+1});
			if(las!=-1) break;
			las=x.F;
		}
	}
	if(!cur[n].size()) cur[n].insert({1,1});
	cout << (*cur[n].rbegin()).F << endl;
}
