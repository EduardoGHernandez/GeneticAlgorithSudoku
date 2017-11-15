#include <iostream>
#include "GA.hpp"

using namespace std;

int main(){
  int iter = 0;
  bool flag=true;
  Sudoku game;
  game.BeginSudoku();
  game.ShowSudoku();
  GA solution(100,game.MissingBoxes(),5,1,9);
  solution.InitializeDemos();
  solution.EvaluateDemos(&game);
  solution.ShowBestInd(&game);
  do{
    cout << iter << " " << solution.GetBestFitness() << endl;
    solution.Selection();
    //solution.ShowProgenitors();
    solution.Crossover(&game);
    solution.Mutation(&game);
    //solution.ShowBestInd(&game);
    iter++;
    if(solution.GetBestFitness()==243) flag=false;
  }while (flag);
  solution.ShowBestInd(&game);
  return 0;
}
