/*
  Same as: https://github.com/nya-nya-meow/CompetitiveProgramming/blob/d9223c8ed33dda8127462c847fcfa517172fa997/Kattis/hanoi18.dividedoughnut.cpp
*/

#include <bits/stdc++.h>

using namespace std;

const int N=1e9;

int n;

void answer(int x)
{
	cout << "YES " << x << endl;
	exit(0);
}

int ask(int x)
{
	int y=(x+N/2-1)%N;
	cout << "QUERY " << x << " " << y << endl;
	int ans;
	cin >> ans;
	if(ans==n/2) answer(x);
	return ans;
}

int main()
{
	cin >> n;
	int st=0,en=N/2;
	int des=n/2,v0=ask(0);
	while(st<en)
	{
		int mid=(st+en)/2;
		int cur=ask(mid);
		if((v0<des&&des<cur)||(cur<des&&des<v0))
			en=mid-1;
		else
			st=mid+1;
	}
	answer((st+en)/2);
}
