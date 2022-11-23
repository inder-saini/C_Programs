#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void convolve();

int main(){
    int arr1[] = {1,2,3};
    int arr2[] = {4,5,6};
    int len1 = sizeof(arr1)/sizeof(int);
    int len2 = sizeof(arr2)/sizeof(int);
    convolve(arr1,arr2,len1,len2);
}
  
void convolve(int list1[],int list2[],int len1, int len2){
    
int i = 0;
int j = 0;
int M = (len1+len2)-1; //'M' is the number of terms we get after convolution.

int y[M]; //This is the array of length 'M', where we will store the convolved elements.
int new_list1[M]; //We are padding the original array 'arr1' to have the length of M for convolution. 
int new_list2[M]; //We are padding the original array 'arr2' to have the length of M for convolution. 

   for (i = 0;i<len1;i++){
    new_list1[i] = list1[i];
   }
   for(i = len1;i<M;i++){
       new_list1[i] = 0;
   }

   for (i = 0;i<len2;i++){
    new_list2[i] = list2[i];
   }
   for(i = len2;i<M;i++){
       new_list2[i] = 0;
   }

    for(i = 0;i<M;i++){
       y[i] = 0;
        for(j = 0;j<=i;j++){
         y[i] = y[i]+(new_list1[j]*new_list2[i-j]);     
        }
        printf("The sum is: %d\n",y[i]); 
       
    }

}
