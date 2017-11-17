#include <stdio.h>

int main() {
	int k;
	int n[100000] = { 0 };
	int max = 0;
	int sum = 0;
	
	scanf("%d", &k);
	for (int i = 0; i < k; ++i)
		scanf("%d", &n[i]);
	
	for (int i = 0; i < k; ++i) {
		sum += n[i];
		
		if (sum < 0)
			sum = 0;
		else if (sum > max)
			max = sum;
	}
	
	printf("%d\n", max);
	
	return 0;
}
