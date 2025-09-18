#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int difficulty;
int x_score, computer_score, draws = 0;
//x -> 1, o -> 2
int board[3][3] = {
    {0,0,0},
    {0,0,0},
    {0,0,0}
};

void input_difficulty();
void print_board(int board[3][3]);
void score_board();
int game_state(int board[3][3]);
void user_turn();
void computer_turn();
void computer_turn_hard_mode();
void clear_screen();
void run_game();

int play_again;

int state;
int current_turn;

int main() {
    srand(time(NULL));
    int run=1;
    do
    {
        run_game();
    } while (play_again);
    

    return 0;
}

void run_game() {
    state = 0;
    current_turn = 1+rand()%2;

    input_difficulty();
    clear_screen();
    score_board();
    print_board(board);

    do
    {
        if(current_turn==1){
            if(!state){
                user_turn();
                current_turn = 2;
            }
        }
        else{
            if(!state){
                if(difficulty==1){
                    computer_turn();
                }
                else{
                    computer_turn_hard_mode();
                }
                current_turn = 1;
            }
        }
        clear_screen();
        score_board();
        print_board(board);

        state = game_state(board);

    } while (!state);

    if(state==1){
        printf("\nPlayer X wins!!");
        x_score += 1;
    }
    else if (state==-1)
    {
        printf("\nIt's a Draw!");
        draws += 1;
    }
    else if (state==2)
    {
        printf("\nComputer wins!!");
        computer_score += 1;
    }

    printf("\nPlay again(1 for y 0 for n): ");
    scanf("%d", &play_again);
    if (play_again) {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = 0;
            }
            
        }
        
    }
}

void input_difficulty() {
    printf("\nSelect difficulty level: ");
    printf("\n1. Easy");
    printf("\n2. Difficult");
    printf("\n Enter your choice: ");
    scanf("%d", &difficulty);

    if (difficulty != 1 && difficulty != 2) {
        printf("\nIncorrect choice!");
        input_difficulty();
    }
}

void print_board(int board[3][3]) {
    printf("\n");
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++) {
            if (!board[r][c]) {
                printf("   ");
            }
            else if (board[r][c]==1)
            {
                printf(" X ");
            }else{printf(" O ");}
            if (c != 2) {
                printf("|");
            }
        }
        if (r != 2) {
            printf("\n---+---+---\n");
        }
    }
    printf("\n");
}

void score_board() {
    printf("Score - Player X: %d, Computer: %d, Draws: %d\n", x_score, computer_score, draws);
    printf("Tic Tac Toe\n");
}

int game_state(int board[3][3]) {

    for (int i = 0; i < 3; i++)
    {
        if (board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][2] != 0) {
        return board[i][0];
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[2][i] != 0) {
        return board[0][i];
        }
    }
    if ((board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[1][1] != 0) || (board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[1][1] != 0)) {
        return board[1][1];
    }
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (!board[i][j]) {
                return 0;
            }
        }
        
    }
    return -1; // Draw
}

void user_turn() {
    int input_row, input_col;

    do
    {
        printf("Enter your move(format: rowNo. colNo.): ");
        scanf("%d %d", &input_row, &input_col);
        input_row -= 1;
        input_col -= 1;
    } while (board[input_row][input_col]);

    board[input_row][input_col] = 1;
}

