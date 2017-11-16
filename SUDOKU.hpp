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
    int missingBoxes;
    unsigned int *solution;
  public:
    bool flag;
    void CopySolution();
    int MissingBoxes();
    int CheckIssues();
    int CheckCols();
    int CheckRows();
    int CheckBoxes();
    void CleanRows();
    void CleanCols();
    void CleanBoxes();
    void CleanIssues();
    void BeginSudoku();
    void ShowSudoku();
    void ShowBestSudoku(unsigned int *solution);
    void ModifySudoku();
    int ActualMissingBoxes();
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
void Sudoku::ModifySudoku(){
  for(int i=0; i<9; i++)
    for(int j=0; j<9; j++)
      sgrid[i][j] = grid[i][j];
}
int Sudoku::SolutionFitness(unsigned int *solution){
  int count = 0;
  int qualify;
  CopySolution();
  for(int i=0; i<9; i++)
    for(int j=0; j<9; j++)
      if(grid[i][j]==0){
        grid[i][j] = solution[count];
        count++;
      }
  qualify=CheckBoxes()+CheckRows()+CheckCols();
  return qualify;
}
void Sudoku::CopySolution(){
  for(int i=0; i<9; i++)
    for(int j=0; j<9; j++)
      grid[i][j] = sgrid[i][j];
}
int Sudoku::ActualMissingBoxes(){
  int count=0;
  for(int i=0; i<9; i++)
    for(int j=0; j<9; j++)
      if(grid[i][j]==0) count++;
  return count;
}
int Sudoku::MissingBoxes(){
  int count=0;
  for(int i=0; i<9; i++)
    for(int j=0; j<9; j++)
      if(sgrid[i][j]==0) count++;
  return count;
}
int Sudoku::CheckCols(){
  int dictionary[10];
  int qualify = 0;
  for(int i=0; i<9; i++){
    for(int a=0; a<10; a++)
      dictionary[a]=0;
    for(int j=0; j<9; j++){
      dictionary[grid[j][i]]++;
    }
    for(int a=1; a<10; a++)
      if(dictionary[a]>1){
          qualify+=dictionary[a]-1;
      }
  }
  //cout <<"Check Cols: " << qualify << endl;
  return qualify;
}
int Sudoku::CheckRows(){
  int dictionary[10];
  int qualify = 0;
  for(int i=0; i<9; i++){
    for(int a=0; a<10; a++)
      dictionary[a]=0;
    for(int j=0; j<9; j++){
      dictionary[grid[i][j]]++;
    }
    for(int a=1; a<10; a++)
      if(dictionary[a]>1){
          qualify+=dictionary[a]-1;
      }
  }
  //cout <<"Check Rows: " << qualify << endl;
  return qualify;
}
int Sudoku::CheckBoxes(){
  int dictionary[10];
  int qualify = 0;
  for(int i=0; i<9; i+=3){
    for(int j=0;j<9; j+=3){
      //dictionary
      for(int a=0; a<10; a++)
        dictionary[a]=0;
      //Check box
      for(int m=i; m<i+3; m++)
        for(int n=j; n<j+3;n++)
          dictionary[grid[m][n]]++;
      for(int a=1; a<10; a++)
        if(dictionary[a]>1){
            qualify+=dictionary[a]-1;
        }
    }
  }
  //cout <<"Check Boxes: " << qualify << endl;
  return qualify;
}
void Sudoku::ShowSudoku(){
  cout << "Sudoku: " << endl;
  for(int i=0; i<9;i++){
    for(int j=0; j<9; j++){
      if(!(j%3)) cout << "\t";
      cout << sgrid[i][j] << " ";
    }
    cout << endl;
    if(!((i+1)%3)){
      cout << endl;
    }
  }
  cout << "Solution: " << endl;
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
int Sudoku::CheckIssues(){
  int dictionary[10];
  int qualify = 0;
  for(int i=0; i<9; i++){
    for(int j=0;j<9; j++){
      for(int a=0; a<10; a++)
        dictionary[a]=0;
      for(int k=0; k<9; k++){
          dictionary[grid[i][k]]++;
          dictionary[grid[k][j]]++;
      }
      for(int a=1; a<10; a++)
        qualify += dictionary[a]-1;
    }
  }
  return qualify;
}
void Sudoku::CleanIssues(){
  int dictionary[10];
  for(int i=0; i<9; i++){
    for(int a=0; a<10; a++)
      dictionary[a]=0;
    for(int j=0;j<9; j++){
      if(grid[i][j]==0)
      for(int k=0; k<9; k++){
          dictionary[grid[j][k]]++;
          dictionary[grid[k][j]]++;
      }
      if(dictionary[grid[i][j]]>1) grid[i][j] = 0;
    }
  }
}
void Sudoku::BeginSudoku(){
  int box[81]={5,2,4,0,6,0,1,9,3,8,0,0,0,1,5,0,0,7,7,0,1,3,9,2,5,0,4,9,0,0,8,3,7,0,0,6,6,3,0,2,4,9,0,1,5,2,0,
    0,1,5,6,0,0,8,3,0,2,9,7,4,8,0,1,1,0,0,6,8,0,0,0,2,4,8,6,0,2,0,3,7,9};
  int count = 0;
  for(int i=0; i<9; i++)
    for(int j=0; j<9; j++){
      grid[i][j] = box[count];
      count++;
    }
  for(int i=0; i<9; i++)
    for(int j=0; j<9; j++)
      sgrid[i][j] = grid[i][j];
  missingBoxes = MissingBoxes();
  if(missingBoxes>60)
    BeginSudoku();
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
  flag = true;
  grid = new unsigned int*[9];
  sgrid = new unsigned int*[9];
  for(int i=0; i<9; i++){
    grid[i] = new unsigned int[9];
    sgrid[i] = new unsigned int[9];
  }
}
