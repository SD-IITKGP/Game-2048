#include <bits/stdc++.h>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////
///////////// GAME - 2048 ///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

/*
    Parameters and seed values for the random-number generator
*/
const int M = (1 << 16) | 1;
const int A = 75;
const int C = 74;
int Xn = 0;
/*
    Return: returns a random (pseudo-random) number
*/
int generateRandomNumber()
{
    Xn = ((A * Xn) + C) % M;
    return Xn;
}

/*
    Arguments: take in a list of (x, y) coordinates of all the empty cells
    Return: returns a value (80% : 2, 20% : 4) along with a Randomly (Pseudo)
    selected cell out of the empty cells
    pair<int, pair<int, int>> --> <value, <x, y>>
*/

pair<int, pair<int, int>> getRandomEmptyCellAndValue(vector<pair<int, int>> &emptyCells)
{
    int mini = 0, maxi = (int)emptyCells.size() - 1;
    int pos = (generateRandomNumber() % (maxi - mini + 1)) + mini;

    sort(emptyCells.begin(), emptyCells.end());

    mini = 1, maxi = 10;
    int value = (generateRandomNumber() % (maxi - mini + 1)) + mini;

    if (value <= 8)
        return make_pair(2, emptyCells[pos]);

    return make_pair(4, emptyCells[pos]);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////  FUNCTIONS ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
vector<vector<int>> board(4, vector<int>(4,0));
/*
    Print the current configuration of the board
*/
void printBoard()
{
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(board[i][j]==0) cout<<"-"<<"\t";
            else cout<<board[i][j]<<"\t";
        }
        cout<<"\n";
    }
}

/*
    Arguments: takes in the direction of the move {1: left, 2: down, 3: right, 4: up}
    Return: after applying the move to the board, returns if the move was successful
    in changing the board or not
*/
int gravity(vector<int> &arr){
    int flag=0;
    int first_empty=0;
    for(int i=0;i<4;i++){
        if(arr[i]!=0){
            flag=1;
            swap(arr[first_empty],arr[i]);
            first_empty++;
        }
    }
    return flag;
}
void mergeCells(vector<int> &arr){
    for(int i=0;i<3;i++){
        if(arr[i]==arr[i+1]&&arr[i]!=0){
            arr[i]+=arr[i+1];
            arr[i+1]=0;
            }
        }
}
int moveIt(vector<int> &arr){
    int flag=0;
    vector<int> copyArr(arr);
    gravity(arr);
    mergeCells(arr);
    gravity(arr);
    for(int i=0;i<4;i++){
        if(copyArr[i]!=arr[i]) return flag=1;
    }
    return flag;
}
bool move(int direction)
{
    int flag=0;
    vector<int> arr(4);
    if(direction==1){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                arr[j]=board[i][j];
            }
            flag|=moveIt(arr);
            for(int j=0;j<4;j++){
                board[i][j]=arr[j];
            }
        }
    }
    else if (direction==2){
        for(int i=0;i<4;i++){
            for(int j=3;j>=0;j--){
                arr[3-j]=board[j][i];
            }
            flag|=moveIt(arr);
            for(int j=3;j>=0;j--){
                board[j][i]=arr[3-j];
            }
        }
    }
    else if (direction==3){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                arr[3-j]=board[i][j];
            }
            flag|=moveIt(arr);
            for(int j=0;j<4;j++){
                board[i][j]=arr[3-j];
            }
        }
    }
    else{
        for(int i=0;i<4;i++){
            for(int j=3;j>=0;j--){
                arr[j]=board[j][i];
            }
            flag|=moveIt(arr);
            for(int j=3;j>=0;j--){
                board[j][i]=arr[j];
            }
        }
    }
    return  flag;
}

/*
    Randomly selects a cell (using getRandomEmptyCellAndValue() function) and
    assigns a value to it
*/
void populateRandomCell()
{
    vector<pair<int,int>> emptyCells;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(board[i][j]==0) emptyCells.push_back({i,j});
        }
    }
    if(!emptyCells.empty()){
    pair<int,pair<int,int>> filledCells;
    filledCells = getRandomEmptyCellAndValue(emptyCells);
    board[filledCells.second.first][filledCells.second.second]=filledCells.first;
    }
}

/*
    Return: returns the current status of the game
    {
        0: Game Over (You lose / No more possible moves left)
        1: Game Over (You win / Target Achieved)
        2: Game still in progress (Valid moves left)
    }
*/
int checkGameStatus()
{
    int flag=0;
    for(int j=0;j<4;j++){
        for(int i=0;i<4;i++){
            if(board[j][i]==2048){
                flag=1;
                return flag;
            }
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(board[i][j]==0){
                flag=2;
                return flag;
            }
        }
    }
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(i<3&&board[i][j]==board[i+1][j]){
                    flag=2;
                    return flag;
                }
                else if (j<3&&board[i][j]==board[i][j+1]){
                    flag=2;
                    return flag;
                }
            }
        }
    return  flag;
}

/*
    Used to Initialize the Board and other values required by the game
*/
void initialize()
{
    populateRandomCell();
    populateRandomCell();
}

int main()
{
    // Read inputs here and perform actions on the board
    int N;
    cin>>N;
    initialize();
    printBoard();
    while(N--){
        int direction;
        cin>>direction;
        if(move(direction)!=true) {
            cout<<"Invalid Move\n";
            continue;
        }
        populateRandomCell();
        printBoard();
        int status=checkGameStatus();
        if(status==0) {

            cout<<"Game Over, You Lose\n";
            return 0;
        }
        else if (status==1) {
            cout<<"Game Over, You Win\n";
            return 0;
        }
//        cout<<"\n"<<status<<"\n";
    }
    return 0;
}
