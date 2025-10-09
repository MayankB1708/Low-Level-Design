#include<bits/stdc++.h>
using namespace std;

enum class Symbol{
    X, O, EMPTY
};

class Position{
    public:
    int row=0,col=0;
    Position(int r=0, int c=0) : row(r), col(c) {}
};

class Board; 

class PlayerStrategy{
    public:
    virtual Position makeMove(Board &board)=0;
    virtual ~PlayerStrategy() {}
};

class Player{
    Symbol symbol;
    PlayerStrategy* strategy;

    public:
    Player(Symbol smb, PlayerStrategy* ps) : strategy(ps), symbol(smb) {}
    Symbol getSymbol(){
        return symbol;
    }
    PlayerStrategy* getPlayerStrategy(){
        return strategy;
    }
};

class Board{
    int rows,cols;
    vector<vector<Symbol>> grid;

    public:
    Board(int r=3, int c=3) : rows(r), cols(c), grid(r,vector<Symbol>(c, Symbol::EMPTY)) {}
    
    bool isValidMove(const Position& pos, Symbol smb){
        return pos.row>=0 && pos.row<rows &&
               pos.col>=0 && pos.col<cols &&
               grid[pos.row][pos.col]==Symbol::EMPTY;
    }
    void makeMove(const Position& pos, Symbol smb){
        if(isValidMove(pos,smb)){
            grid[pos.row][pos.col]=smb;
        }
    }
    bool isWinningLine(const Position& pos, Symbol smb){
        //check row
        bool win=true;
        for(int c=0;c<cols;c++){
            if(grid[pos.row][c]!=smb){
                win=false;
                break;
            }
        }
        if(win) return true;

        //check col
        win=true;
        for(int r=0;r<rows;r++){
            if(grid[r][pos.col]!=smb){
                win=false;
                break;
            }
        }
        if(win) return true;

        //check diagonal
        if(pos.row==pos.col){
            win=true;
            for(int i=0;i<rows;i++){
                if(grid[i][i]!=smb){
                    win=false;
                    break;
                }
            }
            if(win) return true;
        }

        //check antidiagonal
        if(pos.row+pos.col==rows-1){
            win=true;
            for(int i=0;i<rows;i++){
                if(grid[i][cols-i-1]!=smb){
                    win=false;
                    break;
                }
            }
            if(win) return true;
        }

        return false;

    }
    Symbol checkWinner() const{
        // Check rows
        for (int r = 0; r < rows; r++) {
            if (grid[r][0] != Symbol::EMPTY) {
                bool win = true;
                for (int c = 1; c < cols; c++)
                    if (grid[r][c] != grid[r][0]) { win = false; break; }
                if (win) return grid[r][0];
            }
        }

        // Check columns
        for (int c = 0; c < cols; c++) {
            if (grid[0][c] != Symbol::EMPTY) {
                bool win = true;
                for (int r = 1; r < rows; r++)
                    if (grid[r][c] != grid[0][c]) { win = false; break; }
                if (win) return grid[0][c];
            }
        }

        // Check main diagonal
        if (grid[0][0] != Symbol::EMPTY) {
            bool win = true;
            for (int i = 1; i < rows; i++)
                if (grid[i][i] != grid[0][0]) { win = false; break; }
            if (win) return grid[0][0];
        }

        // Check anti-diagonal
        if (grid[0][cols - 1] != Symbol::EMPTY) {
            bool win = true;
            for (int i = 1; i < rows; i++)
                if (grid[i][cols - 1 - i] != grid[0][cols - 1]) { win = false; break; }
            if (win) return grid[0][cols - 1];
        }

        return Symbol::EMPTY;
    }
    bool isFull() const{ 
        for (auto &row : grid)
            for (auto &cell : row)
                if (cell == Symbol::EMPTY) return false;
        return true;
    }
    void printBoard() const{
        cout << "\nBoard:\n";
        for (auto &row : grid) {
            for (auto &cell : row) {
                char ch = (cell == Symbol::X ? 'X' : (cell == Symbol::O ? 'O' : '.'));
                cout << ch << " ";
            }
            cout << "\n";
        }
        cout << endl;
    }
};

class HumanStrategy: public PlayerStrategy{
    string playername;
    public:
    HumanStrategy(const string& name) : playername(name) {}

    Position makeMove(Board& board) override{
        int r,c;
        while(true){
            cout<<playername<<" Enter row and column(0 based): ";
            cin>>r>>c;
            Position pos(r,c);
            if(board.isValidMove(pos,Symbol::X) || board.isValidMove(pos,Symbol::O)) return pos;
            else cout<<"Invalid Move....Try again"<<endl;
        }
    }
};

class BoardGames{
    public:
    virtual void play()=0;
    virtual ~BoardGames() {}
};

class TicTacToeGame: public BoardGames{
    Board board;
    Player px;
    Player po;
    Player* cp;

    public:
    TicTacToeGame(PlayerStrategy* psx, PlayerStrategy* pso, int rows, int cols): board(rows,cols), px(Symbol::X,psx), po(Symbol::O,pso), cp(&px) {}

    void play() override{
        while(!board.isFull() && board.checkWinner()==Symbol::EMPTY){
            board.printBoard();

            Position move=cp->getPlayerStrategy()->makeMove(board);
            board.makeMove(move,cp->getSymbol());

            if(board.checkWinner()!= Symbol::EMPTY) break;

            //switch player
            cp=(cp==&px) ? &po : &px;
        }
        board.printBoard();
        Symbol winner=board.checkWinner();
        if(winner!=Symbol::EMPTY){
            cout<<"Winner is "<<(winner==Symbol::X ? "X!" : "O!")<<endl;
        }
        else cout<<"Its a DRAW!"<<endl;
    }
};

int main(){
    PlayerStrategy* xst=new HumanStrategy("PlayerX");
    PlayerStrategy* ost=new HumanStrategy("PlayerO");

    TicTacToeGame game(xst,ost,3,3);
    game.play();

    delete xst;
    delete ost;
    return 0;
}
