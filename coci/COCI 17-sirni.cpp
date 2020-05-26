/*
  Same as: https://github.com/dolphingarlic/CompetitiveProgramming/blob/master/COI/COCI%2017-sirni.cpp
*/

#include <bits/stdc++.h>
 
using namespace std;
 
const int N=1e5+5,M=1e7+7;
 
int n;
int arr[N];
vector< pair<int,int> > ed[M];
int uni[N];
 
int uni_find(int x)
{
	return uni[x]=(uni[x]==x?x:uni_find(uni[x]));
}
 
int unio(int x,int y)
{
	x=uni_find(x); y=uni_find(y);
	if(x==y) return 0;
	uni[x]=y;
	return 1;
}
 
int main()
{
	scanf("%d",&n);
	set<int> ss;
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
		ss.insert(arr[i]);
	}
	n=0;
	for(int i:ss) arr[n++]=i;
	for(int i=0;i<n;i++)
	{
		int s=i+1;
		for(int j=arr[i];j<M;j+=arr[i])
		{
			while(s<n && arr[s]<j) s++;
			if(s<n) ed[arr[s]%j].emplace_back(i,s);
		}
	}
	iota(uni,uni+n,0);
	long long ans=0;
	for(int i=0;i<M;i++)
	{
		for(auto j:ed[i])
		{
			if(unio(j.first,j.second)) ans+=i;
		}
	}
	cout << ans << endl;
}
