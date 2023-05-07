/*
	Klaountio Manofi
	AM: 2022201900119
	dit19119@go.uop.gr
	
	Giwrgos Karudakhs
	AM: 2022201900075
	dit19075@go.uop.gr
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define H_ROW 20		//higher_row
#define L_ROW 5			//lowest_row
#define H_COLUMN 20		//highest_column
#define L_COLUMN 5		//lowest_column

int obstacle_count(int x,int y,int percentage);
int **make_board(int n,int m);
int **fake_board(int n,int m);
int last_game(int **board,int n,int m,int mines);
void generate_mines(int **board,int n,int m,int mines);
void generate_board(int **board,int n,int m);
void update_board(int **board,int **inv_board,int x,int y);
int recursion(int **board,int **inv_board,int n,int m,int x, int y);
void mark(int **inv_board,int x,int y);
void cheat(int **board,int x,int y);
void print_board(int **board,int n,int m);
void print_invboard(int **inv_board,int n,int m);
int is_mine(int x,int y,int **board);



int main() {
	
	int i,j,n,m;
	int **board,**inv_board;
	char level_difficulty,mode,game_closed;
	int obstacles,custom_mines;
	int row,col,x,y;
	int newgame = 1,desicion = 1;
	
	srand(time(NULL));
		
	printf("Type your prefered rows (please do not exceed %d and to be higher than %d )",H_ROW,L_ROW);
	scanf("%d",&n);
	while(n>H_ROW || n<L_ROW){  
		printf("Please,Type your prefered rows (please do not exceed %d and to be higher than %d )",H_ROW,L_ROW); 
		scanf(" %d",&n);
	}
	printf("Type your preferd column (please do not exceed %d and to be higher than %d )",H_COLUMN,L_COLUMN);
	scanf("%d",&m);
	while(m>H_COLUMN || m<L_COLUMN){
		printf("Please,Type your preferd column (please do not exceed %d and to be higher than %d )",H_COLUMN,L_COLUMN);
		scanf("%d",&m);
	}
	
	printf ("Choose the difficulty\n");
	printf ("(e)EASY , (n)Normal , (h)HARD , (i)impossible\n");
	printf ("\n");
	printf("If you want a custom game press (c)custom\n");			// custom game which the user determines the mines
	scanf(" %c",&level_difficulty);
	while((level_difficulty != 'e') && (level_difficulty != 'n') && (level_difficulty != 'h') && (level_difficulty != 'i')  && (level_difficulty != 'c')){
		printf("Please, Choose your prefered difficulty (e)easy ,(n)normal ,(h)hard ,(i)impossible \n");
		printf("If you want a custom game press (c)custom\n");
		scanf(" %c",&level_difficulty);
	}
	
	while(newgame != 0){ 							//START OF THE GAME
		if (level_difficulty == 'e'){
			 obstacles = obstacle_count(n,m,10);
		}
		else if (level_difficulty == 'm'){
			 obstacles = obstacle_count(n,m,15);
		} 
		else if(level_difficulty == 'h'){                           // Determine difficulty
			obstacles = obstacle_count(n,m,20);
		}
		else{
			obstacles = obstacle_count(n,m,25);
		}	
	
		board = make_board(n,m);  					// fuction, making the inside board
		inv_board = fake_board(n,m);  					// fuction, making the board that the user sees
		if(level_difficulty == 'c'){
			printf("How many mines do you want, please mines should not exceed %d: ",(n*m));
			scanf(" %d",&custom_mines);
			while(custom_mines>=(n*m)){
				printf("please mines should not exceed %d: ",(n*m));  //generating mines for the custom game
				scanf(" %d",&custom_mines);			      // user decides the mines 
			}
			generate_mines(board,n,m,custom_mines);
		}
		else{
			generate_mines(board,n,m,obstacles);  			// generating mines for the difficulties
		}

		generate_board(board,n,m); 					//filling the board with our numbers
		while(desicion != 0){
			printf("\n");
			printf("________________________________________________________________________________\n");
			printf("  -----------MAKE YOUR MOVE(s)----------- \n");
			print_invboard(inv_board,n,m);
			printf("-------------------------------------\n");
			printf("~If you want to play press (p)play\n");
			printf("~If you want to mark a cell press (m)mark\n");
			printf("~If you want to cheat press (c)cheat\n");
			printf("~If you want to see what the board has inside it,press (a)appear\n");			// if the user types 'a' then the final 
			printf("~If you want to Exit press (e)exit\n");							// board will appear
			printf("-------------------------------------\n");
			scanf(" %c",&mode);
			while ((mode!='p') && (mode!='m') && (mode!='c') && (mode!='a') && (mode!='e')){
				printf("----------------------------------------\n");
				printf("if you want to play press (p)play\n");
				printf("If you want to mark a cell press (m)mark\n");
				printf("If you want to cheat press (c)cheat\n");
				printf("If you want to see what the board has inside it,press (a)appear\n");
				printf("If you want to exit press (e)xit\n");
				printf("----------------------------------------\n");
				scanf(" %c",&mode);
			}
			if (mode == 'e'){
				printf("	!!WARNING!!	\n");
				printf("Are you sure you want to exit?\n");
				printf("Press y for yes\n");
				printf("press n for no\n");
				scanf(" %c",&game_closed);				
				if (game_closed == 'y'){
					printf("-----GOOD BYE-----\n");
					exit(0);
				}
			}
			else if(mode == 'a'){
				print_board(board,n,m);
			}			
			else {
				printf("Make your first move X-axis: ");
				scanf("%d",&x);
				while(x<1 || x>n){
					printf("Your X-axis should be greater than 0 and lower than %d,try again : ",n);
					scanf("%d",&x);
				}
				printf("Make your second move Y-axis: ");
				scanf("%d",&y);
				while( y<1 || y>m ){					
					printf("Your Y-axis should be greater than 0 and lower than %d,try again : ",m);
					scanf("%d",&y);
				}
				x=x-1;  
				y=y-1;
			
				if(mode == 'c'){
					cheat(board,x,y);  			// function for cheat
				}
				if(mode == 'm'){
					mark(inv_board,x,y);
					print_invboard(inv_board,n,m); 		// function for mark
				}
				if(mode == 'p'){				// play
					if(board[x][y]=='.'){
						recursion(board,inv_board,n,m,x,y);
					}
					else{
						update_board(board,inv_board,x,y);
					}	
				desicion = is_mine(x,y,board);  		// is this a mine? if yes return 0	
				}
				if (desicion==0){
					printf("\n");
					printf("You Lost!,You hit a mine \n");
					exit(0);
				}
			
				newgame = last_game(inv_board,n,m,obstacles); 	 // did the round end? if yes return 0
				if (newgame == 0){
					printf("Good job you made it \n");
					n = n+5;
					m = m+5;
					desicion = 0;  				// making desicion = 0 so we can get out of the loop
				}
			}
		}
		
		desicion=1; 							// then making desicion = 1 so we can get inside with our new board
		
		if(n > H_ROW && m>H_COLUMN){  
			printf("------------------------------\n");							// determins the win condition
			printf("You won the game congrats!!! \n");
			newgame = 0; 						// if 0 then end the programm
		}else{
			newgame=1; 						// if 1 continue
		}
	}
	
	for(i=0;i<n;i++){
		free(board[i]);
	}
	free(board);
	for(i=0;i<n;i++){
		free(inv_board[i]);						// freeing both boards
	}
	free(inv_board);
	
	return 0;
	
}

int obstacle_count(int x,int y,int percentage){ 					// percentage of mines 
	int percent,obstacle_percentage;
	percent = x*y;
	obstacle_percentage = percent*percentage/100;
	return obstacle_percentage;	
}

int **make_board(int n, int m){
	int i,j;
	int **board = NULL;
											// making our main board
	board = (int**)malloc(n*sizeof(int*));
	for (i=0; i<n; i++){
		board[i]=(int*)malloc(m*sizeof(int));
	}
	
	for (i=0;i<n;i++){
		for(j=0;j<m;j++){
			board[i][j]='.';
		}
	}	
	return board;
}

int **fake_board(int n,int m){
	int i,j;
	int **inv_board = NULL;
	
	inv_board = (int**)malloc(n*sizeof(int*));
	for(i=0;i<n;i++){
		inv_board[i]=(int*)malloc(m*sizeof(int));
	}
											// making our board that the user sees	
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			inv_board[i][j]='#';
		}
	}
	return inv_board;
}

int last_game(int **board,int n,int m,int mines){		// determines if the round is over
	int i,j,sum,counter=0;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(board[i][j]=='.'|| board[i][j]=='1'|| board[i][j]=='2'|| board[i][j]=='3' || board[i][j]=='4' ||
			   board[i][j]=='5'|| board[i][j]=='6'|| board[i][j]=='7'|| board[i][j]=='8'){
			counter++;												
			}
		}						
	}
	sum = (m*n)-mines; 					//all cells without the mines
	if(counter >= sum){
		printf("End of stage! WELL DONE\n");
		return 0;
	}
	else{
		return 1;
	}
}

void generate_mines(int **board,int n,int m,int mines){		//generating mines
	
	int row,col,i;	
	for (i=0;i<mines;i++){
	 	row = rand() % n;
		col = rand() % m;
		if (board[row][col]== '@'){			
			i--;
		}
		else{
			board[row][col]= '@';
		}
	}
}

void generate_board(int **board,int n,int m){  					// generating the board with neighboors
	int i,j;
	char counter ='0';
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
			     counter = '0';
			}
			
		}
	}
}

void update_board(int **board, int **inv_board, int x, int y){  		// update the board to the user
	inv_board[x][y] = board[x][y];
}

int recursion(int **board, int **inv_board, int xBoardSize, int yBoardSize, int x, int y){
	if( (x < 0) || (y < 0) || (x >= xBoardSize) || (y >= yBoardSize) || (inv_board[x][y] != '#') ){		//recursion
		return 0;
	}
	update_board(board, inv_board, x, y);
	if(board[x][y] == '.'){
		recursion(board, inv_board, xBoardSize, yBoardSize, x - 1, y);
		recursion(board, inv_board, xBoardSize, yBoardSize, x + 1, y);
		recursion(board, inv_board, xBoardSize, yBoardSize, x, y-1);
		recursion(board, inv_board, xBoardSize, yBoardSize, x, y+1);
		recursion(board, inv_board, xBoardSize, yBoardSize, x-1, y-1);
		recursion(board, inv_board, xBoardSize, yBoardSize, x+1, y-1);
		recursion(board, inv_board, xBoardSize, yBoardSize, x-1, y+1);
		recursion(board, inv_board, xBoardSize, yBoardSize, x+1, y+1);
	}
}
void mark(int **inv_board,int x,int y){								// mark
	inv_board[x][y]='@';
}

void cheat(int **board,int x,int y){								// cheat
	if(board[x][y]=='.'){ 
		printf("\n");
		printf("--- No mines nearby ---\n");
		printf("---YOU ARE SAFE---\n");
	}
	else if(board[x][y]=='1' || board[x][y]== '2' || board[x][y]=='3' || board[x][y]=='4'){
		printf("---There are %c mines nearby---\n",board[x][y]);
		printf("---BE CAREFUL!!!---\n");
	}
	else{
		printf("---This is a mine, LOOK OUT---\n");
	}
}

void print_board(int **board,int n,int m){
	int i,j;
	for ( j = 0; j < m; j++) {
		if (j==0){
        	printf("      %d", j+1);
        	}
        	else{
        		if(j<9){
        		printf("  %d", j+1);
        		}
        		else{
        			printf(" %d", j+1);
        		}
        	}
        }
        printf("\n");
        printf("-------");
        for (j=0;j<m;j++){
        	printf("---");
        }
        printf("\n");
   	for (i = 0; i < n; ++i) {
    		if (i<9){
    			printf("  %d| ", i+1);	
    		}
    		else{
    			printf(" %d| ", i+1);
    		}
        for (j = 0; j < m; ++j) {
            printf(" %c ", board[i][j]);
        }
        printf("\n");
    }
}

void print_invboard(int **inv_board,int n,int m){
	int i,j;
	for ( j = 0; j < m; j++) {
		if (j==0){
        	printf("      %d", j+1);
        	}
        	else{
        		if(j<9){
        		printf("  %d", j+1);
        		}
        		else{
        			printf(" %d", j+1);
        		}
        	}
        }
        
        printf("\n");
        printf("-------");
        for (j=0;j<m;j++){
        	printf("---");
        }
        printf("\n");
   	for (i = 0; i < n; ++i) {
    		if (i<9){
    			printf("  %d| ", i+1);	
    		}
    		else{
    			printf(" %d| ", i+1);
    		}
        for (j = 0; j < m; ++j) {
            printf(" %c ", inv_board[i][j]);
        }
        printf("\n");
    }
    	
   
}
int is_mine(int x,int y,int **board){					// if is mine return 0
	if (board[x][y]== '@'){
		return 0;
	}
}

