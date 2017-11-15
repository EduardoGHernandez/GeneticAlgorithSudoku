#include <iostream>
#include <cstdlib>

using namespace std;
class Sudoku{
  private:
    unsigned int **grid; //9x9
    unsigned int **sgrid; //9x9
    int max; //max value 9
    int min; //min value 1
    int level; // 1: Easy 2:Medium 3:Hard
    int fitness;
    unsigned int *solution;
  public:
    void CopySolution();
    int MissingBoxes();
    int CheckCols();
    int CheckRows();
    int CheckBoxes();
    void CleanRows();
    void CleanCols();
    void CleanBoxes();
    void BeginSudoku();
    void ShowSudoku();
    void ShowBestSudoku(unsigned int *solution);
    int SolutionFitness(unsigned int *solution);
    Sudoku();
    ~Sudoku();
};
void Sudoku::ShowBestSudoku(unsigned int *solution){
  int count = 0;
  CopySolution();
  for(int i=0; i<9; i++)
    for(int j=0; j<9; j++)
      if(grid[i][j]==0){
        grid[i][j] = solution[count];
        count++;
      }
  ShowSudoku();
}
int Sudoku::SolutionFitness(unsigned int *solution){
  int count = 0;
  CopySolution();
  for(int i=0; i<9; i++)
    for(int j=0; j<9; j++)
      if(grid[i][j]==0){
        grid[i][j] = solution[count];
        count++;
      }
  return CheckBoxes()+CheckRows()+CheckCols();
}
void Sudoku::CopySolution(){
  for(int i=0; i<9; i++)
    for(int j=0; j<9; j++)
      grid[i][j] = sgrid[i][j];
}
int Sudoku::MissingBoxes(){
  int count=0;
  for(int i=0; i<9; i++)
    for(int j=0; j<9; j++)
      if(grid[i][j]==0) count++;
  return count;
}
int Sudoku::CheckCols(){
  int dictionary[10];
  int qualify = 81;
  for(int i=0; i<9; i++){
    for(int a=0; a<10; a++)
      dictionary[a]=0;
    for(int j=0; j<9; j++){
      dictionary[grid[j][i]]++;
    }
    for(int a=1; a<10; a++)
      if(dictionary[a]>1){
          qualify--;
      }
  }
  //cout <<"Check Cols: " << qualify << endl;
  return qualify;
}
int Sudoku::CheckRows(){
  int dictionary[10];
  int qualify = 81;
  for(int i=0; i<9; i++){
    for(int a=0; a<10; a++)
      dictionary[a]=0;
    for(int j=0; j<9; j++){
      dictionary[grid[i][j]]++;
    }
    for(int a=1; a<10; a++)
      if(dictionary[a]>1){
          qualify--;
      }
  }
  //cout <<"Check Rows: " << qualify << endl;
  return qualify;
}
int Sudoku::CheckBoxes(){
  int dictionary[10];
  int qualify = 81;
  for(int i=0; i<9; i+=3){
    for(int j=0;j<9; j+=3){
      //dictionary
      for(int a=0; a<10; a++)
        dictionary[a]=0;
      //Check box
      for(int m=i; m<i+3; m++)
        for(int n=j; n<j+3;n++)
          dictionary[grid[m][n]]+=1;
      for(int a=1; a<10; a++)
        if(dictionary[a]>1){
            qualify--;
        }
    }
  }
  //cout <<"Check Boxes: " << qualify << endl;
  return qualify;
}
void Sudoku::ShowSudoku(){
  for(int i=0; i<9;i++){
    for(int j=0; j<9; j++){
      if(!(j%3)) cout << "\t";
      cout << grid[i][j] << " ";
    }
    cout << endl;
    if(!((i+1)%3)){
      cout << endl;
    }
  }
}
void Sudoku::CleanBoxes(){
  int dictionary[10];
  for(int i=0; i<9; i+=3)
    for(int j=0;j<9; j+=3){
      //dictionary
      for(int a=0; a<10; a++)
        dictionary[a]=0;
      //Check box
      for(int m=i; m<i+3; m++)
        for(int n=j; n<j+3;n++){
          dictionary[grid[m][n]]++;
          if(dictionary[grid[m][n]]>1) grid[m][n] = 0;
        }
    }
}
void Sudoku::CleanRows(){
  int dictionary[10];
  for(int i=0; i<9; i++){
    for(int a=0; a<10; a++)
      dictionary[a]=0;
    for(int j=0;j<9; j++){
      dictionary[grid[i][j]]++;
      if(dictionary[grid[i][j]]>1) grid[i][j] = 0;
    }
  }
}
void Sudoku::CleanCols(){
  int dictionary[10];
  for(int i=0; i<9; i++){
    for(int a=0; a<10; a++)
      dictionary[a]=0;
    for(int j=0;j<9; j++){
      dictionary[grid[j][i]]++;
      if(dictionary[grid[j][i]]>1) grid[j][i] = 0;
    }
  }
}
void Sudoku::BeginSudoku(){
  for(int i=0; i<9; i++)
    for(int j=0; j<9; j++){
      if(rand()%100<70) grid[i][j] = (rand()%max)+min;
      else grid[i][j]=0;
    }
  CleanBoxes();
  CleanRows();
  CleanCols();
  for(int i=0; i<9; i++)
    for(int j=0; j<9; j++)
      sgrid[i][j] = grid[i][j];
}
Sudoku::~Sudoku(){
  for(int i=0; i<9; i++){
    delete[] grid[i];
    delete[] sgrid[i];
  }
  delete[] grid;
  delete[] sgrid;
}
Sudoku::Sudoku(){
  max = 9;
  min = 1;
  grid = new unsigned int*[9];
  sgrid = new unsigned int*[9];
  for(int i=0; i<9; i++){
    grid[i] = new unsigned int[9];
    sgrid[i] = new unsigned int[9];
  }
}
