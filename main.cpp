#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
//#include <chrono>
#define SIZE(x)  (sizeof(x) / sizeof((x)[0]))
using namespace std;
//using namespace std::chrono;
int cnt1=0;

typedef struct share
{
    string date;
    float open;
}SHARE;

void PrintArray(SHARE array[],int N)
{
  
    for(int i=0;i<=N-1;i++)
    {
        cout<<"Date:"<<array[i].date<<"\tOpen:"<<array[i].open<<endl;
    }
}

void ReadFile(const string inputfile,SHARE *array)
{
    int i=0;
    ifstream  InFile(inputfile);
    if(InFile.good())
    {
        string temp;
        getline(InFile,temp);
        while(!InFile.eof())
     {
        getline(InFile,array[i].date,',');
        getline(InFile,temp,',');
        array[i].open=stof(temp);
        getline(InFile,temp,'\n');
        i++;   
     }
    InFile.close();
    }
   else
   {
      cout<<"Error opennning the file...Aborting..."<<endl;
      exit(0);
   }
}

int NoOfLine(string f)
{
    int cnt=0;
    ifstream file(f);
    string cline;
    if(file.good())
    {
     while(getline(file,cline))
        cnt++;   
    file.close();
    }
   else
   {
      cout<<"Error opennning the file...Aborting..."<<endl;
      exit(0);
   }
    return cnt-1;
}

void swap(int *a, int *b) 
{ 
    int temp;
    temp = *a; 
    *a = *b; 
    *b = temp; 
} 
void swapSh(SHARE &a,SHARE &b)
{
    SHARE TEMP;
    TEMP.date = a.date;
    TEMP.open = a.open;
    a.date = b.date;
    a.open = b.open;
    b.date = TEMP.date;
    b.open = TEMP.open;
}

void Qsort(SHARE S[],int start,int end) //ok
{   
   
    int Pleft,Pright,pivot;
    
    if(start<end){

     pivot = start; //Pivot element.Here first
     Pleft=start; //Pointer to the left of the Array.
     Pright=end;  //Pointer to the right of the Array.
     
    for(;Pleft<Pright;)
        {
           
             for(;(S[Pleft].open<=S[pivot].open && Pleft<end) || (S[Pright].open>S[pivot].open);)
            {
               Pleft+=(S[Pleft].open<=S[pivot].open && Pleft<end)?1:0;
               Pright-=(S[Pright].open>S[pivot].open)?1:0;
            }
            if(Pleft<Pright)
                swapSh(S[Pleft],S[Pright]);
        }
    
    swapSh(S[pivot],S[Pright]);
    Qsort(S,start,Pright-1);
    Qsort(S,Pright+1,end);
    }
}

void Merge(SHARE ar[],int left,int right,int mid){
    
    int n1 = mid - left + 1; //pointers of the temp arrays we will create to store n/2
    int n2 = right - mid;
    
    SHARE tempar1[n1];
    SHARE tempar2[n2];  //creation of the temp arrays
    
    for(int i=0; i<n1; i++){           // fill em with the elements
        tempar1[i].open=ar[left+i].open;
        tempar1[i].date=ar[left+i].date;
    }
    
    for(int j=0; j<n2; j++){
        tempar2[j].open=ar[mid + 1 + j].open;
        tempar2[j].date=ar[mid + 1 + j].date;
    }
    
    int i = 0;  //index of the first temp array
    
    int j = 0;  //index of the second temp array
    
    int k = left;   //index of the final merged array 
    
    while(i < n1 && j < n2){
        if(tempar1[i].open < tempar2[j].open){
            ar[k].open = tempar1[i].open;
           ar[k].date = tempar1[i].date;
            i++;
            k++;
        }
        else{
            ar[k].open = tempar2[j].open;
            ar[k].date = tempar2[j].date;
            j++;
            k++;
        }
    }
    
    while(i < n1){
        ar[k].open=tempar1[i].open;
        ar[k].date=tempar1[i].date;
        i++;
        k++;
    }
    while (j < n2) 
    { 
        ar[k].open = tempar2[j].open;
       ar[k].date = tempar2[j].date; 
        j++; 
        k++; 
    } 
    
}

void mergesort(SHARE ar[],int left, int right){
    if (left<right){
        int mid = left + (right - left) / 2;
        
        mergesort(ar,left,mid);
        mergesort(ar,mid+1,right);
        
        Merge(ar,left,right,mid);
    }
    
}


int main ()
{ 
    int choise;
    string InputFilePath;
    cout<<"Please insert the file with the share info: "<<endl;
    cout<<"press 1:agn.us.txt"<<endl;
    cout<<"press 2:ainv.us.txt"<<endl;
    cout<<"press 3:ale.us.txt"<<endl;
    cin>>choise;
    
    switch(choise){
    case 1:
     InputFilePath="agn.us.txt"; 
     break;
   
    case 2:
     InputFilePath="ainv.us.txt"; 
     break;
    
    case 3:
     InputFilePath="ale.us.txt";
     break; 
     
     
    }
    
    SHARE SH[NoOfLine(InputFilePath)];
    ReadFile(InputFilePath,SH);
    
    cout<<"Change algorithm for short"<<endl;
    cout<<"press 1:quickshort"<<endl;
    cout<<"press 2:mergshort"<<endl;
    cin>>choise;
    
    switch(choise){
        case 1:
        Qsort(SH,0,SIZE(SH)-1);
        break;
        
        case 2:
        mergesort(SH,0,SIZE(SH)-1);
        break;
    }
    
     //  auto start = high_resolution_clock::now();
   // auto duration = duration_cast<microseconds>(stop - start);*/
   // auto stop2 = high_resolution_clock::now();
 
   PrintArray(SH,SIZE(SH));

    return 0;
} 
