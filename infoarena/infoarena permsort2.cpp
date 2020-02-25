/*
Same as: https://github.com/stefdasca/CompetitiveProgramming/blob/master/Infoarena/permsort2.cpp

Another idea that's slow: https://github.com/mahmoudbadawy5/CompetitiveProgramming/blob/master/infoarena/infoarena%20permsort2_splay.cpp
*/

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int btree[N],pos[N];
int n;

void update(int ind)
{
	for(;ind<=n;ind+=ind&(-ind))
		btree[ind]++;
}

int query(int ind)
{
	int ans=0;
	for(;ind>0;ind-=ind&(-ind))
		ans+=btree[ind];
	return ans;
}

int main()
{
	freopen("permsort2.in","r",stdin); freopen("permsort2.out","w",stdout);
	scanf("%d",&n);
	
	for(int i=0;i<n;i++)
	{
		int x;
		scanf("%d",&x);
		pos[x]=i+1;
	}
	vector<int> ans;
	for(int i=n;i>0;i--)
	{
		int p=pos[i]+query(n)-query(pos[i]-1);
		if(p-1)
		{
			if(p-1>1) ans.push_back(p-1);
			ans.push_back(p);
		}
		update(pos[i]);
	}
	printf("%d\n",(int)ans.size());
	for(int i:ans)
		printf("P %d\n",i);
}
