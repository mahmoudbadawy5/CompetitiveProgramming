/*
  Same as: https://github.com/nya-nya-meow/CompetitiveProgramming/blob/master/Kattis/jurassicjungle.cpp
*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
	while(true)
	{
		int n,m;
		cin >> n >> m;
		if(n==-1) break;
		if(n==m)
		{
			cout << "YES" << endl;
			for(int i=0;i<n;i++)
				cout << i+1 << " " << (i+1)%n+1 << endl;
		}
		else if(n%2==0 && n*n/4 == m)
		{
			cout << "YES" << endl;
			for(int i=1;i<=n/2;i++)
				for(int j=n/2+1;j<=n;j++)
					cout << i << " " << j << endl;
		}
		else if(n*(n-1)/2 == m)
		{
			cout << "YES" << endl;
			for(int i=1;i<=n;i++)
				for(int j=i+1;j<=n;j++)
					cout << i <<" " << j << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
}
