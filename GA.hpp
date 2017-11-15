#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "SUDOKU.hpp"
using namespace std;
double pow(double a, int b){
  if (b==0) return 1;
  return a*pow(a,b-1);
}
bool randomBool() {
    return 0 + (rand() % (1 - 0 + 1)) == 1;
}
struct INDIVIDUAL{
  bool *chromosome;
  double fitness;
};

class GA{
private:
    int nGenes; //Number of genes
    int geneSize; //Bits per gene
    int demosSize;
    int bestIndID;
    int bestNDIndID;
    double minValue;
    double maxValue;
    double Pm; //Mutation probability
    double Pc; //Crossover probability
    INDIVIDUAL *demos;
    INDIVIDUAL *newDemos;
    int *progenitor;
  public:
    GA(int nIndividuals, int numG, int gSize, int min, int max);
    ~GA();
    void InitializeDemos();//Set values for each Individual
    void ShowDemos();
    void EvaluateDemos(Sudoku *p);
    double OFunciton(INDIVIDUAL *a);
    double Decode(bool *x, int nGen);
    int DecodeInt(bool *x, int nGen);
    void ShowBestInd(Sudoku *p);
    void ShowProgenitors();
    void Selection();
    void Crossover(Sudoku *p);
    void ShowNewDemos();
    void Mutation(Sudoku *p);
    void EvaluateNewDemos(Sudoku *p);
    void ReplaceOldDemos();
    void ShowSolution();
    double GetBestFitness();
};
double GA::GetBestFitness(){
  return demos[bestIndID].fitness;
}
void GA::ShowSolution(){
  cout << "Solution: ";
  cout << Decode(demos[bestIndID].chromosome,0) << " "
       << Decode(demos[bestIndID].chromosome,1)
       << endl;
}
void GA::EvaluateNewDemos(Sudoku *p){
  unsigned int *solution;
  solution = new unsigned int[nGenes];
  bestNDIndID = 0;
  for (int i=0; i<demosSize; i++){
    for (int j=0; j<nGenes; j++){
      solution[j] = DecodeInt(demos[i].chromosome,j);
    }
    newDemos[i].fitness=p->SolutionFitness(solution);
    if (newDemos[i].fitness>newDemos[bestIndID].fitness)
      bestNDIndID = i;
  }
  delete[] solution;
}
void GA::ReplaceOldDemos(){
  //Best Individual
  if(demos[bestIndID].fitness> newDemos[bestNDIndID].fitness){
    for(int i=0; i<nGenes*geneSize; i++)
      demos[0].chromosome[i] = demos[bestIndID].chromosome[i];
    demos[0].fitness = demos[bestIndID].fitness;
  }
  else{
    for(int i=0; i<nGenes*geneSize; i++)
      demos[0].chromosome[i] = newDemos[bestNDIndID].chromosome[i];
    demos[0].fitness = newDemos[bestNDIndID].fitness;
  }
  bestIndID=0;
  for(int i=1; i<demosSize; i++){
    for(int j=0; j<nGenes*geneSize; j++)
        demos[i].chromosome[j] = newDemos[i].chromosome[j];
      demos[i].fitness = newDemos[i].fitness;
  }
}
void GA::Mutation(Sudoku *p){
  float r;
  for(int i=0; i<demosSize; i++)
    for(int j=0; j<nGenes*geneSize; j++){
      r = (double)rand()/RAND_MAX;
      if (r<Pm){
        newDemos[i].chromosome[j] = !newDemos[i].chromosome[j];
      }
    }
  EvaluateNewDemos(p);
  ReplaceOldDemos();
}
void GA::ShowNewDemos(){
  cout << "New demos:" << endl;
  for(int i=0;i<demosSize;i++){
    cout << "\tIndividual " << i << "\t";
    for(int j=0; j<nGenes*geneSize; j++){
      if(j%geneSize==0) cout << " ";
      cout << newDemos[i].chromosome[j];
    }
    cout << "\t" << "Fitness: " << fixed << setprecision(4) << +newDemos[i].fitness << endl;
  }
}
void GA::Crossover(Sudoku *p){
  //1 point Crossover
  double r; //Crossover probability
  float point = nGenes*geneSize/2;
  for(int i=0; i<demosSize; i+=2){
    r = (double)rand()/RAND_MAX;
    if(r<Pc){
      for(int j=0; j<nGenes*geneSize; j++){
        //child 1
        if(j<point){
          //Child 1
          newDemos[i].chromosome[j] = demos[progenitor[i]].chromosome[j];
          //Child 2
          newDemos[i+1].chromosome[j] = demos[progenitor[i+1]].chromosome[j];
        }
        else{
          //Child 1
          newDemos[i].chromosome[j] = demos[progenitor[i+1]].chromosome[j];
          //Child 2
          newDemos[i+1].chromosome[j] = demos[progenitor[i]].chromosome[j];
        }
      }
    }
    else{
      for(int j=0; j<nGenes*geneSize;j++){
        newDemos[i].chromosome[j] = demos[progenitor[i]].chromosome[j];
        newDemos[i+1].chromosome[j] = demos[progenitor[i+1]].chromosome[j];
      }
    }
  }
  EvaluateNewDemos(p);
}
void GA::ShowProgenitors(){
  cout << "\nProgenitors: " << endl;
  for(int i=0; i<demosSize; i++)
    cout << progenitor[i] << " ";
  cout << endl;
}
void GA::Selection(){
  double sum = 0;
  double aux = 0 ;
  double r;
  //Toltal amount
  for (int i=0; i<demosSize; i++)
    sum+=demos[i].fitness;
  for(int i=0;i<demosSize; i++){
    r = rand()%((int)sum+1);
    aux = 0;
    for(int j=0; j<demosSize; j++){
      aux+=demos[j].fitness;
      if(r<=aux){
        progenitor[i]=j;
        break;
      }
    }
  }
}
void GA::ShowBestInd(Sudoku *p){
  unsigned int *solution;
  solution = new unsigned int[nGenes];
  cout << "Best Individual " << bestIndID << endl;
  for (int j=0; j<nGenes; j++){
    solution[j] = DecodeInt(demos[bestIndID].chromosome,j);
  }
  p->ShowBestSudoku(solution);
  cout << "\n" << "Fitness: " << +demos[bestIndID].fitness << endl;
  delete[] solution;
}
int GA::DecodeInt(bool *x, int nGen){
  int value=0;
  for(int i=0; i<geneSize; i++){
    if(x[i+geneSize*(nGen)])
      value += pow(2,geneSize-i-1);
  }
  return value*(maxValue-minValue)/(pow(2,geneSize)-1)+minValue;
}
double GA::Decode(bool *x, int nGen){
  double value=0;
  for(int i=0; i<geneSize; i++){
    if(x[i+geneSize*(nGen)])
      value += pow(2,geneSize-i-1);
  }
  return value*(maxValue-minValue)/(pow(2,geneSize)-1)+minValue;
}
double GA::OFunciton(INDIVIDUAL *a){
  //f = 50 - ((x1-5)^2+(x2-5)^2)
  double x1 = Decode(a->chromosome,0);
  double x2 = Decode(a->chromosome,1);
  return 50-(pow(x1-5,2)+pow(x2-5,2));
}
void GA::EvaluateDemos(Sudoku *p){
  unsigned int *solution;
  solution = new unsigned int[nGenes];
  bestIndID = 0;
  for (int i=0; i<demosSize; i++){
    for (int j=0; j<nGenes; j++){
      solution[j] = DecodeInt(demos[i].chromosome,j);
    }
    demos[i].fitness=p->SolutionFitness(solution);
    if (demos[i].fitness>demos[bestIndID].fitness)
      bestIndID = i;
  }
  delete[] solution;
}
void GA::ShowDemos(){
  cout << "Demos:" << endl;
  for(int i=0;i<demosSize;i++){
    cout << "\tIndividual " << i << "\t";
    for(int j=0; j<nGenes*geneSize; j++){
      if(j%geneSize==0) cout << " ";
      cout << demos[i].chromosome[j];
    }
    cout << "\t" << "Fitness: " << fixed << setprecision(4) << +demos[i].fitness << endl;
  }
}
void GA::InitializeDemos(){
  for(int i=0; i<demosSize; i++){
    for(int j=0; j<nGenes*geneSize; j++)
      demos[i].chromosome[j] = randomBool();
    demos[i].fitness = 0;
  }
}
GA::GA(int nIndividuals, int numG, int gSize, int min, int max ){
  Pm = 0.01;
  Pc = 0.70;
  minValue = min;
  maxValue = max;
  nGenes = numG;
  geneSize = gSize;
  bestIndID = 0;
  demosSize = nIndividuals;
  demos = new INDIVIDUAL[demosSize];
  newDemos = new INDIVIDUAL[demosSize];
  for (int i=0;i<demosSize;i++){
    demos[i].chromosome = new bool[nGenes*geneSize];
    newDemos[i].chromosome = new bool[nGenes*geneSize];
  }
  progenitor = new int [demosSize];
}
GA::~GA(){
  for (int i=0; i<demosSize;i++){
    delete[] demos[i].chromosome;
    delete[] newDemos[i].chromosome;
  }
  delete[] demos;
  delete[] newDemos;
  delete[] progenitor;
}
