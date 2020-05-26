/*
 - https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Balkan/official/2018/elections_solution.pdf
 */
 
 #include <bits/stdc++.h>

using namespace std;

const int N=5e5+5;

int btree[4*N],lazy[4*N];
string s;
int n,q;
vector<pair<int,int> > qs[N];
int ans[N];

void prob(int node,int l,int r)
{
	btree[node]+=lazy[node];
	if(l!=r)
	{
		lazy[node<<1]+=lazy[node];
		lazy[(node<<1)|1]+=lazy[node];
	}
	lazy[node]=0;
}

void update(int node,int l,int r,int ql,int qr,int v)
{
	if(lazy[node]) prob(node,l,r);
	if(r<ql||qr<l) return;
	if(ql<=l&&r<=qr)
	{
		lazy[node]+=v;
		prob(node,l,r);
		return;
	}
	int mid=(l+r)>>1;
	update(node<<1,l,mid,ql,qr,v);
	update((node<<1)|1,mid+1,r,ql,qr,v);
	btree[node]=max(btree[node<<1],btree[(node<<1)|1]);
}

int query(int node,int l,int r,int ql,int qr)
{
	if(lazy[node]) prob(node,l,r);
	if(r<ql||qr<l) return -(1<<30);
	if(ql<=l&&r<=qr) return btree[node];
	int mid=(l+r)>>1;
	return max(query(node<<1,l,mid,ql,qr),query((node<<1)|1,mid+1,r,ql,qr));
}

int main()
{
	cin >> n >> s >> q;
	for(int i=0;i<q;i++)
	{
		int l,r;
		cin >> l >> r;
		l--; r--;
		qs[r].push_back({l,i});
	}
	vector<int> qp;
	for(int i=0;i<n;i++)
	{
		if(s[i]=='T')
		{
			qp.push_back(i);
		}
		else
		{
			if(qp.size())
			{
				update(1,0,n-1,qp.back(),n,1);
				qp.pop_back();
			}
			update(1,0,n-1,i,n,-1);
		}
		for(auto j:qs[i])
		{
			int l=j.first;
			int x=lower_bound(qp.begin(),qp.end(),l)-qp.begin();
			ans[j.second]=(qp.size()-x)+max(query(1,0,n-1,l,i)-(l?query(1,0,n-1,l-1,l-1):0),0);
		}
	}
	for(int i=0;i<q;i++)
		printf("%d\n",ans[i]);
}
