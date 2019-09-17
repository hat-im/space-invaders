#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include"inter.h"

int* setOrder(int n){//shuffles the elements of the array
    int *o=calloc(n,sizeof(int));
    for(int i=0;i<n;i++){
        *(o+i)=rand()%30;
    }
    return o;
}
void birdmanPrint(char *s,int l, int t){//prints the characters on the screen in a random order
    printf("\e[?25l");
    int *o=setOrder(l);
    for(int i=0;i<=30;i+=2){
        for(int j=0;j<l;j++)
            if(i>=*(o+j)||*(s+j)=='\n')
                printf("%c",*(s+j));
            else
                printf("%c",' ');
        Sleep(t);
        if(i<30)
            system("cls");
    }
}
int cheatcode(){
    printf("\e[?25h");
    char c1[]="hatim";
    char c2[]="poorvi";
    char c3[]="sidharth";
    system("cls");
    char s[]="Congratulations! You have entered the cheat menu!";
    for(int i=0;i<strlen(s);i++){
        printf("%c",s[i]);
        Sleep(1);
    }
    Sleep(1000);
    printf("\nPress any key to proceed");
    getch();
    system("cls");
    printf("Enter cheat code:");
    scanf("%s",s);
    printf("\e[?25l");
    if(!(strcmp(s,c1))){
        printf("Congratulations! You have unlocked rapid fire!");
        getch();
        return 0;
    }
    if(!strcmp(s,c2)){
        printf("Congratulations! You've unlocked freeze. Press S to activate.");
        getch();
        return 1;
    }
    if(!strcmp(s,c3)){
        printf("Congratulations! You've gained bonus points!");
        getch();
        return 2;
    }
    printf("No such cheatcode. Try again later");
    getch();
    return 4;
}
void endGame(int score, int victory){
    if (victory != 0) {
        printf("\n \n \n \n \n \n               CONGRATULATIONS! \n \n \n \n \n");
        Sleep(1000);
        printf("\n \n               Score: %d", score);
        Sleep(1000);
        printf("\n \n \n \n               Well done");
        Sleep(1000);
        printf(", Hero.");
        Sleep(1000);
        getch();
    }
    else {
        printf("\n \n \n \n \n \n               You have failed.");
        Sleep(1000);
        printf("\n \n \n \n \n \n               Windows is doomed.");
        Sleep(1000);
        printf("\n \n               Final Score: %d", score);
        getch();
    }
}
void welcome(){
    printf("\t\t\tpress any key to start.");
    getch();
    system("cls");
    char s[]="XXXXX XXXXX XXXXX XXXXX XXXXX\nX     X   X X   X X     X    \nXXXXX XXXXX XXXXX X     XXXX \n    X X     X   X X     X    \nXXXXX X     X   X XXXXX XXXXX\n                             XXXXX X   X X     X XXXXX XXXX  XXXXX XXXX  XXXXX\n                               X   XX  X  X   X  X   X X   X X     X   X X\n                               X   X X X  X   X  XXXXX X   X XXXX  XXXX  XXXXX\n                               X   X  XX   X X   X   X X   X X     XX        X\n                             XXXXX X   X    X    X   X XXXX  XXXXX X  X  XXXXX";
    birdmanPrint(s,strlen(s),200);
    printf("\nPress Enter to start.");
    getch();
}
void beginGame(){
    printf("\e[?25l");
    int sizey=23;
    int sizex=40;//Dimensions of the play area
    int laserVal=4;//minimum laser reload time
    int x, y, yi;
    char world[sizey][sizex];
    player p;
    p.logo='A';
    p.bullet='^';
    enemy e;
    e.logo='M';
    e.shielded='O';
    e.laser='U';
    e.exploded='X';
    int score=0;
    int victory=1;
    int laserReady=1;//Keeps track of how much time has passed since the player last fired the laser.
    int freezeReady=0;
    int enemyReady=0;//Keeps track of how much time has passed since
    int totalEnemies=0;

    for (x = 0; x < sizex; x ++) {
        for (y = 0; y < sizey; y ++) {
            if ((y+1) % 2 == 0 && y < 7 && x > 4
            && x < sizex - 5 && x % 2 ==0) {
                world[y][x] = e.logo;
                totalEnemies ++;
            }
            else if ((y+1) % 2 == 0 && y >= 7 && y < 9 && x > 4
            && x < sizex - 5 && x % 2 ==0){
                world[y][x] = e.shielded;
                totalEnemies = totalEnemies + 2;
            }
            else {
                world[y][x] = ' ';
            }
        }
    }
    world[sizey - 1][sizex / 2] = p.logo;
    int i = 1;
    char direction = 'l';
    char keyPress;
    int currentEnemies=totalEnemies;
    while(currentEnemies>0&&victory) {
        int drop = 0;
        int enemySpeed=1+10*currentEnemies/totalEnemies;
        laserReady++;

        /*display world*/
        system("cls");
        printf("     \t\t\tSCORE:    %d", score);
        printf("\n");
            for (y = 0; y < sizey; y ++) {
            printf("\t\t\t|");
                for (x = 0; x < sizex; x ++) {
                    printf("%c",world[y][x]);
                }
            printf("|");
            printf("\n");
            }

        /*laser time*/
        for (x = 0; x < sizex; x ++) {
            for (y = sizey-1; y >= 0; y --) {
                if (i%2 == 0 && world[y][x] == e.laser
                && (world[y+1][x] != e.logo & world[y+1][x] != e.shielded)){
                world[y+1][x] = e.laser;
                world[y][x] = ' ';
                }
                else if (i%2 == 0 && world[y][x] == e.laser
                && (world[y+1][x] == e.logo | world[y+1][x] == e.shielded)){
                    world[y][x] = ' ';
                }
            }
        }
        for (x = 0; x < sizex; x ++) {
            for (y = 0; y < sizey; y ++) {
                if ((i % 5) == 0 && (world[y][x] == e.shielded
                | world[y][x] == e.logo) && (rand() % 15) > 13
                && world[y+1][x] != p.bullet) {
                    for (yi = y+1; yi < sizey; yi ++) {
                        if (world[yi][x] == e.logo
                        | world[yi][x] == e.shielded) {
                            enemyReady = 0;
                            break;
                        }
                        enemyReady = 1;
                    }
                    if (enemyReady) {
                        world[y+1][x] = e.laser;
                    }
                }
                if (world[y][x] == p.bullet && world[y-1][x] == e.logo) {
                    world[y][x] = ' ';
                    world[y-1][x] = e.exploded;
                    currentEnemies--;
                    score = score + 50;
                }
                else if (world[y][x] == p.bullet
                && world[y-1][x] == e.shielded) {
                    world[y][x] = ' ';
                    world[y-1][x] = e.logo;
                    currentEnemies--;
                    score = score + 50;
                }
                else if (world[y][x] == p.bullet
                && world[y-1][x] == e.laser) {
                    world[y][x] = ' ';
                }
                else if (world[y][x] == e.exploded) {
                    world[y][x] = ' ';
                }
                else if ((i+1) % 2 == 0 && world[y][x] == e.laser
                && world[y+1][x] == p.logo) {
                    world[y+1][x] = e.exploded;
                    world[y][x] = ' ';
                    victory = 0;
                }
                else if (world[y][x] == p.bullet
                && world[y-1][x] != e.laser) {
                        world[y][x] = ' ';
                        world[y-1][x] = p.bullet;
                }
            }
        }

        /*update enemy direction*/
        for (y = 0; y < sizey; y ++) {
            if (world[y][0] == e.logo) {
                direction = 'r';
                drop = 1;
                break;
            }
            if (world[y][sizex-1] == e.logo){
                direction = 'l';
                drop = 1;
                break;
            }
        }

        /*update board*/
        if (i % enemySpeed == 0) {
            if (direction == 'l') {
                for (x = 0; x < sizex - 1; x ++) {
                    for (y = 0; y < sizey; y ++) {
                        if (drop && (world[y-1][x+1] == e.logo
                            || world[y-1][x+1] == e.shielded)){
                            world[y][x] = world[y-1][x+1];
                            world[y-1][x+1] = ' ';
                        }
                        else if (!drop && (world[y][x+1] == e.logo
                            || world[y][x+1] == e.shielded)) {
                            world[y][x] = world[y][x+1];
                            world[y][x+1] = ' ';
                        }
                    }
                }
            }
            else {
                for (x = sizex; x > 0; x --) {
                    for (y = 0; y < sizey; y ++) {
                        if (drop && (world[y-1][x-1] == e.logo
                            || world[y-1][x-1] == e.shielded)) {
                            world[y][x] = world[y-1][x-1];
                            world[y-1][x-1] = ' ';
                        }
                        else if (!drop && (world[y][x-1] == e.logo
                            || world[y][x-1] == e.shielded)) {
                            world[y][x] = world[y][x-1];
                            world[y][x-1] = ' ';
                        }
                    }
                }
            }
            for (x = 0; x < sizex; x ++) {
                if (world[sizey - 1][x] == e.logo) {
                    victory = 0;
                }
            }
        }

        /*control player*/
        if(kbhit()){
            keyPress = getch();
        }
        else {
            keyPress = ' ';
        }
        if (keyPress == 'a') {
            for (x = 0; x < sizex; x = x+1) {
                if ( world[sizey-1][x+1] == p.logo) {
                    world[sizey-1][x] = p.logo;
                    world[sizey-1][x+1] = ' ';
                }
            }
        }

        if (keyPress == 'd') {
            for (x = sizex - 1; x > 0; x = x-1) {
                if ( world[sizey-1][x-1] == p.logo) {
                    world[sizey-1][x] = p.logo;
                    world[sizey-1][x-1] = ' ';
                }
            }
        }

        if (keyPress == 's' && freezeReady && i) {
            i-=1;
        }

        if (keyPress == 'm' && laserReady > laserVal) {
            for (x = 0; x < sizex; x = x+1) {
                if ( world[sizey-1][x] == p.logo) {
                    world[sizey - 2][x] = p.bullet;
                    laserReady = 0;
                }
            }
        }
        if (keyPress=='9'){
            switch(cheatcode()){
        case 0:
            laserVal=1;
            break;
        case 1:
            freezeReady=1;
            break;
        case 2:
            score+=5000;
            break;
        }
        Sleep(50);
        }
        i++;

    }
    system("cls");
        printf("     SCORE:    %d", score);
        printf("\n");
            for (y = 0; y < sizey; y ++) {
            printf("\t\t|");
                for (x = 0; x < sizex; x ++) {
                    printf("%c",world[y][x]);
                }
            printf("|");
            printf("\n");
            }
    Sleep(1000);
    system("cls");

    if(currentEnemies)
        endGame(score,0);
    else
        endGame(score,1);
    printf("\e[?25h");
}

