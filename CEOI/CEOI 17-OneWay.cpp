/*
First, Every non-bridge edge can take both directions. Now we only want to deal with bridges. Let's decompose the graph into a
bridge tree. We can make a dfs to know for each edge wheather it needs to be on left, right or it doesn't matter.*/

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int N=2*100005;

int n,ne,m,p;
int head[N],nxt[N],from[N],to[N],eid[N];
int disc[N],low[N];
int isartic[N],isbridge[N];
int stk[N],stksize,dfstime;
int cid[N],idc;
int a[N],b[N];
int isa[N],isb[N];
int rootid,childc;

void clear()
{
    memset(head,-1,sizeof head);
    ne=0;
}

void extractcomp(int k)
{
    do{
        int x=stk[--stksize];
        cid[x]=cid[x^1]=idc;
    }while(stk[stksize]!=k);
    idc++;
}

void dfs(int i,int e)
{
    disc[i]=low[i]=dfstime++;
    for(int k=head[i];~k;k=nxt[k])
    {
        if((k^1)==e) continue;
        int j=to[k];
        if(disc[j]==-1)
        {
            stk[stksize++]=k;
            dfs(j,k);
            low[i]=min(low[i],low[j]);
            if(i==rootid)
            {
                extractcomp(k);
                if(++childc>1)
                    isartic[i]=1;
            }
            else if(low[j]>=disc[i])
            {
                extractcomp(k);
                isartic[i]=1;
            }
            if(low[j]>disc[i])
                isbridge[k]=isbridge[k^1]=1;
        }
        else
        {
            low[i]=min(low[i],disc[j]);
            if(disc[j]<disc[i])
            stk[stksize++]=k;
        }
    }
}

void biconnected()
{
    memset(disc,-1,sizeof disc);
    for(rootid=1;rootid<=n;rootid++)
    {
        childc=0;
        if(disc[rootid]==-1)
        dfs(rootid,-1);
    }
}

void addedge(int x,int y,int id)
{
    nxt[ne]=head[x];
    from[ne]=x;
    to[ne]=y;
    eid[ne]=id;
    head[x]=ne++;
}

void addbiedge(int x,int y,int id)
{
    addedge(x,y,id);
    addedge(y,x,id);
}

char ans[N];
int uni[N];

int uni_find(int x)
{
    return uni[x]=(uni[x]==x?x:uni_find(uni[x]));
}

void unio(int x,int y)
{
    int a=uni_find(x); int b=uni_find(y);
    uni[a]=b;
}

vector< pair<int,int> > adj[N];
int ups[N],downs[N];
int vist[N];

void dfstree(int x,int pa)
{
    vist[x]=1;
    for(int i=0;i<adj[x].size();i++)
    {
        if(adj[x][i].F==pa) continue;
        int node=adj[x][i].F,edge=adj[x][i].S;
        dfstree(node,x);
        if(ups[node])
        {
            if(uni_find(from[edge])==node) ans[eid[edge]]='R';
            else ans[eid[edge]]='L';
        }
        if(downs[node])
        {
            if(uni_find(from[edge])==node) ans[eid[edge]]='L';
            else ans[eid[edge]]='R';
        }
        ups[x]+=ups[node];
        downs[x]+=downs[node];
    }
    if(ups[x]&&downs[x])
    {
        //LCA
        if(ups[x]>downs[x])
        {
            ups[x]-=downs[x];
            downs[x]=0;
        }
        else
        {
            downs[x]-=ups[x];
            ups[x]=0;
        }
    }
}

int main() {
    clear();
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        addbiedge(x,y,i);
    }
    scanf("%d",&p);
    for(int i=0;i<p;i++)
    {
        scanf("%d %d",&a[i],&b[i]);
        isa[a[i]]=1; isb[b[i]]=1;
    }
    biconnected();
    for(int i=1;i<=n;i++) uni[i]=i;
    for(int i=0;i<ne;i+=2)
    {
        if(isbridge[i]) continue;
        unio(from[i],to[i]);
    }
    for(int i=0;i<ne;i+=2)
    {
       if(!isbridge[i]) continue;
       int x=uni_find(from[i]); int y=uni_find(to[i]);
       adj[x].push_back({y,i});
       adj[y].push_back({x,i});
    }
    for(int i=0;i<ne;i+=2)
    {
        if(!isbridge[i])
            ans[eid[i]]='B';
    }
    for(int i=0;i<p;i++)
    {
        int x=uni_find(a[i]); int y=uni_find(b[i]);
        if(x!=y)
        {
            ups[x]++; downs[y]++;
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(!vist[uni_find(i)])
            dfstree(uni_find(i),-1);
    }
    for(int i=0;i<m;i++)
        if(!ans[i]) ans[i]='B';
    printf("%s\n",ans);
    return 0;
}
