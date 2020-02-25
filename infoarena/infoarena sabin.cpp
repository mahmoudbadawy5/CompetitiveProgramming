/*
Let's keep a trie where the state of the node (moving from the parent) isn't just a character but a vector of k characters that
represents the next k characters on the shelf. now to answer the queries we can go to depth = X using states of the k indieces.
We want it to be exactly X so we subtract the number of shelves that continues to state X+1.
*/

#include <bits/stdc++.h>

using namespace std;

const int N=3e4+5;

struct node{
	map<vector<char>,int> ch;
	int cnt;
	node():cnt(0){}
} trie[60*N];

string cur[15];
string arr[N];
char tmp[33];
int n,k,m,p,q;
int nodes;

void insert(int node,int l)
{
	trie[node].cnt++;
	if(l==p) return;
	vector<char> v(k);
	for(int i=0;i<k;i++)
		v[i]=cur[i][l];
	if(!trie[node].ch.count(v))
		trie[node].ch[v]=++nodes;
	insert(trie[node].ch[v],l+1);
}

int get(int node,int l,int x,vector<int> &ind)
{
	if(!node) return 0;
	if(l==x)
	{
		if(l==p) return trie[node].cnt;
		vector<char> nxt(k);
		for(int i=0;i<k;i++)
			nxt[i]=arr[ind[i]][l];
		if(trie[node].ch.count(nxt))
			return trie[node].cnt-trie[trie[node].ch[nxt]].cnt;
		return trie[node].cnt;
	}
	vector<char> v(k);
	for(int i=0;i<k;i++)
		v[i]=arr[ind[i]][l];
	return get(trie[node].ch[v],l+1,x,ind);
}

int main()
{
	freopen("sabin.in","r",stdin); freopen("sabin.out","w",stdout);
	scanf("%d %d %d %d %d",&n,&k,&m,&p,&q);
	nodes=1;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<k;j++)
			scanf("%s",tmp),cur[j]=tmp;
		insert(1,0);
	}
	for(int i=1;i<=m;i++)
		scanf("%s",tmp),arr[i]=tmp;
	while(q--)
	{
		vector<int> ind(k);
		int x;
		scanf("%d",&x);
		for(int i=0;i<k;i++)
			scanf("%d",&ind[i]);
		printf("%d\n",get(1,0,x,ind));
	}
}
