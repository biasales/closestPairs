#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>   
#include <math.h>
#include <time.h>
#include <iomanip>
#include<tuple>
using namespace std;


class points
{
    public:
    double x,y;
    points(){x = 0.00; y = 0.00;}
    ~points();
};
struct stcDistance{
    double x1,y1,x2,y2;
    double size;
};

double calcDistance(double x1,double y1, double x2, double y2);
void mergeSort(points array[], int const begin, int const end, char pos);
stcDistance minDistFront(points* aux, int m, stcDistance mind);
stcDistance DistBrute(points* point,int size);
stcDistance smallerDistance(stcDistance dist1, stcDistance dist2);


stcDistance minDistance(points* point, int size){
    points* aux;
    aux = (points *)malloc(sizeof(points) * size);
    
    int mid;
    double midx;
    stcDistance dl = stcDistance();
    stcDistance dr = stcDistance();
    stcDistance distance = stcDistance();
    stcDistance distanceFront = stcDistance();

    int j = 0, i = 0;

    if (size<=3)
        return DistBrute(point,size);
    mid = size/2;
    dl = minDistance(point , mid);
    dr = minDistance(point + mid, size - mid);
    distance = smallerDistance(dl, dr);
    midx = point[mid].x;

    for ( ; i < size; i++){
        if ((abs(point[i].x) - midx) < distance.size){
            aux[j++] = point[i];
        }
    }
    distanceFront = minDistFront(aux, j, distance);
    return smallerDistance(distance, distanceFront);
}
stcDistance smallerDistance(stcDistance dist1, stcDistance dist2){
    return (dist1.size < dist2.size) ? dist1 : dist2;
}
stcDistance minDistFront(points* aux, int m, stcDistance mind){
    int i;
    double auxd;

    mergeSort(aux, 0, m-1, 'y');
    for (i = 0; i <= m-1; i++){
        for (int j = i+1; ((j < m) && (aux[m].y) < mind.size); j++){
            auxd = calcDistance(aux[i].x, aux[i].y, aux[j].x, aux[j].y);
            if (auxd < mind.size){
                mind.x1 = aux[i].x;
                mind.y1 = aux[i].y;
                mind.x2 = aux[j].x;
                mind.x2 = aux[j].y;
                mind.size = auxd;
            }
        }   
    }
    return mind;
}

stcDistance DistBrute(points* point, int size){

    double minDist = 999999999;
    stcDistance dist = stcDistance();
    double distance = 0;
        for(int i = 0; i < size; i++){
        distance = calcDistance(point[i].x, point[i].y, point[i+1].x, point[i+1].y); 
            if (distance < minDist){
                minDist = distance;
                dist.x1 = point[i].x;
                dist.y1 = point[i].y;
                dist.x2 = point[i+1].x;
                dist.y2 = point[i+1].y;
                dist.size = distance;
            }
        }
    return dist;
 }

double calcDistance(double x1,double y1, double x2, double y2){ 
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

void mergeSort(points array[], int const begin, int const end, char pos) 
{
    if (begin >= end)
        return; 
  
    int mid = begin + (end - begin) / 2;

    mergeSort(array, begin, mid,pos);
    mergeSort(array, mid + 1, end,pos);
    merge(array, begin, mid, end, pos);
}


void openFile(ifstream& inFile, string filename){
    inFile.open(filename);
    if (!inFile.is_open()){
        cout << "Failed to open file" << filename << endl;
        exit(-1);
    }
    
}

points* readfile(ifstream& inFile, int size){
    points *point;
    string line;
    string coordinate;
    int pos = 0;

    point = (points *)malloc(sizeof(points)* size);

    while (!inFile.eof() && pos < size) {
        getline(inFile,line);
        stringstream  is(line);

        if (inFile.good()) {
            getline(is, coordinate, ' ');
            point[pos].x = stod(coordinate); 
            getline(is, coordinate, ' ');
            point[pos].y = stod(coordinate); 
        }
       pos++;
    }
    return point;
}

int main(int argc,char* argv[]){
    if (argc < 2){
        cout << "Insira o nome do arquivo" << endl;
    }

    ifstream inFile;
    points* point;
    stcDistance distancePoints = stcDistance();
    string firstLine;
    int size;
    double timeElapsed;
    
    clock_t start = clock();
    
    openFile(inFile,argv[1]);
    getline(inFile, firstLine);
    size = stoi(firstLine);
    point = readfile(inFile, size);

    mergeSort(point,0,size-1,'x');
    
    distancePoints = minDistance(point, size);
    free(point);
    clock_t end = clock();
    timeElapsed = double(end-start)/CLOCKS_PER_SEC;

    cout<<timeElapsed<<distancePoints.size<<distancePoints.x1<<distancePoints.y1<<distancePoints.x2<<distancePoints.y2<<endl;  
    return 0;
}