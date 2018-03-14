# TicTacToe

This porject aims to play TicTacToe efficiently. Every placement and winning condition check can be done in constant time. In addition, the board is scalable. One interesting feature is implemented called "suggestNextMove". It will give the player best choice for the next move. The amortized complexity of this feature is O(N).

## Idea

To realize the constant check of the winning condition, for each player, we maintain one row vector, one column vector, and two variables, "45 degree diagonal" and "135 degree diagonal" for counting. Suppose the player placed a valid move at (r, c). Here, we called it is valid after doing the boundary test and checking that the place has not be occupied by a player before. Then, we will increment row[player][r], col[player][c], and diag45/diag135 if r is equal to c or r is equal to N-1-c. After the increment, if one of the variables reached N, then the player wins the game.

## Algorithm of "suggestNextMove"

The feature needs to achieve two functionality. 
  
  1. Choose the most possible winning position. 
      This is realized by using opponent's move to remove impossible winning positions. Suppose there is a move placed at (r, c) by the         opponent. It's not going to win for the current player to place at (r, x) or (x, c) where x is from 0 to N-1. Then, we use current         player's counting variables as a reward to find the maximum reward.
      
  2. Block the opponent if the opponent is going to win.
      We utilize the opponent's counting variable to do this check. If row[opponent] is N-1 or col[opponent] is N-1, then we will set the       reward as N*N. This way, this placement has the maximum reward. Here is a question why do we not checking diagonal's counting             result. It is because when removing impossible row and column, the left position will cover the diagonal in the previous step.
      
If after going through step 1 and 2, we cannot find a good placement, we will maintain a "playerNextMove" storage for returning a valid next move.
