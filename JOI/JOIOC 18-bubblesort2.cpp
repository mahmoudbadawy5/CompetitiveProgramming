/*
You need to notice that in each pass every element that needs to be moved to left is moved only one time to left. That means the
number of passes is max(curPos[i]-actualPos[i]) for each i. To keep this fast we can use splay tree with lazy propagation.
*/

#include "bubblesort2.h"
#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;
     
struct node;
extern node* emptyNode;
 
enum dir{LF,RT};
 
struct node{
	int val,mx,lazy;
	pair<int,int> cur;
	int sz;
	node *par;
	node *ch[2];
	node():par(this),val(0),sz(0),ch({this,this}),mx(-(1<<30)),lazy(0){}
	node(int val,pair<int,int> cur,node* lf=emptyNode,node *rt=emptyNode,node *par=emptyNode):par(par),cur(cur),val(val),sz(1+lf->sz+rt->sz),ch({lf,rt}),mx(val),lazy(0){}
	void update()
	{
		pushd();
		sz=1+ch[0]->sz+ch[1]->sz;
		mx=max(ch[LF]->mx,max(val,ch[RT]->mx));
	}
	void addtolazy(int val)
	{
		if(this == emptyNode) return;
		lazy+=val;
		mx+=val;
		this->val+=val;
	}
	void pushd()
	{
		if(lazy)
		{
			ch[LF]->addtolazy(lazy);
			ch[RT]->addtolazy(lazy);
			lazy=0;
		}
	}
};
 
node *emptyNode=new node();
 
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
	if(cur->par!=emptyNode)
		pushdtoroot(cur->par);
	cur->pushd();
}
 
void rotate(node* &p,dir d)
{
	node* q=p->ch[d],*gp=p->par;
	link(p,q->ch[!d],d);
	link(q,p,(dir)!d);
	if(gp!=emptyNode)
		link(gp,q,getdir(gp,p));
	else
		q->par=emptyNode;
	p->update(); q->update();
}
 
void splay(node* &root, node* &cur)
{
	pushdtoroot(cur);
	while(cur->par != emptyNode)
	{
		node* p=cur->par;
		dir dd=getdir(p,cur);
		if(p->par==emptyNode)
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
 
node *get_by_index(node* &root,pair<int,int> ind)
{
	if(root==emptyNode) return emptyNode;
	root->pushd();
	if(ind == root->cur)
		return root;
	if(ind < root->cur)
		return get_by_index(root->ch[LF],ind);
	node* x=get_by_index(root->ch[RT],ind);
	if(x==emptyNode)
		return root;
	else
		return x;
}
 
void print(node* &root,int dep=0)
{
	if(root==emptyNode) return;
	//cout << string(dep,'\t') << (root->val) << endl << "L";
	root->pushd();
	print(root->ch[LF],dep+1);
	//cout << "R";
	cout << string(dep,'\t') << (root->val) << "," << (root->cur.first) << endl;
	print(root->ch[RT],dep+1); 
}
 
void merge(node *ls,node *gr,node* &ret)
{
	if(ls==emptyNode)
	{
		ret=gr; return;
	}
	node * cur=ls;
	cur->pushd();
	while(cur->ch[RT]!=emptyNode)
	{
		cur=cur->ch[RT];
		cur->pushd();
	}
	splay(ls,cur);
	link(ls,gr,RT);
	ls->update();
	ret=ls;
}
 
void split(node *root,node* &ls,node* &gr,pair<int,int> lsz)
{
	node *tmp=get_by_index(root,lsz);
	//cout << lsz.first << " "  << lsz.second  <<" " << (tmp->cur.first) << endl;
	if(tmp==emptyNode)
	{
		ls=emptyNode; gr=root;
		return;
	}
	splay(root,tmp);
	gr=root->ch[RT];
	gr->par=emptyNode;
	ls=root;
	root->ch[RT]=emptyNode;
	root->update();
	/*ls=root->ch[LF];
	ls->par=emptyNode;
	gr=root;
	root->ch[LF]=emptyNode;
	root->update();*/
}


const int N=1e5+5;

node* root;
int n,q;

void modify(int ox,int nx,int i)
{
	node *a,*b,*c,*d;
	split(root,a,d,{ox,i});
	split(a,a,b,{ox,i-1});
	//print(a); cout << "----------" << endl; print(b); cout << "----------" << endl; print(d); cout << "-------" << endl;
	if(ox<nx)
	{

		split(d,c,d,{nx,i});
		//cout << "A" << endl; print(a); cout << "B" << endl; print(b); cout << "C" << endl; print(c); cout << "D" << endl; print(d);
		//print(c);
		c->addtolazy(1);
		b->addtolazy(-(c->sz));
		b->cur={nx,i};
		//cout << (c->mx) <<" " << (b->mx) << "MX\n";
		merge(a,c,root);
		merge(root,b,root);
		merge(root,d,root);
	}
	else
	{
		split(a,a,c,{nx,i});
		//cout << "AA" << endl; print(a); cout << "B" << endl; print(b); cout << "C" << endl; print(c); cout << "D" << endl; print(d);
		c->addtolazy(-1);
		b->addtolazy((c->sz));
		b->cur={nx,i};
		merge(a,b,root);
		merge(root,c,root);
		merge(root,d,root);
	}
}


std::vector<int> countScans(std::vector<int> A,std::vector<int> X,std::vector<int> V){
	n=A.size(),q=X.size();	
	vector<pair<int,int> > v;
	for(int i=0;i<A.size();i++)
		v.push_back({A[i],2*i});
	sort(v.begin(),v.end());
	root=emptyNode;
	for(int i=0;i<n;i++)
	{
	    node* cur=new node(v[i].second/2-i,v[i]);
		merge(root,cur,root);
	}
	//cout << (root->mx) << endl;
	vector<int> ans;
	for(int i=0;i<q;i++)
	{
	    if(A[X[i]]!=V[i])
		    modify(A[X[i]],V[i],2*X[i]);
		A[X[i]]=V[i];
		ans.push_back(root->mx);
	}
	return ans;
}
