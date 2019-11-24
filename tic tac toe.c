#include <stdio.h>


/******************************************************************************************************************************
*Variables
******************************************************************************************************************************/

char board1[4][5];				//Array to store '|' lines
char board2[4][4];				//Array to store 'X' and 'O'
char nameX[20], nameO[20];		//Name of gamers
int gPos = 0; 					//Grid position variable to be entered by gamers
int row = 0;					//Variable to find the exact location in the array					
int column = 0;					//Variable to find the exact location in the array
int errorFlag = 0;				//Variable to detect invalid integer entry
char term;							

/******************************************************************************************************************************
*Prototypes
******************************************************************************************************************************/

void creatGameBoard();			//To create initial TIC TAC TOE game board 
void printGameBoard();			//To print initial TIC TAC TOE game board
void enterUserNames();			//To enter gamer names 
void printBoardWithGridPos();   //To print the game board with grid location for gamer reference
void enterGridPosX();			//To enter grid position be 'X' gamer 
void enterGridPosO();			//To enter grid position be 'O' gamer
void enterElement(char ch);			//To enter 'X' or 'O' element to array
int checkWinner();				//To check the winner
char checkHortVert();			//To check the condition of win on horizontal(row) and vertical(column) elements of the array
char checkDiag();				//To check the condition of win on diagonal elements of the array

/******************************************************************************************************************************
*Code
******************************************************************************************************************************/

int main()
{   
    int check ;
    
    creatGameBoard();			 
    printGameBoard();			
    enterUserNames();			
    printBoardWithGridPos();
    
    for(int moves = 0; moves < 8; moves++)
    {
        enterGridPosX();	  // To enter grid position by 'X' user
        if(errorFlag)  		 // Exit game if the entered grid position is a invalid integer
        {
            printf("Invalid entry Game exit");
            break;
        }
        else
        {
            printGameBoard();	//To print game board after each turn
            if(moves > 2)		// Check for winner after each turn of gamer  
            {
                check = checkWinner();
                if(check == 1)
                {
                    printf("Hooray!! %s is the winner\n",nameX);
                    break;
                }    
                else if(check == 2)
                {
                    printf("Hooray!! %s is the winner\n",nameO);
                    break;
                }
            }
        } 
        
        enterGridPosO();	// To enter grid position by 'O' user
        if(errorFlag)		// Exit game if the entered grid position is a invalid integer
        {   
            printf("Invalid entry Game exit");
            break;
        }
        else
        {
            printGameBoard();	//To print game board after each turn 
            if(moves > 2)
            {
                check = checkWinner();
                if(check == 1)
                {
                    printf("Hooray!! %s is the winner\n",nameX);
                    break;
                }    
                else if(check == 2)
                {
                    printf("Hooray!! %s is the winner\n",nameO);
                    break;
                }
                else if((check == 0) && (moves == 7))
                    printf("Game is a Tie\n");
            }
        } 
    }
    
    return 0;
}

void creatGameBoard()
{
    for(int i = 0;i < 4; i++)
    {
        for(int j =0;j < 5;j++)
        {
            board1[i][j] = '|';
        
            if((i!=4) && (j!=4))
                board2[i][j] = '_';
        }
    }
}

void printGameBoard()
{
    for(int i = 0;i < 4; i++)
    {
        for(int j =0;j < 5;j++)
        {
            printf("%c",board1[i][j]);
        
            if((i!=4) && (j!=4))
                printf("%c",board2[i][j]);
        }
        printf("\n");
    }
}

void enterUserNames()
{
    printf("TIC TAC TOE GAME BOARD \n");
    printf("'x' user please enter your name ");
    scanf("%s",nameX);
    printf("'o' user please enter your name ");
    scanf("%s",nameO);
    //printf("Users please enter grid position less than or equal to 16\n");
}

void printBoardWithGridPos()
{
    printf("\nUsers please enter grid position between 1 - 16\n");
    printf("Grid positions are as below\n\n");
    for(int i = 0;i < 4; i++)
    {
        for(int j =0;j < 5;j++)
        {
            printf("%c",board1[i][j]);
        
            if((i!=4) && (j!=4))
                if(i<2)
                    printf("%d",  ((4*i)+(j+1)));
                else
                    printf("%d",  ((4*i)+(j+1)));
        }
    printf("\n");
    }
    printf("\n");
}

