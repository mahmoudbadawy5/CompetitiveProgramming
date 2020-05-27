/*
One information we can use is the number of vertices themselves. We will go through an edge from s to t in two cases:
- s < t and color[s] == color[t]
- s > t and color[s] != color[t]
So we can bfs from T and depending on the relation of s and t we put the number of s.
*/

#include "Annalib.h"
#include <bits/stdc++.h>

using namespace std;

void Anna(int K, int N, int T, int A[], int B[]) {
  	vector<int> adj[N+1];
  	for(int i=0;i<N-1;i++)
  	{
  		adj[A[i]].push_back(B[i]);
  		adj[B[i]].push_back(A[i]);
  	}
  	queue<int> q;
  	q.push(T);
  	vector<int> vis(N+1,0),ans(N+1,0);
  	vis[T]=1;
  	while(!q.empty())
  	{
  		int x=q.front();
  		q.pop();
  		for(int i:adj[x])
  		{
  			if(vis[i]) continue;
  			// i -> x
  			// i<x -> col[i] == col[x]
  			// i>x -> col[i] != col[x]
  			if(i<x) ans[i]=ans[x];
  			else ans[i]=1-ans[x];
  			q.push(i);
  			vis[i]=1;
  		}
  	}
  	for(int i=1;i<=N;i++)
  		Flag(i,ans[i]);
}

#include "Brunolib.h"

void Bruno(int K, int S, int F, int L, int P[], int Q[]) {
	for(int i=0;i<L;i++)
	{
		if(S<P[i] && F == Q[i])
		{
			Answer(P[i]);
			return;
		}
		if(S>P[i] && F != Q[i])
		{
			Answer(P[i]);
			return;
		}
	}
	Answer(S);
}

