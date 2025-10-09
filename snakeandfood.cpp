#include<bits/stdc++.h>
using namespace std;

class Position{
    public:
    int row;
    int col;
    Position(int r=0, int c=0): row(r), col(c) {}
    bool operator==(const Position &other) const{
        return row==other.row && col==other.col;
    }
    bool operator<(const Position &other) const {
        return (row < other.row) || (row == other.row && col < other.col);
    }
};

class GameBoard{
    int width;
    int height;

    public:
    GameBoard(int w=10, int h=10): width(w), height(h) {}
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

class MovementStrategy{
    public:
    virtual Position getNextPosition(Position currentHead, string direction) = 0;
    virtual ~MovementStrategy() {}
};

class HumanStrategy: public MovementStrategy{
    public:
    Position getNextPosition(Position currentHead, string direction) override{
        int row=currentHead.row;
        int col=currentHead.col;
        if(direction=="U") return Position(row-1,col);
        else if(direction=="D") return Position(row+1,col);
        else if(direction=="L") return Position(row,col-1);
        else if(direction=="R") return Position(row,col+1);

        return currentHead;
    }
};

/* NOT NECESSARY*/

// class FoodItem {
//     public:
//     int row, column, points;

//     public:
//     FoodItem(int r, int c, int p) : row(r), column(c), points(p) {}
//     virtual ~FoodItem() {}

//     int getRow() const { return row; }
//     int getColumn() const { return column; }
//     int getPoints() const { return points; }
// };

// class NormalFood : public FoodItem {
//     public:
//     NormalFood(int r, int c) : FoodItem(r, c, 1) {}
// };

// class BonusFood : public FoodItem {
//     public:
//     BonusFood(int r, int c) : FoodItem(r, c, 3) {}
// };

// class FoodFactory{
//     public:
//     static FoodItem* createFood(vector<int> pos, string type){
//         if(type=="bonus") return new BonusFood(pos[0],pos[1]);
//         return new NormalFood(pos[0],pos[1]);
//     }
// };

class SnakeGame{
    GameBoard board;
    deque<Position> snake;
    map<Position, bool> snakeMap;
    vector<vector<int>> food;
    int foodIndex;
    MovementStrategy* ms;

    public:
    SnakeGame(int width, int height, vector<vector<int>> foodPositions)
    : board(width,height), food(foodPositions), foodIndex(0){
        Position initialPos(0,0);
        snake.push_front(initialPos);
        snakeMap[initialPos]=true;
        ms=new HumanStrategy();
    }
    ~SnakeGame() {
        if(ms) delete ms;
    }

    void setMovementStrategy(MovementStrategy* strategy){
        if(ms) delete ms;
        ms=strategy;
    }

    int move(string direction){
        Position currentHead=snake.front();
        Position newHead=ms->getNextPosition(currentHead,direction);

        int nr=newHead.row;
        int nc=newHead.col;

        bool crossBoundary = nr<0 || nr>=board.getHeight() || nc<0 || nc>=board.getWidth();

        Position currentTail=snake.back();
        bool bitesItself= snakeMap.count(newHead) && !(newHead==currentTail);
        if(crossBoundary || bitesItself) return -1;

        bool ateFood= (foodIndex < (int)food.size()) && (food[foodIndex][0]==nr) && (food[foodIndex][1]==nc);
        if(ateFood) foodIndex++;
        else{
            snake.pop_back();
            snakeMap.erase(currentTail);
        }

        snake.push_front(newHead);
        snakeMap[newHead]=true;
        return (int)snake.size()-1; // score;
    }

    int getSnakeLength() const { return (int)snake.size(); }
    int getFoodIndex() const { return foodIndex; }
    deque<Position> getSnake() const { return snake; } 
};

class SnakeGameMain{
    public:
    static string convertInput(string input){
        if (input=="W") return "U";
        if (input=="S") return "D";
        if (input=="A") return "L";
        if (input=="D") return "R";
        return "";
    }
    static void displayGameState(SnakeGame& game){
        cout<<"Current snake length is "<<game.getSnakeLength()<<endl;
    }
    static void run(){
        int width=20, height=15;
        vector<vector<int>> foodPositions={{1,0},{5,5},{10,8},{3,12},{8,17},{12,3}};
        SnakeGame game(width,height,foodPositions);
        cout << "===== SNAKE GAME =====\n";
        cout << "Controls: W (Up), S (Down), A (Left), D (Right), Q (Quit)\n";
        cout << "Eat food to grow your snake and increase your score.\n";
        cout << "Don't hit the walls or bite yourself!\n";
        cout << "=======================\n";

        bool gameRunning=true;
        int score=0;

        while(gameRunning){
            displayGameState(game);
            cout<<"Enter move (W/A/S/D) or Q to quit: ";
            string input;
            cin>>input;

            if(input=="Q"){
                cout<<"Game ended by the player. Final score is "<<score<<endl;
                gameRunning=false;
                continue;
            }

            string direction=convertInput(input);
            if(direction.empty()){
                cout<<"Invalid input! Use (W/A/S/D) to move or Q to quit."<<endl;
                continue;
            }

            score=game.move(direction);
            if (score == -1) {
                cout << "GAME OVER! You hit a wall or bit yourself."<<endl;
                cout << "Final score: " << game.getSnakeLength() - 1 << endl;
                gameRunning = false;
            } 
            else {
                cout << "Score: " << score << endl;
            }
        }
        cout<<"Thanks for playing!"<<endl;
    }
};

int main(){
    SnakeGameMain::run();
    return 0;
}