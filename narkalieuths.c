#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define H_ROW 20
#define L_ROW 2
#define H_COLUMN 20
#define L_COLUMN 2

int obstacle_count(int x,int y,int percentage);
int **make_board(int n,int m);
int last_game(int **board,int n,int m,int mines);
//void update_board(char **board,int x,int y);
void generate_mines(int **board,int n,int m,int mines);
void generate_board(int **board,int n,int m);
void print_board(int **board,int n,int m);
int is_mine(int x,int y,int **board);
int is_open(int **board,int x,int y);
//void has_neighboor(char **board,int x,int y);

int main() {
	
	int i,j,n,m;
	int **board;
	char level_difficulty;
	int obstacles;
	int row,col,x,y;
	int newgame = 1,desicion = 1;
	
	srand(time(NULL));
	
	do{	
		printf("Type your prefered rows (please do not exceed %d and to be higher than %d )",H_ROW,L_ROW);
		scanf("%d",&n);
	}while(n>H_ROW || n<L_ROW);
	
	do{
		printf("Type your preferd column (please do not exceed %d and to be higher than %d )",H_COLUMN,L_COLUMN);
		scanf("%d",&m);
	}while(m>H_COLUMN || m<L_COLUMN);
	
	
	
	do{
	printf("Please Choose your prefered difficulty (e)easy ,(n)normal ,(h)hard ,(i)impossible \n");
	scanf("%c",&level_difficulty);
	 
	}while((level_difficulty != 'e') && (level_difficulty != 'n') && (level_difficulty != 'h') && (level_difficulty != 'i'));
	
	while(newgame != 0){ //ARXH PAIXNIDIOU
		if (level_difficulty == 'e'){
			 obstacles = obstacle_count(n,m,10);
		}
		else if (level_difficulty == 'm'){
			 obstacles = obstacle_count(n,m,15);
		} 
		else if(level_difficulty == 'h'){
			obstacles = obstacle_count(n,m,20);
		}
		else{
			obstacles = obstacle_count(n,m,25);
		}	
	
		board = make_board(n,m);
		printf("  Make your move(s) \n");
		generate_mines(board,n,m,obstacles);
		printf("  they got in \n");
		generate_board(board,n,m);
		while(desicion != 0){
			printf("\n");
			print_board(board,n,m);
			
			do{
				printf("Make your first move X-axis: ");
				scanf("%d",&x);
			}while( x<1 || x>n );
			do{
				printf("Make your second move Y-axis: ");
				scanf("%d",&y);
			}while( y<1 || y>m );
			//has_neighboor(board,x,y);
				/*if(opencell == 0){
					printf("the cell is already open");
					opencell = 1;
				}
				else{
					update_board(board,x,y);
				}
				
				printf(" this is the opencell %d",opencell);*/
				
			desicion = is_mine(x,y,board);
			if (desicion==0){
				printf("You steped on a mine . You lost \n");
				exit(0);
			}
			
			newgame = last_game(board,n,m,obstacles);
			if (newgame == 0){
				printf("Good job you made it \n");
				n = n+5;
				m = m+5;
				desicion = 0;
			}
		}
		
		desicion=1;
		if(n > H_ROW && m>H_COLUMN){
			printf("You won the game congrats!!! /n");
			newgame = 0;
		}else{
			newgame=1;
		}
	}
	free(board);
	
	return 0;
	
}

int obstacle_count(int x,int y,int percentage){
	int percent,obstacle_percentage;
	percent = x*y;
	obstacle_percentage = percent*percentage/100;
	return obstacle_percentage;	
}

int **make_board(int n, int m){
	int **board = NULL;
	
	board = (int**)malloc(n*sizeof(int*));
	for (int i=0; i<n; i++){
		board[i]=(int*)malloc(m*sizeof(int));
	}
	
	for (int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			board[i][j]='.';
		}
	}
	
	return board;
}

//void update_board(char **board,int x,int y){
	//board[x][y]='.';
//}
int is_open(int **board,int x,int y){
	
	if(board[x][y]== '.'){
		return 0;
	}
	else{
		return 1;
	}
	
	
}
int last_game(int **board,int n,int m,int mines){
	int i,j,sum,counter=0;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(board[i][j]== '@'){
				counter++;
			}
		}
	}
	sum = (m*n)-mines; //OLA TA KELIA MAS XWRIS TA MINES
	if(counter >= sum){
		printf("End of stage! \n");
		return 0;
	}
	else{
		printf("Continue \n");
		return 1;
	}
}

