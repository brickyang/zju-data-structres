#include <stdio.h>

int main() {
	int k;
	int n[100000] = { 0 };
	int max = 0;
	int sum = 0;
	int first = 0;
	int last = 0;
	int tmp_first = 0;
	int all_negtive = 1;
	int skip = 0;
	
	scanf("%d", &k);
	for (int i = 0; i < k; ++i)
		scanf("%d", &n[i]);
	
	for (int i = 0; i < k; ++i)
	{
		if (n[i] >= 0)
		{
			all_negtive = 0;
			break;
		}
	}
	
	if (all_negtive == 1)
	{
		printf("%d %d %d\n", 0, n[0], n[k - 1]);
		return 0;
	}
	
	if (k == 1)
	{
		printf("%d %d %d\n", n[0], n[0], n[0]);
		return 0;
	}
	
	tmp_first = n[0];
	
	for (int i = 0; i < k; ++i)
	{
		if (n[i] == 0)
			continue;
			
		if (sum == 0 && skip == 1)
			tmp_first = n[i];
			
		sum += n[i];
		
		if (sum < 0)
		{
			sum = 0;
			skip = 1;
		}	
		else if (sum > max) 
		{
			max = sum;
			first = tmp_first;
			last = n[i];
		}	
	}
	
	printf("%d %d %d\n", max, first, last);
	
	return 0;
}