void enterGridPosX()
{
    printf("%s please enter grid position ", nameX);
    //scanf("%d",&gPos);
    if(scanf("%d%c", &gPos, &term) != 2 || term != '\n')
        errorFlag = 1;
    else
        enterElement('X');
}

void enterGridPosO()
{
    printf("%s please enter grid position ",nameO);
    //scanf("%d",&gPos);
    if(scanf("%d%c", &gPos, &term) != 2 || term != '\n')
        errorFlag = 1;    
    else
        enterElement('O');
}

void enterElement(char ch)
{   
    int flag = 0; ////To break nested loop
    
    if(gPos > 16) // When grid position is greater than 16
    {
        printf("Grid position is greater than 16 , enter new grid position \n");
        if(ch == 'X')
            enterGridPosX();
        else if(ch == 'O')
            enterGridPosO(); 
    }
    else if(gPos <= 16) // When grid position is less than 16 : Ideal scenario
    {
        if((gPos % 4) != 0)
        {
            row = gPos/4;
            column = (gPos%4)-1;
        }
        else
        {
            row = (gPos/4) - 1;
            column = (gPos%4) +3;
        }
    
        for (int i = 0;i < 4;i++)
        {
            for(int j = 0; j < 5; j++)
            {
                if((i == row) && (j == column))
                {
                    if(board2[i][j] == '_')
                    {
                        board2[i][j] = ch;
                    }    
                    else if ((board2[i][j] == 'X') || (board2[i][j] == 'O'))
                    {
                        printf("Element already present in this position, enter new grid position\n");
                        if(ch == 'X')
                        {
                            enterGridPosX();
                            flag = 1;
                            break;
                        }
                        else if(ch == 'O')
                        {
                             enterGridPosO();
                             flag = 1;
                             break;
                        }
                    }
                }
            }
            if(flag == 1)  
                break;
        }  
    }
}

char checkHortVert()
{
    int countXH = 0;
    int countXV = 0;
    int countOH = 0;
    int countOV = 0;
  
    for(int i = 0;i < 4; i++)
    {
        for(int j =0;j < 4; j++)
        {   
            if(board2[i][j] == 'X')
                countXH++;    
        
            if(board2[j][i] == 'X') 
                countXV++;
        
            if(board2[i][j] == 'O')
                countOH++;
        
            if(board2[j][i] == 'O') 
                countOV++;
        }
        if((countXH == 4) || (countXV == 4))          
			return 'X';
        
        else if((countOH == 4) || (countOV == 4))
			return 'O';       
                    
        countOH = 0;
        countXH = 0;
        countOV = 0;
        countXV = 0;
    }
    return 0;  
}

char checkDiag()
{
    int countXLR =0;
    int countXRL =0;
    int countORL = 0;
    int countOLR = 0;
    for(int i = 0;i < 4;i++)
    {
        for(int j =0;j < 4;j++)
        {   
            if(i==j)
            {
                if(board2[i][j] == 'X')
                    countXLR++;
                    
                if(board2[i][j] == 'O')
                    countOLR++;
            }
            
            if((i+j) == 3)
            {
                if(board2[i][j] == 'X')
                    countXRL++;
                    
                if(board2[i][j] == 'O')
                    countORL++;
            }
        }
        
        if((countXRL == 4) || (countXLR == 4))
            return 'X';
        
        else if((countORL == 4) || (countOLR == 4))
            return 'O';
    }
    return 0;
}

int checkWinner()
{
    char ch1 = ' ';
    char ch2 = ' ';
    ch1 = checkHortVert();
    ch2 = checkDiag();
    
    if((ch1 != ' ') || (ch2 != ' '))
    {
        if((ch1 == 'X') || (ch2 == 'X'))
            return 1;
        
        else if((ch1 == 'O') || (ch2 == 'O'))
            return 2;
    }
    else 
        return 0;
}

