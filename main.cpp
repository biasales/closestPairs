#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>    // std::sort
#include <math.h>

#include <iomanip>
#include<tuple>
using namespace std;


class points
{
    public:
    float x,y;
    points(){x = 0.00; y = 0.00;}
    ~points();
};

float calcDistance(float x1,float y1, float x2, float y2);
void mergeSort(points array[], int const begin, int const end, char pos);
float minDistFront(points* aux, int m, float mind);
float DistBrute(points* point,int size);


float minDistance(points* point, int size){
    points* aux;

    aux = (points *)malloc(sizeof(points)*size);

    int mid,dl,dr,midx;
    float distance,distanceFront;
    int j = 0, i =0;

    if (size<=3)
    {
        return DistBrute(point,size);
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
            auxd = calcDistance(aux[i].x, aux[j].x, aux[i].y, aux[j].y);
            if (auxd < mind)
                mind = auxd;
        }
    }
    return mind;
}

float DistBrute(points* point,int size){

    float minDist = 9999999999999;

     float dist = 0;
     for(int i = 0; i < size ;i++){
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


void openFile(ifstream& inFile, string filename){
    inFile.open(filename);
    if (inFile.is_open())
        cout << "Reading " << filename << endl;
    else{
        cout << "Failed to open file" << filename << endl;
        exit(-1);
    }
}

points* readfile(ifstream& inFile){
    points *point;

    string line;
    string size;
    string coordinate;
    int pos = 0;

    getline(inFile, size);
    point = (points *)malloc(sizeof(points)* stoi(size));

    while (!inFile.eof()) {
        getline(inFile,line);
        istringstream  is(line);
        if (inFile.good()) {
            // Split String coordinates
            getline(is, coordinate, ' ');
            point[pos].x = std::stof(coordinate); 
            getline(is, coordinate, ' ');
            point[pos].y = std::stof(coordinate); 
        }
       pos++;
    }
    return point;
}

int main(){
    ifstream inFile;
    points* point;
    float distancePoints;
    
    int size = 5;
    openFile(inFile,"input.txt");
    // Unpack tuple
    point = readfile(inFile);
    
    mergeSort(point,0,size-1,'x');

  for(int i = 0; i< size; i++){
      cout <<"Ponto x "<<point[i].x<<endl;
      cout <<"Ponto y "<<point[i].y<<endl;
      cout<<"++++++++++++++++++++++"<<endl;
  }

    distancePoints = minDistance(point,size);

    cout<<"a menor distancia eh"<<distancePoints<<endl;

  return 0;
}