void computer_turn() {
    printf("\n Its easy mode\n");
    int random_r, random_c;
    do
    {
        random_r = rand() % 3;
        random_c = rand() % 3;
    }while(board[random_r][random_c]);

    // printf("\n%d %d\n", random_r, random_c);  //debu
    board[random_r][random_c] = 2;
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int turn = 2;
int store_wins[3][3] = {
        {0,0,0},
        {0,0,0},
        {0,0,0}
    };
int store_depth[3][3] = { // to make the 
        {9,9,9},
        {9,9,9},
        {9,9,9}
    };

void calculate_all_poss(int board_copy[3][3], int turn, int depth, int move_r, int move_c) {
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board_copy[i][j]) {
                continue;
            }
            board_copy[i][j] = turn;
            int current_game_state = game_state(board_copy);
            int next_turn = 3- turn;
            if (current_game_state==2){
                store_wins[move_r][move_c] += 10;
                if (store_depth[move_r][move_c] > depth) {
                    store_depth[move_r][move_c] = depth;
                }
            }
            else if (current_game_state==1)
            {
                store_wins[move_r][move_c] -= 10;
                if (store_depth[move_r][move_c] > depth) {
                    store_depth[move_r][move_c] = depth;
                }
            }
            else if (current_game_state==-1)
            {
                store_wins[move_r][move_c] += 0;
            }
            else{
                calculate_all_poss(board_copy, next_turn, depth+1, move_r, move_c);
            }
            board_copy[i][j] = 0; 
            
        }  

    }
    
    return;
    
}

void computer_turn_hard_mode() {
    // 1. Calculate all poss moves
    // 2. take the move with minimum lose or max wins
    // 3. take the move where fast win
    //

    turn = 2;
    int max_wins = -1000;
    int min_depth = 9;
    int best_count = 0;
    int best_win_count = 0;
    int min_depth_in_arr = 9;
    int r; int c;

    int poss_moves[9][2];
    for (int i = 0; i < 9; i++)    // making the poss_moves
    {
        for (int j = 0; j < 2; j++)
        {
            poss_moves[i][j] = -1;
        }
        
    }

    int max_win_pos[9][2];      // making the max_win_positions it stores all the pos with same no. of wins
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            max_win_pos[i][j] = -1;
        }
        
    }
    
    

    for (int i = 0; i < 3; i++)          // making store_wins
    {
        for (int j = 0; j < 3; j++)
        {
            store_wins[i][j] = 0;
        }
        
    }

    for (int i = 0; i < 3; i++)          // making store_depth
    {
        for (int j = 0; j < 3; j++)
        {
            store_depth[i][j] = 9;
        }
        
    }
    

    int board_copy[3][3];              // making the board_copy

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board_copy[i][j] = board[i][j];
        }
        
    }
     

    for (int r = 0; r < 3; r++)               
    {
        for (int c = 0; c < 3; c++)
        {
            if (board_copy[r][c]) {
                continue;
            }
            board_copy[r][c] = 2;

            calculate_all_poss(board_copy, turn, 0, r, c);



            board_copy[r][c] = 0;
        }
        
    }
    
    

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            if(store_wins[i][j] > max_wins) {
                max_wins = store_wins[i][j];
                min_depth = store_depth[i][j];
            }
            else if (store_wins[i][j] == max_wins)
            {
                if (store_depth[i][j] < min_depth){
                    min_depth = store_depth[i][j];
                }
            }
            
        }
        
    }
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(store_wins[i][j] == max_wins) {  // store_depth[i][j] == min_depth
                max_win_pos[best_win_count][0] = i;
                max_win_pos[best_win_count][1] = j;
                best_win_count++;

                // poss_moves[best_count][0] = i;
                // poss_moves[best_count][1] = j;
                // best_count++;
            }
        }
        
    }

    for (int i = 0; i < best_win_count; i++)
    {
        r = max_win_pos[i][0];
        c = max_win_pos[i][1];
        if (store_depth[r][c] < min_depth_in_arr) {
            min_depth_in_arr = store_depth[r][c];
        }
    }
    
    for (int i = 0; i < best_win_count; i++)
    {
        r = max_win_pos[i][0];
        c = max_win_pos[i][1];
        if (store_depth[r][c] == min_depth_in_arr) {
            poss_moves[best_count][0] = r;
            poss_moves[best_count][1] = c;
            best_count++;
        }
        
    }
    
    
    
    if (best_count > 0) {
        int choice = rand() % best_count;
        int r = poss_moves[choice][0];
        int c = poss_moves[choice][1];
        board[r][c] = 2;
    }
    

}
}
