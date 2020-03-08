/*
Same as: https://github.com/stefdasca/CompetitiveProgramming/blob/master/IZhO/IZhO%2019-xoractive.cpp
*/

#include "interactive.h"
#include <bits/stdc++.h>
using namespace std;

map<int,int> pos;

vector<int> guess(int n) {
	vector<int> ans=vector<int>(n);
	ans[0]=ask(1);
	for(int i=0;i<=6;i++)
	{
		vector<int> v;
		for(int j=2;j<=n;j++)
		{
			if(j&(1<<i))
				v.push_back(j);
		}
		if(!v.size()) continue;
		vector<int> r1=get_pairwise_xor(v);
		v.push_back(1);
		vector<int> r2=get_pairwise_xor(v);
		map<int,int> mp;
		for(int x:r2)
			if(x) mp[x]++;
		for(int x:r1)
			if(x) mp[x]--;
		for(auto x:mp)
		{
			if(x.second==0) continue;
			pos[x.first^ans[0]]|=(1<<i);
		}
	}
	for(auto i:pos)
		ans[i.second-1]=i.first;
	return ans;
}
