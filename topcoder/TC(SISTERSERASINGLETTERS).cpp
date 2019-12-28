/*
min-max dp to know if you this move can make the next player difenitly lose.
dp[ind][pre][t] -> currently at index ind, the last unerased letter is pre, it's the turn of player t
*/

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>

using namespace std;

int mem[55][55][2];
string s;
int n;

int go(int ind,int pre,int t)
{
	if(ind>=n) return t;
	if(mem[ind][pre][t]!=-1) return mem[ind][pre][t];
	mem[ind][pre][t]=!go(ind+1,pre,1-t); // erasing this letter
	if(mem[ind][pre][t]) return 1;
	// leave the letter
	if(ind==n-1) return mem[ind][pre][t]=0;
	if(s[ind]<s[pre])
		return mem[ind][pre][t]=t;
	else if(s[ind]>s[pre])
		return mem[ind][pre][t]=!t;
	else
		return mem[ind][pre][t]=go(ind+1,pre+1,t);
}

class SistersErasingLetters {
public:
	string whoWins(string word) {
		s=word;
		n=s.size();
		memset(mem,-1,sizeof mem);
		return go(0,0,0)?"Camomile":"Romashka";
	}
};


<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
