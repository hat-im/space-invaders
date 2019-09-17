struct Player{
    char logo;
    char bullet;
    char name[20];
};
struct Enemy{
    char logo;
    char shielded;
    char exploded;
    char laser;

};
typedef struct Player player;
typedef struct Enemy enemy;
int* setOrder(int n);
void birdmanPrint(char *s,int l, int t);
int cheatcode();
void endgame(int score, int victory);
void welcome();
void beginGame();
