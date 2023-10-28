/*It's an important sequence in maths and has a lot importance in daily life.
It's linked to the golden ratio used in architecture, art and modern technologies.*/

#include <stdio.h>

int main(){
    
    int n,num0=0,num1=1,num2;
    printf("Enter a positive integer: ");
    scanf("%d", &n);
    if(n>=0){ //input validation added
    for(int i=0;i<n;i++){
        printf("%d ",num0);
        num2=num0+num1;
        num0=num1;
        num1=num2;
    }
    }
    else{
        printf("This number isn't positive.");
    }
    return 0;
}
