//This is the program that I wrote while solving my first Post Lab 1.
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
  int randnum, usernum;
  char yn;
  srand(time(0));
  printf("Welcome to the Number Guessing Game!\n");
  printf("Are you ready(Hit Y to start): ");
  scanf("%c", &yn);
  if(yn=='Y' || yn=='y'){
    printf("Wohoo! Get ready!\n");
    randnum = rand() % 100 + 1;
    printf("Guess the number: ");
    scanf("%d", &usernum);
    if(usernum==randnum){
        printf("WOW! You guessed it right! Great.\n");
    }
    else if(usernum>randnum){
        printf("Ah! man, too high!\n");
    }
    else if(usernum<randnum){
        printf("Well, that's a bit low!\n");
    }
    else{
        printf("Nooo! that's invalid\n");
    }
  }
    else{
        printf("Well, alright, Your Choice!\n");
    }
    printf("Thanks for playing. Wanna try again?\n");
    printf("Run the program again!");
    return 0;  
  }
