/*
  Same as editorial: https://codeforces.com/blog/entry/55701
*/

#include <bits/stdc++.h>

using namespace std;

const int N=2e5+5;

struct node{
	int co,ind;
	int ch[2];
};

node trie[30*N];
int arr[N],uni[N];
vector<int> v[N];
set<pair<int,int> > ss;
unordered_map<int,set<int> > mp;
int n,nodes;

int getb(int x,int i)
{
	return (x&(1<<i))!=0;
}

void add(int node,int ind,int v,int a,int i)
{
	trie[node].co+=a;
	trie[node].ind=i;
	if(ind<0) return;
	if(!trie[node].ch[getb(v,ind)])
	{
		trie[node].ch[getb(v,ind)]=++nodes;
	}
	add(trie[node].ch[getb(v,ind)],ind-1,v,a,i);
}

pair<int,int> get(int x)
{
	int cur=1,ans=0;
	for(int i=29;i>=0;i--)
	{
		int ds=getb(x,i),nx=trie[cur].ch[ds];
		if(trie[nx].co)
		{
			cur=nx;
		}
		else
		{
			cur=trie[cur].ch[ds^1];
			ans+=(1<<i);
		}
	}
	int ind=trie[cur].ind;
	return {ans,ind};
}

int uni_find(int x)
{
	return uni[x]=(uni[x]==x?x:uni_find(uni[x]));
}

void unio(int x,int y)
{
	x=uni_find(x); y=uni_find(y);
	assert(x!=y);
	if(v[x].size()>v[y].size()) swap(x,y);
	ss.erase({v[x].size(),x}); ss.erase({v[y].size(),y});
	for(int i:v[x])
		v[y].push_back(i);
	ss.insert({v[y].size(),y});
	uni[x]=y;
}

int main()
{
	nodes=1;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
		if(mp[arr[i]].size()) continue;
		add(1,29,arr[i],1,i);
		v[i].push_back(i); uni[i]=i;
		ss.insert({1,i});
		mp[arr[i]].insert(i);
	}
	long long ans=0;
	while(ss.size()>1)
	{
		int x=(*ss.begin()).second;
		int mnx=(1<<30),ind=-1;
		for(int i:v[x])
			add(1,29,arr[i],-1,i);
		for(int i:v[x])
		{
			auto res=get(arr[i]);
			if(res.first<mnx)
			{
				mnx=res.first;
				ind=res.second;
			}
		}
		ans+=mnx;
		for(int i:v[x])
			add(1,29,arr[i],1,i);
		
		unio(v[x][0],ind);
	}
	printf("%lld\n",ans);
}
