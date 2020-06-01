/*
  Same as: https://github.com/dolphingarlic/CompetitiveProgramming/blob/master/APIO/APIO%2015-bridge.cpp
*/

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

struct median{
	multiset<int> l,r;
	long long lsum,rsum;
	int med;
	// l < med
	// r med  , > med
	median():lsum(0),rsum(0){}
	void fix()
	{
		// odd: l.size() = r.size()-1 , even: l.size() = r.size() (taking larger as median)
		if(l.size()>r.size())
		{
			med=(*l.rbegin());
			lsum-=med; rsum+=med;
			l.erase(l.find(*l.rbegin()));
			r.insert(med);
		}
		if(r.size() > l.size()+1)
		{
			l.insert(*r.begin());
			lsum+=*r.begin(); rsum-=*r.begin();
			r.erase(r.begin());
			med=*r.begin();
		}
	}
	void insert(int x)
	{
		med=r.size()?(*r.begin()):-1;
		if(x<med)
		{
			lsum+=x;
			l.insert(x);
		}
		else
		{
			rsum+=x;
			r.insert(x);
		}
		fix();
	}
	void erase(int x)
	{
		med=r.size()?(*r.begin()):-1;
		if(x<med)
		{
			lsum-=x;
			l.erase(l.find(x));
		}
		else
		{
			rsum-=x;
			r.erase(r.find(x));
		}
		fix();
	}
};

vector< pair<int,int> > v;
int n,k;

bool cmp(pair<int,int> a,pair<int,int> b)
{
	return a.F+a.S < b.F+b.S;
}

int main()
{
	scanf("%d %d",&k,&n);
	long long init=0,ans=(1LL<<60);
	for(int i=0;i<n;i++)
	{
		char s,t;
		int x,y;
		scanf(" %c %d %c %d",&s,&x,&t,&y);
		if(s==t) init+=abs(x-y);
		else v.push_back({x,y});
	}
	n=v.size();
	sort(v.begin(),v.end(),cmp);
	init+=n;
	median l,r;
	for(int i=0;i<n;i++)
	{
		r.insert(v[i].F);
		r.insert(v[i].S);
	}
	ans=r.rsum-r.lsum;
	if(k==2)
	{
		for(int i=0;i<n;i++)
		{
			r.erase(v[i].F); l.insert(v[i].F);
			r.erase(v[i].S); l.insert(v[i].S);
			ans=min(ans,(r.rsum-r.lsum)+(l.rsum-l.lsum));
		}
	}
	cout << ans+init << endl;
}
