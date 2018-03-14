#include <iostream>
#include <vector>
#include <utility>

class TicTacToe {
 public:
  using Location = std::pair<int, int>;
  enum Player { NoPlayer = 0, Player1, Player2 };
  enum Result { NoWin = 0, Win, InvalidMove, End };
  
  TicTacToe();
  ~TicTacToe();

  ///
  /// \brief MakeMove Interface for the game playing system to add a new move to
  /// the game.
  /// \param player   Player making this move.
  /// \param location The selected location. X=first, Y=second
  /// \return Result of the move. Win if the move wins the game, Invalid move if
  /// input has errors, NoWin otherwise.
  ///
  Result MakeMove(Player player, Location location);
  Location SuggestNextMove(Player player);

  void ResetGame();

 private:
  std::vector< std::vector<int> > board;
  std::vector<int> row[2], col[2];
  int diag1[2], diag2[2];
  int boardSize, cnt;
};


TicTacToe::TicTacToe() {
  // Add any initializations for the data structures.
  boardSize = 3;
  ResetGame();
}

TicTacToe::~TicTacToe() {
  // Add any clean-up or deallocations needed.
  for(int i=0;i<boardSize;++i)
    board[i].clear();
  board.clear();
  for(int i=0;i<2;++i){
    row[i].clear();
    col[i].clear();
  }
}

TicTacToe::Result TicTacToe::MakeMove(Player player, Location location) {
  // Validate parameters, update game state and check for win condition.
  
  // valid location
  if(location.first < 0  || location.first >= boardSize ||
     location.second < 0 || location.second >= boardSize) return InvalidMove;
  // player can access the location
  if(board[location.first][location.second] != NoPlayer)  return InvalidMove;
  // valid player
  if(player != TicTacToe::Player1 && player != TicTacToe::Player2) return InvalidMove;
  
  // update the board
  board[location.first][location.second] = player;
  --cnt;
  
  ++row[player-1][location.first];
  ++col[player-1][location.second];
  if(location.first == location.second){
    ++diag1[player-1];
  }
  if(boardSize-location.first-1 == location.second){
    ++diag2[player-1];
  }

  // cehck the win condition  
  if(row[player-1][location.first] == boardSize || 
     col[player-1][location.second] == boardSize ||
     diag1[player-1] == boardSize ||
     diag2[player-1] == boardSize) return Win;
     
  if(cnt == 0) return End;
  return NoWin;
}

TicTacToe::Location TicTacToe::SuggestNextMove(Player player){
}

void TicTacToe::ResetGame() {
  // Clear the game state for a new game.
  board = std::vector< std::vector<int> >(boardSize, std::vector<int>(boardSize, 0));
  for(int i=0;i<2;++i){
    row[i] = std::vector<int>(boardSize, 0);
    col[i] = std::vector<int>(boardSize, 0);
    diag1[i] = diag2[i] = 0;
  }
  cnt = 0;
}

TicTacToe game;

int main(int argc, char** argv) {
  std::cout << "Starting test!" << std::endl;
  game.ResetGame();
  const TicTacToe::Player player1 = TicTacToe::Player1;
  const TicTacToe::Player player2 = TicTacToe::Player2;

//   if (game.MakeMove(player1, TicTacToe::Location(1, 2)) != TicTacToe::NoWin) {
//     std::cout << "Test failed!" << std::endl;
//   }
//   if (game.MakeMove(player2, TicTacToe::Location(0, 1)) != TicTacToe::NoWin) {
//     std::cout << "Test failed!" << std::endl;
//   }

  // Add some useful test cases.
  std::cout << "First Round" << std::endl; // player 1 win
  std::cout << "Result: " << game.MakeMove(player1, TicTacToe::Location(1, 1)) << std::endl;
  std::cout << "Result: " << game.MakeMove(player2, TicTacToe::Location(1, 0)) << std::endl;
  std::cout << "Result: " << game.MakeMove(player1, TicTacToe::Location(0, 1)) << std::endl;
  std::cout << "Result: " << game.MakeMove(player2, TicTacToe::Location(2, 1)) << std::endl;
  std::cout << "Result: " << game.MakeMove(player1, TicTacToe::Location(0, 2)) << std::endl;
  std::cout << "Result: " << game.MakeMove(player2, TicTacToe::Location(2, 0)) << std::endl;
  std::cout << "Result: " << game.MakeMove(player1, TicTacToe::Location(0, 0)) << std::endl;
  game.ResetGame();
  
  std::cout << "Second Round" << std::endl; // no one win
  std::cout << "Result: " << game.MakeMove(player1, TicTacToe::Location(1, 1)) << std::endl;
  std::cout << "Result: " << game.MakeMove(player2, TicTacToe::Location(2, 0)) << std::endl;
  std::cout << "Result: " << game.MakeMove(player1, TicTacToe::Location(1, 2)) << std::endl;
  std::cout << "Result: " << game.MakeMove(player2, TicTacToe::Location(1, 0)) << std::endl;
  std::cout << "Result: " << game.MakeMove(player1, TicTacToe::Location(0, 0)) << std::endl;
  std::cout << "Result: " << game.MakeMove(player2, TicTacToe::Location(2, 2)) << std::endl;
  std::cout << "Result: " << game.MakeMove(player1, TicTacToe::Location(2, 1)) << std::endl;
  std::cout << "Result: " << game.MakeMove(player2, TicTacToe::Location(0, 1)) << std::endl;
  std::cout << "Result: " << game.MakeMove(player1, TicTacToe::Location(0, 2)) << std::endl;
  game.ResetGame();
  
  // make a 4 x 4 test case to test the scalability.
  
  return 0;
}