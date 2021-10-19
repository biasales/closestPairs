#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>    // std::sort


using namespace std;

struct points {
    float x;
    float y;
};

float minDistance(points point[], int size){
    int m,dl,dr,d;
    int j = 0, i =0;
    if (size<=3)
    {
        //return minDistBrute(point[0]);
    }
    m = size/2;
   // dl = minDistance(point[0],m);
    //dr = minDistance(point[m],n-m);
    //d = min(dl,dr);
    

}

void merge(points array[], int const left, int const mid, int const right)
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

void mergeSort(points array[], int const begin, int const end)
{
    if (begin >= end)
        return; // Returns recursively
  
    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}



int main(){
  string line,temp = "";
  int i =0, numPoints = -1,size = 5;
  points *point;
  float distance;

  point = (points *)malloc(sizeof(points)*size);

  ifstream myfile ("input.txt"); 
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
 

   for(i = 0; i< size; i++){
      cout <<"Ponto x "<<point[i].x<<endl;
      cout <<"Ponto y "<<point[i].y<<endl;
      cout<<"++++++++++++++++++++++"<<endl;
  }

  mergeSort(point,0,size-1);

  distance = minDistance(point,size);

  return 0;
}