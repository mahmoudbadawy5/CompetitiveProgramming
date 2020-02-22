/*
Same as: https://github.com/luciocf/Problems/blob/master/POI/POI%202016/streets.cpp
*/

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int N=5e5+5,M=1e6+6;

int disc[N],low[N],lowd[N];
int stk[N],stksz;
int cid[N],idc, dfstime;

int head[N],nxt[M],to[M];

int n,m,ne;

void clear () {
	ne = 0;
	memset(head,-1,sizeof(head));
}

void addedge (int f, int t) {
	nxt[ne] = head[f];
	to[ne] = t;
	head[f] = ne++;
}

void tarjandfs (int i) {

	disc[i] = low[i] = dfstime++;
	stk[stksz++] = i;

	for (int k=head[i]; ~k; k=nxt[k]) {
		int j = to[k];

		if (disc[j] == -1) {
			tarjandfs(j);
			low[i] = min(low[i],low[j]);
		} else if (cid[j] == -1) 
		{
			low[i] = min(low[i],disc[j]);
		}
	}
	if (low[i] == disc[i]) {

		do {
			cid[ stk[--stksz] ] = idc;
		} while (stk[stksz] != i);

		idc++;
	}
}

void scc () {
	memset(disc,-1,sizeof(disc));
	memset(cid,-1,sizeof(cid));
	idc = 0; dfstime = 0;
	for (int i=1; i<=n; i++) if (disc[i] == -1) tarjandfs(i);

}

vector<int> adj[N],radj[N];
vector<int> sor,ans;
int tmd;
int vis[N],dtm[N],mn[N],mx[N],okid[N];

void dfs(int x)
{
	if(vis[x]) return;
	vis[x]=1;
	for(int i:adj[x])
		dfs(i);
	sor.push_back(x);
	dtm[x]=tmd--;
}

int main()
{
	clear();
	scanf("%d %d",&n,&m);
	for(int i=0;i<m;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		addedge(x,y);
	}
	//cout << endl;
	scc();
	ne=0;
	for(int i=1;i<=n;i++)
	{
		//cout << cid[i] << " ";
		for(int k=head[i];~k;k=nxt[k])
		{
			if(cid[i]!=cid[to[k]])
			{
				adj[cid[i]].push_back(cid[to[k]]);
				radj[cid[to[k]]].push_back(cid[i]);
			}
		}
	}
	//cout << endl;
	tmd=idc;
	for(int i=0;i<idc;i++)
		if(!vis[i])
			dfs(i);
	reverse(sor.begin(),sor.end());
	for(int i=0;i<sor.size();i++)
	{
		mn[sor[i]]=(1<<30);
		//cout << sor[i] << " " << dtm[sor[i]] << " : ";
		for(int j:adj[sor[i]])
		{
			//cout << j << " ";
			mn[sor[i]]=min(mn[sor[i]],dtm[j]);
		}
		//cout << endl;
		for(int j:radj[sor[i]])
			mx[sor[i]]=max(mx[sor[i]],dtm[j]);
		okid[sor[i]]=1;
		//cout << mn[sor[i]] << " " << mx[sor[i]] << endl;
	}
	int mxx=0,mnn=(1<<30);
	
	for(int i=0;i<sor.size();i++)
	{
		if(mxx>dtm[sor[i]])
		{
			okid[sor[i]]=0;
		}
		mxx=max(mxx,mn[sor[i]]);
	}
	for(int i=sor.size()-1;i>=0;i--)
	{
		if(mnn<dtm[sor[i]])
		{
			okid[sor[i]]=0;
		}
		mnn=min(mnn,mx[sor[i]]);
	}
	for(int i=1;i<=n;i++)
	{
		//cout << cid[i] << " " << isartic[cid[i]] << endl;
		if(okid[cid[i]])
			ans.push_back(i);
	}
	cout << ans.size() << endl;
	for(int i:ans)
		cout << i << " ";
	cout << endl;
}
