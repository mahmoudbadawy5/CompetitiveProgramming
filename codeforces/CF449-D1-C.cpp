/*
  Same as editrial: https://codeforces.com/blog/entry/13112
*/

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5;
int isp[N],vis[N];

int main()
{
	int n;
	scanf("%d",&n);
	vector<pair<int,int> > ans;
	for(int i=3;i<=n/2;i++)
	{
		if(isp[i]==0)
		{
			vector<int> v;
			for(int j=i;j<=n;j+=i)
			{
				isp[j]=1;
				if(!vis[j])
					v.push_back(j);
				vis[j]=1;
			}
			int st=0;
			if(v.size()%2)
			{
				swap(v[0],v[1]);
				st=1;
				vis[2*i]=0;
			}
			for(int j=st;j+1<v.size();j+=2)
				ans.push_back({v[j],v[j+1]});
		}
	}
	vector<int> v;
	for(int i=2;i<=n;i+=2)
		if(!vis[i]) v.push_back(i);
	for(int i=0;i+1<v.size();i+=2)
		ans.push_back({v[i],v[i+1]});
	printf("%d\n",(int)ans.size());
	for(auto i:ans)
		printf("%d %d\n",i.first,i.second);
}
