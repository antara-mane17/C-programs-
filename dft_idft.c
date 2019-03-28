/*
        Author: Komal Mane
             DFT-IDFT
*/




#include<stdio.h>
#include<math.h>

int dft(int N, float *X){
float static X_Real[100], X_Img[100];                                       //defining two arrays to store the real and imaginary values seperately
int n,k;                                                                    //defining the counters for the array calculations 

/*To find the discrete fourier transform*/                                                               
printf("\tDiscrete Fourier Transform\n");
for(k=0;k<N;k++)
{
X_Real[k]=X_Img[k]=0.00;                                                   //the sums will reset to zero for every different value of k
 for(n=0;n<N;n++)                                                          //calculation for n=0 to n=N begins
     {
       X_Real[k]=X_Real[k]+X[n]*cos((2*M_PI*k*(n-N))/N);                   //Summation of X[n]*real(W*nk) where W is the twiddle factor and real(W*nk)=cos(2*M_PI*k*(n-N)/N)
       X_Img[k]=X_Img[k]+X[n]*sin((2*M_PI*k*(n-N))/N);                     //Summation of X[n]*img(W*nk) where W is the twiddle factor and img(W*nk)=sin(2*M_PI*k*(n-N)/N)
     }
     X_Img[k]=X_Img[k]*(-1.0);                                             //negating the imaginary value as W has the power of (-j) and it expands to cos(t)-j*sin(t)
}
/*printing the obtained DFT as output */
printf("\nThe %d point DFT of given sequence is:\n",N); 
printf("\n\n\tReal X(k)\t\tImaginary X(k)\n");
   for(k=0;k<N;k++)
   printf("\nX(%d)= %f\t\t\t%f\n\n",k,X_Real[k],X_Img[k]);

/*To find the inverse DFT of the obtained DFT*/
printf("\tInverse DFT\n");
for(n=0;n<N;n++)
 {
  X[n]=0;
  for(k=0;k<N;k++)
  {
   X[n]=X[n]+X_Real[k]*cos((2*M_PI*k*n)/N)-X_Img[k]*sin((2*M_PI*k*n)/N);   //Summation of X[k]*W^(-nk)
  }
  X[n]=X[n]/N;                                                             //Dividing by N to obtain the value of X[n] as per the IDFT formula
 }
/*printing the obtained IDFT as output*/
 printf("\n\n The sequence x(n) is as follows:");
 for(n=0;n<N;n++)
 {
  printf("\n\n X(%d)=%3.6f",n,X[n]);
 }

}

void main(){
int k,n,N;                                                                      //defining n,k and the length of sequence N
float static X[100];                                                            //defining the array to store the sample sequence, max length=100

/*Input the sample sequence of length N*/                                                       
printf("Enter the number of samples in the sequence X(n)=");                                                                                                
scanf("%d",&N);
printf("Enter the samples of X(n):\n");
for(n=0;n<N;n++){
 scanf("%f",&X[n]);                                
}

/*Calling the DFT function to find the DFT. The length of the sequence array and the sequence array have been passed*/
dft(N,X);
}



