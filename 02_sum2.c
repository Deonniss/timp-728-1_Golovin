
#include <stdio.h>

int main(void)
{
    int i1, i2;
    if (scanf("%d %d", &i1, &i2) > 1) {
        int sum = i1 + i2;
	printf("%d", sum);
    }   
	return 0;
}