void generate_mines(int **board,int n,int m,int mines){
	
	int row,col;	
	for (int i=0;i<mines;i++){
	 	row = rand() % n;
		col = rand() % m;
		if (board[row][col]== '@'){
			--i;
		}
		else{
			board[row][col]= '@';
		}
	}
}

void generate_board(int **board,int n,int m){
	int i,j;
	char counter ='0';
	printf("the counter is %c \n",counter);
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(board[i][j] == '.'){
				if(i<n-1){
					if(board[i+1][j] == '@'){
						counter++;
						board[i][j]=counter;
					}
				}
				if(i!=0){
					if(board[i-1][j] == '@'){
						counter++;
						board[i][j]=counter;
					}
				}
				if(j<m-1){
					if(board[i][j+1] == '@'){
						counter++;
						board[i][j]=counter;
					}
				}	
				if(j!=0){
					if(board[i][j-1]== '@'){
						counter++;
						board[i][j]=counter;
					}
				}
				
				if( i!=0 && j!=0){
					if(board[i-1][j-1]== '@'){
						counter++;
						board[i][j]=counter;	
					}
				}
				if(i!=0 && j<m-1){	
					if(board[i-1][j+1]=='@'){
						counter++;
						board[i][j]=counter;
					}
				}
				if(i<n-1 && j!=0){
					if(board[i+1][j-1]=='@'){
						counter++;
						board[i][j]=counter;
					}
				}
				if(i<n-1 && j<m-1){
					if(board[i+1][j+1]=='@'){
						counter++;
						board[i][j]=counter;
					}
				}
			     /* edw } */
			     counter = '0';
			}
			
		}
	}
}

void print_board(int **board,int n,int m){

	int i,j;
	printf(" 0 ");
	for (int j = 0; j < m; j++) {
        	printf(" %d  ", j+1);
        }
        printf("\n");
    	for (i = 0; i < n; i++) {
    		printf(" %d|", i+1);
        	//printf(" |");
        for (j = 0; j < m; j++) {
        	
        	printf(" %c  ", board[i][j]);
            
        }
        printf("|\n");
    }
    printf("\n");
}

int is_mine(int x,int y,int **board){
	x=x-1;
	y=y-1;
	if (board[x][y]== '@'){
		printf("You Lost !");
		return 0;
	}

	/*else{
		
		
			board[x][y]='.';
			printf("Continue Playing");
			return 1;
		
	}*/
}

int show_cell(int **board,int x,int y){
	if(!is_mine(x,y,board) && board[x][y]=='#'){
		return 1;
	}
	else{
		return 0;
	}
}

/*void has_neighboor(char **board,int x,int y){
	
	if(is_mine(x,y,board)){

	if (board[x-1][y-1]=='@' || board[x-1][y]=='@' || board[x-1][y+1]=='@' || board[x][y-1]=='@' || board[x][y+1]=='@' || board[x+1][y-1]=='@'|| board[x+1][y]=='@' || board[x+1][y+1] == '@'){
		
		board[x][y]='1';
	}
	
	(board[x-1][y-1]=='@' && ((x-1>=n) && (y-1>=m)))|| (board[x-1][y]=='@' && (x-1>=n)) || (board[x-1][y+1]=='@'&& ((x-1>=n)&&
(y+1<=m))) || (board[x][y-1]=='@'&& (y-1>=m)) || (board[x][y+1]=='@'&& (y+1<=m)) || (board[x+1][y-1]=='@' && ((x+1<=n)&&(y-1>=m))) || (board[x+1][y]=='@'&&(x+1<=n)) || (board[x+1][y+1] == '@'&&((x+1<=n)&&(y+1<=m)))
}
}*/


/* printf(" ");
    	for (int j = 1; j <= m; j++) {
        	printf("%2d ", j);
    	}
    	printf("\n");

    	// Print table separator
    	printf("--");
    	for (int j = 1; j <= m; j++) {
        	printf("---");
    	}
    	printf("\n");

    	// Print table content
    	for (int i = 1; i <= n; i++) {
        	printf("%d|", i); // print row header
        	for (int j = 1; j <= m; j++) {
            		printf(" # "); // print table cell value
        	}
        	printf("\n");
    	} */
    	
    	/*for (int i=0;i<obstacles;i++){
		row = rand() % n;
		col = rand() % m;
		if (board[row][col]== '@'){
			--i;
		}
		else{
			board[row][col]='@';
		}
	}*/


