#include <iostream>
#include "GA.hpp"

using namespace std;

int main(){
  int iter = 0;
  int missingBoxes;
  Sudoku game;
  game.BeginSudoku();
  game.ShowSudoku();
  missingBoxes = game.MissingBoxes();
  GA *solution;
  solution = new GA(100,missingBoxes,6,1,9);
  solution->InitializeDemos();
  solution->EvaluateDemos(&game);
  //solution->ShowBestInd(&game);
  do{
    cout << iter << " " << solution->GetBestFitness() << endl;
    solution->SelectionPerTournament();
    solution->Crossover2p(&game);
    solution->Mutation(&game);
    iter++;
  }while (solution->GetBestFitness()>=32);
  solution->ShowDemos();
  solution->ShowBestInd(&game);
  return 0;
}
