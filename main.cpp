#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>    // std::sort
#include <math.h>


using namespace std;


class points
{
    public:
    float x,y;
    points(){x = 0.00; y = 0.00;}
    ~points();
};

float minDistance(points* point, int size){
    points* aux;

    aux = (points *)malloc(sizeof(points)*size);

    int mid,dl,dr,midx;
    float distance,distanceFront;
    int j = 0, i =0;

    if (size<=3)
    {
        return DistBrute(point);
    }
    mid = size/2;
    dl = minDistance(point,mid);
    dr = minDistance(point+mid,size-mid);
    distance = min(dl,dr);
    midx = point[mid].x;

    for (;i<size;i++){
        if ((abs(point[i].x) - midx) < distance){
            aux[j++] = point[i];
        }
    }
    distanceFront = minDistFront(aux,j,distance);
    return min(distance,distanceFront);
}

float minDistFront(points* aux, int m, float mind){
    int i=0;
    float auxd;

    mergeSort(aux,0,m-1,'y');//em funcao de y
    for (i=0;i<=m-1;i++){
        for (int j = i+1; ((j < m) && (aux[m].y)< mind); j++){
            
            
        }
    
    }

}

float DistBrute(points* point){

    float minDist = 9999999999999;
    float dist = 0;
    for(int i = 0; i < point.size(); i++){
        dist = calcDistance(point[i].x, point[i].y, point[i+1].x, point[i+1].y); 
        if (dist < minDist)
            minDist = dist;
    }
    
    return minDist;
}


float calcDistance(float x1,float y1, float x2, float y2){ //teorema de euclides
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}


void merge(points array[], int const left, int const mid, int const right, char pos)
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;
  
    points *leftArray = new points[subArrayOne],
         *rightArray = new points[subArrayTwo];
  
    for (int i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
  
    int indexOfSubArrayOne = 0,
        indexOfSubArrayTwo = 0; 
    int indexOfMergedArray = left;

    if (pos == 'x'){
        while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne].x <= rightArray[indexOfSubArrayTwo].x) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
        }
    }

    else {
        while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne].y <= rightArray[indexOfSubArrayTwo].y) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
        }
    }
    
    

    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

void mergeSort(points array[], int const begin, int const end, char pos) //falta x ou y
{
    if (begin >= end)
        return; // Returns recursively
  
    int mid = begin + (end - begin) / 2;

    mergeSort(array, begin, mid,pos);
    mergeSort(array, mid + 1, end,pos);
    merge(array, begin, mid, end, pos);
}

int main(){
  string line,temp = "";
  int i =0, numPoints = -1,size = 5;
  points *point;
  float distance;

  point = (points *)malloc(sizeof(points)*size);

  ifstream myfile ("input.txt"); //TODO: separar leitura de arquivo em uma função
  //TODO:ler o n do arquivo
  if (myfile.is_open())
  {
    while (! myfile.eof() )
    {
      getline (myfile,line);
      temp = "";
      for(i=0; i < line.size();i++){
          if (line[i] != ' '){
              temp = temp + line[i];
          }
          else {
              break;
          }
      }
      if (temp != ""){
        point[numPoints].x = std::stof(temp); 
      }
       temp = "";

      for (i = i+1 ; i < line.size();i++){
            temp = temp + line[i];
      }

      if (temp != ""){
         point[numPoints].y = std::stof(temp); 
      }
      
        numPoints++;

    }
  }
 
  mergeSort(point,0,size-1,'x');

  for(i = 0; i< size; i++){
      cout <<"Ponto x "<<point[i].x<<endl;
      cout <<"Ponto y "<<point[i].y<<endl;
      cout<<"++++++++++++++++++++++"<<endl;
  }

 // distance = minDistance(point,size);

  return 0;
}