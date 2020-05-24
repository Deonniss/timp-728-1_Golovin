#include <stdio.h>
#include <math.h> 
int main()
{
    int n; 
    double a, sum = 0, one =-1, cube = 3, deg, s1, s2;
    
    if (scanf("%d", &n) == 1) {
    	int i;
    	for (i = 0; i < n; i++) {
        if (scanf("%lf", &a) == 1) { 
        	deg = (double)i + 2;
        	s1 = pow(one, deg);
        	s2 = pow(a, cube);
        	sum += s1 * s2;
        }
        
    }
    printf("%lf", sum);
    }
    return 0;
}