#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
void createSymbol(int range, char symbol){for(;range>=1;range--){printf("%c ", symbol);}}
void d_program();void main(){system("clear");printf("---------------------\n\n");d_program();
printf("\n\n---------------------\n\n");}
int input(char text[]){int inRET;printf("%s", text);scanf("%d", &inRET);return inRET;}
void debug(int num){printf("%d\n", num);} void d_calcTimeTaken(){int time = clock();
printf("\nTime Taken is : %f \n", (float)time/CLOCKS_PER_SEC);}
int d_swapInt(int *x, int *y){*x+=*y;*y=*x-*y;*x-=*y;}