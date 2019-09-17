#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include"inter.h"
int main(){
    int choice=4;
    welcome();
    do{
            printf("\nSelect option:\n1. PLAY\n2.Instructions \n3.Exit\n");

    scanf("%d",&choice);
    switch(choice){
    case 1:
        beginGame();
        choice=3;
        break;
    case 2:
        printf("\nYour objective is to save your system by shooting down all the alien invaders.\npress \'A\' and \'D\' to move left and right and press \'M\' to fire your laser.\n\n\t\t\tPress any key to return to menu");
        getch();
        system("cls");
        break;
    case 3:
        exit(0);
    default:
        printf("\nInvalid input. Learn to read.");
        choice=1;
    }
    }
    while(choice<3 && choice>0);
    return 0;
}
