/*
  Same as:  https://github.com/nikolapesic2802/Programming-Practice/blob/master/tetris%203d/main.cpp
*/

#include <bits/stdc++.h>

using namespace std;

const int N=1001,M=2048;

int n,x,y;

struct segtree{
	vector<int> btree,lazy;
	segtree()
	{
		btree=vector<int>(M);
		lazy=vector<int>(M);
	}
	void prob(int node,int l,int r)
	{
		btree[node]=max(btree[node],lazy[node]);
		if(l!=r)
		{
			lazy[node<<1]=max(lazy[node],lazy[node<<1]);
			lazy[(node<<1)|1]=max(lazy[node],lazy[(node<<1)|1]);
		}
		lazy[node]=0;
	}
	void update(int node,int l,int r,int ql,int qr,int val)
	{
		if(lazy[node]) prob(node,l,r);
		if(r<ql||qr<l) return;
		if(ql<=l&&r<=qr)
		{
			lazy[node]=val;
			prob(node,l,r);
			return;
		}
		int mid=(l+r)>>1;
		update(node<<1,l,mid,ql,qr,val);
		update((node<<1)|1,mid+1,r,ql,qr,val);
		btree[node]=max(btree[node<<1],btree[(node<<1)|1]);
	}
	int query(int node,int l,int r,int ql,int qr)
	{
		//cout << node << " " << l << " " << r << " " << ql << " " << qr << " " << btree[node] << " " << lazy[node] << endl;
		if(lazy[node]) prob(node,l,r);
		if(r<ql||qr<l) return 0;
		if(ql<=l&&r<=qr) return btree[node];
		int mid=(l+r)>>1;
		return max(query(node<<1,l,mid,ql,qr),query((node<<1)|1,mid+1,r,ql,qr));
	}
};

struct segtree2d{
	vector<segtree> full,part;
	segtree2d()
	{
		full=vector<segtree>(M);
		part=vector<segtree>(M);
	}
	void update(int node,int l,int r,int qlx,int qrx,int qly,int qry,int val)
	{
		if(r<qlx||qrx<l) return;
		if(qlx<=l&&r<=qrx)
		{
			full[node].update(1,0,N-1,qly,qry,val);
			part[node].update(1,0,N-1,qly,qry,val);
			return;
		}
		int mid=(l+r)>>1;
		update(node<<1,l,mid,qlx,qrx,qly,qry,val);
		update((node<<1)|1,mid+1,r,qlx,qrx,qly,qry,val);
		full[node].update(1,0,N-1,qly,qry,val);
	}
	int query(int node,int l,int r,int qlx,int qrx,int qly,int qry)
	{
		if(r<qlx||qrx<l) return 0;
		if(qlx<=l&&r<=qrx) {/*cout << "FULL: "<< node <<" " << l << " " << r << " " << qlx << " " << qrx << endl;*/ return full[node].query(1,0,N-1,qly,qry);}
		int mid=(l+r)>>1;
		int f=max(query(node<<1,l,mid,qlx,qrx,qly,qry),query((node<<1)|1,mid+1,r,qlx,qrx,qly,qry));
		//cout << "PART: " << node <<" " << l << " " << r << " " << qlx << " " << qrx << endl;
		return max(f,part[node].query(1,0,N-1,qly,qry));
	}
} btree;

int main()
{
	scanf("%d %d %d",&x,&y,&n);
	while(n--)
	{
		int a,b,l,c,d;
		scanf("%d %d %d %d %d",&a,&b,&l,&c,&d);
		a--; b--;
		int cur=btree.query(1,0,N-1,c,c+a,d,d+b);
		//cout << cur << " " <<  cur+l << endl;
		btree.update(1,0,N-1,c,c+a,d,d+b,cur+l);
	}
	printf("%d\n",btree.query(1,0,N-1,0,N-1,0,N-1));
}
