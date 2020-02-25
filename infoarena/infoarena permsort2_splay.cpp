/*
This code gets 70 (the splay tree is a bit slow)

To sort the array let's assume that the current prefix of lenght i is sorted and we want to get the (i+1)th element in its place
we can place this element at the end by reversing the suffix starting at it then reverse the suffix starting at i+1 will bring
it in the (i+1)th position
We keep track of the indices of elements using a splay tree.
*/

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5;

struct node;
extern node* empty;

enum dir{LF,RT};

struct node{
	int val;
	int sz;
	node *par;
	node *ch[2];
	bool isrev;
	node():par(this),val(0),sz(0),ch({this,this}),isrev(0){}
	node(int val,node* lf=empty,node *rt=empty,node *par=empty):par(par),val(val),sz(1+lf->sz+rt->sz),ch({lf,rt}),isrev(0){}
	void update()
	{
		sz=1+ch[0]->sz+ch[1]->sz;
	}
	void reverse()
	{
		if(this==empty) return;
		swap(ch[0],ch[1]);
		isrev^=1;
	}
	void pushd()
	{
		if(isrev)
		{
			ch[0]->reverse();
			ch[1]->reverse();
			isrev=0;
		}
	}
};

node *empty=new node();

inline void link(node* &par,node* &child,dir d)
{
	par->ch[d]=child;
	child->par=par;
}

inline dir getdir(node* &root,node* &ch)
{
	return (root->ch[LF]==ch?LF:RT);
}

void pushdtoroot(node* cur)
{
	if(cur->par!=empty)
		pushdtoroot(cur->par);
	cur->pushd();
}

void rotate(node* &p,dir d)
{
	node* q=p->ch[d],*gp=p->par;
	link(p,q->ch[!d],d);
	link(q,p,(dir)!d);
	if(gp!=empty)
		link(gp,q,getdir(gp,p));
	else
		q->par=empty;
	p->update(); q->update();
}

void splay(node* &root, node* &cur)
{
	pushdtoroot(cur);
	while(cur->par != empty)
	{
		node* p=cur->par;
		dir dd=getdir(p,cur);
		if(p->par==empty)
		{
			rotate(p,dd);
			continue;
		}
		node* gp=p->par;
		dir d=getdir(gp,p);
		if(d==dd)
		{
			rotate(gp,d); rotate(p,d);
		}
		else
		{
			rotate(p,dd); rotate(gp,d);
		}
	}
	root = cur;	
}

node *get_by_index(node* &root,int ind)
{
	root->pushd();
	if(ind == root->ch[LF]->sz)
		return root;
	if(ind < root->ch[LF]->sz)
		return get_by_index(root->ch[LF],ind);
	return get_by_index(root->ch[RT],ind-root->ch[LF]->sz-1);
}


void merge(node *ls,node *gr,node* &ret)
{
	if(ls==empty)
	{
		ret=gr; return;
	}
	node * cur=ls;
	cur->pushd();
	while(cur->ch[RT]!=empty)
	{
		cur=cur->ch[RT];
		cur->pushd();
	}
	splay(ls,cur);
	link(ls,gr,RT);
	ls->update();
	ret=ls;
}

void split(node *root,node* &ls,node* &gr,int lsz)
{
	if(lsz>=root->sz)
	{
		ls=root; gr=empty;
		return;
	}
	node *tmp=get_by_index(root,lsz);
	splay(root,tmp);
	ls=root->ch[LF];
	ls->par=empty;
	gr=root;
	root->ch[LF]=empty;
	root->update();
}

void reverse(node* &root,int s,int e)
{
	node *bef,*bet,*aft;
	split(root,bef,root,s);
	split(root,bet,aft,e-s+1);
	bet->reverse();
	merge(bef,bet,root);
	merge(root,aft,root);
}

int getidx(node* cur)
{
	pushdtoroot(cur);
	int res=cur->ch[LF]->sz;
	while(cur->par != empty)
	{
		if(getdir(cur->par,cur)==RT)
			res+=cur->par->ch[LF]->sz+1;
		cur=cur->par;
	}
	return res;
}

node* arr[N];
int pos[N];

int main()
{
	freopen("permsort2.in","r",stdin); freopen("permsort2.out","w",stdout);
	int n;
	scanf("%d",&n);
	
	node* root=empty;
	for(int i=0;i<n;i++)
	{
		int x;
		scanf("%d",&x);
		arr[i]=new node(x);
		merge(root,arr[i],root);
		pos[x]=i;
	}
	printf("%d\n",2*n);
	for(int i=0;i<n;i++)
	{
		int j=getidx(arr[pos[i+1]]);
		printf("S %d\n",j+1);
		if(j!=n-1) reverse(root,j,n-1);
		printf("S %d\n",i+1);
		if(i!=n-1) reverse(root,i,n-1);
	}

}
