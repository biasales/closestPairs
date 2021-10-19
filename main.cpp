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

void merge(points array[], int const left, int const mid, int const right)
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;
  
    // Create temp arrays
    points *leftArray = new points[subArrayOne],
         *rightArray = new points[subArrayTwo];
  
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (int i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
  
    int indexOfSubArrayOne = 0, // Initial index of first sub-array
        indexOfSubArrayTwo = 0; // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array
  
    // Merge the temp arrays back into array[left..right]
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
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}
  
// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted 

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
  char c = 0;
  int i =0, numPoints = -1,n = 5;
  points *point;

  point = (points *)malloc(sizeof(points)*n);

  ifstream myfile ("input.txt"); //abre arquivo
  if (myfile.is_open())
  {
    while (! myfile.eof() ) //enquanto end of file for false continua
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
        point[numPoints].x = std::stof(temp); //salva cood x
      }
       temp = "";

      for (i = i+1 ; i < line.size();i++){
            temp = temp + line[i];
      }

      if (temp != ""){
         point[numPoints].y = std::stof(temp); //salva cood y
      }
      
        numPoints++;
     
    }
  }
 

   for(i = 0; i< n; i++){
      cout <<"Ponto x "<<point[i].x<<endl;
      cout <<"Ponto y "<<point[i].y<<endl;
      cout<<"++++++++++++++++++++++"<<endl;
  }

  mergeSort(point,0,4);
  cout<<"depois do merge"<<endl;

    for(i = 0; i< n; i++){
      cout <<"Ponto x "<<point[i].x<<endl;
      cout <<"Ponto y "<<point[i].y<<endl;
      cout<<"++++++++++++++++++++++"<<endl;
  }


  return 0;
}