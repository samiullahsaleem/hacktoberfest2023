#include <stdio.h>

int main() {
    float basic, homealw, fuelalw, otheralw, gross; 
    printf("What's your basic salary: ");
    scanf("%f", &basic);
    printf("What's your home allowance: ");
    scanf("%f", &homealw);
    printf("What's your fuel allowance:");
    scanf("%f", &fuelalw);
    printf("Any other allowance?(enter amount): ");
    scanf("%f", &otheralw);
    gross = basic+homealw+fuelalw+otheralw;
    printf("Your gross salary is %.2f", gross);
    return 0;
}
