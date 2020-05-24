#include <stdio.h>

int main()
{   
    int n, count = 0; 
    double a;
    if (scanf("%d", &n) == 1) {  
    	int i;
    for (i = 0; i < n; i++) {
        if (scanf ("%lf", &a) == 1) {
        	if (a > 0) {
         	   count++;
        	}
		}
    }
    printf("%d", count);
}
    return 0;
}
