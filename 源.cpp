#include<iostream>
using namespace std;
int main()
{
	int n;
	int Max = -999, sum = 0;
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++)
	{
		if (sum < 0)
		{
			sum = a[i];
		}
		else
		{
			sum = sum + a[i];
		}
		Max = max(Max, sum);
	}
	cout << Max << endl;
	return 0;
}