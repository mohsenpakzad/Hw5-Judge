#include <stdio.h>

double cal(int number){
	double makhraj = (double)100-(2.0*(100.0-(double)number));
	return (double)100/makhraj;
}

int main () {
   int n;
   scanf("%d",&n);
   int i;
   int number;
   double result;
   for (i=0;i<n;i++){
   	scanf("%d",&number);
   		result = cal(number);
   		printf("Case Study #%d: %.6f\n",i+1,result);
   }
   return(0);
}
