/*       
	AUTHOR  : Komal Mane
	FFT 8 Point
*/


#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void FFT_4_Point( int N, float x[4][2], float t[4][2]);  //initialising the 4-point fft function
void FFT_8_Point( int N, float x[8][2], float t[8][2]);  //initialising the 8-point fft function

void main()
{
	     int i,j,k,n,L,N;
	     float x[8][2], X[8][2],t[8][2]; //A two dimensional array to store real and imaginary values
	    
	     for(i=0;i<4;i++)   // Real & Imaginary part initialization
	     {
		 X[i][0] = 0; X[i][1] = 0; // Input X[k] = 0 
		 x[i][0] = 0; x[i][1] = 0; // Output x[n] = 0 
	     }
	   
	     printf("\n\n Enter the length of x[n] ( 4 pt or 8 pt)  = : ");  //Input the length of x[n]
	     scanf("%d",&L);
	  
	     if ( L > 4 ) 
                  N = 8; 
             else N = 4; // N must be Radix 2 Number for FFT algorithm
	   

	     printf( " Enter the values of x[n]     : ");   

	     for(i=0;i<L;i++)
	     {
		 scanf("%f",&x[i][0]);                 //Input the values of x[n] according to the length specified earlier
	     }
 
	     if(N==4) 
		    FFT_4_Point(N, x, X);           //calling the respective function according to the length of the input
	     else if(N==8) 
		    FFT_8_Point(N, x, X);
	     else 
		    exit(0);

//DIT-FFT Result	     
	     printf("\n\n FFT results X[k] =  :\n  ");           //printing the fft result 
             for(k=0; k<N; k++) {
	     printf("\n %7.3f  + j  %7.3f", X[k][0], X[k][1]);   //for loop to print the real and imaginary values
             }
	     
	     printf("\n\n");

//INVERSE DIT-FFT
	       
	     for(i=0;i<N;i++)   // initilization of an empty output array
		{
		 	x[i][0] = 0; // Re(x[n])=0
                        x[i][1] = 0; // Im(x[n])=0
		}
	      
             for (k=0; k< N; k++)
		{
		     X[k][1] = X[k][1] * (-1);      //taking the complex conjugate of X[k]=X*[k]

		}
              //For Radix-2 N, calling the fft function to find FFT(X*[k])
	     if (N==4)                             
		   FFT_4_Point(N,X,x); //for N=4          
	     else if (N==8) 
		   FFT_8_Point(N,X,x); //for N=8
	     else 
		   exit(0);
              //Finding x[n] = {  FFT{X*[k]} / N  }* 
	     for(n=0; n<N; n++)                         
		{
			x[n][0] = (float) x[n][0]/N;
			x[n][1] = (-1) * x[n][1]/N;
		}
              //Printing the obtained inverse fft
                printf("\n Inverse FFT results x[n] =  :\n  ");

		for(n=0; n<N; n++) 
		printf("\n %7.3f  + j  %7.3f", x[n][0], x[n][1]);

		printf("\n\n");
}

void FFT_8_Point( int N, float x[8][2], float t[8][2])           //defining the DITFFT function for an 8 point sequence
{
     	int i,j,k,d;
      	float X1[4][2], X2[4][2], G[4][2], H[4][2];
		
	for(i = 0; i < 4; i++)                                  //splitting the inout sequence into N/2 long odd and even sequences
	{
        	X1[i][0] = x[2*i][0];                           //N/2 even sequence
                X1[i][1] = x[2*i][1]; 
               
                X2[i][0] = x[2*i+1][0];                        //N/2 odd sequence
                X2[i][1] = x[(2*i)+1][1];  
        }

        //solving each of the N/2 sequence with 4 point DITFFT 
        FFT_4_Point(4,X1,G); 
	FFT_4_Point(4,X2,H);
        
        // X[k] = G[k] + W H[k]
           	
        float e = 6.283185307179586/N;   //initialising twiddle factor	

        //operating over obtained G[k] and H[k] to obtain final output

        for(k=0; k<4; k++)   //for n=even                                       
        {
        
                t[k][0] = G[k][0] + ( H[k][0] * cos(e*k) + H[k][1] * sin(e*k) );
                t[k][1] = G[k][1] + ( H[k][1] * cos(e*k) - H[k][0] * sin(e*k) );

        }
        
        for(k=0; k<4; k++)  //for n=odd
        {
                d = k + 4;
                t[d][0] = G[k][0] + ( H[k][0] * cos(e*d) + H[k][1] * sin(e*d) );
                t[d][1] = G[k][1] + ( H[k][1] * cos(e*d) - H[k][0] * sin(e*d) );

        }	 	        
}

void FFT_4_Point( int N, float x[4][2], float t[4][2])            //defining the DITFFT function for an 4 point sequence
{		     	
	int i,j,k,n,d;
     	float e;
        float G[4][2], H[4][2];
	
	for(n=0; n<N; n++) //initialisinig all outputs as 0
	{
		t[n][0] = 0; t[n][1] = 0;
		G[n][0] = 0; G[n][1] = 0;
		H[n][0] = 0; H[n][1] = 0;
		
	}

	  // Stage-1 (2 point DITFFT)
	 
	 
		 G[0][0] = x[0][0] + x[2][0];    G[0][1] = x[0][1] + x[2][1];
		
		 G[1][0] = x[0][0] - x[2][0];    G[1][1] = x[0][1] - x[2][1];
		 
		 H[0][0] = x[1][0] + x[3][0];    H[0][1] = x[1][1] + x[3][1];
		
		 H[1][0] = x[1][0] - x[3][0];    H[1][1] = x[1][1] - x[3][1];
	
	  	
		  
        
          // Stage-2 (4 point DITFFT)
          
	  e = 6.283185307179586/N;      //initialising twiddle factor	
         	
         
         // X[k] = G[k] + WNnk H[k]
         
         
               k=0;   t[0][0] = G[0][0] + ( H[0][0] * cos(e*k) + H[0][1] * sin(e*k) );
                      t[0][1] = G[0][1] + ( H[0][1] * cos(e*k) - H[0][0] * sin(e*k) );
                      
               k=1;   t[1][0] = G[1][0] + ( H[1][0] * cos(e*k) + H[1][1] * sin(e*k) );
                      t[1][1] = G[1][1] + ( H[1][1] * cos(e*k) - H[1][0] * sin(e*k) );


               k=2;   t[2][0] = G[0][0] + ( H[0][0] * cos(e*k) + H[0][1] * sin(e*k) );
                      t[2][1] = G[0][1] + ( H[0][1] * cos(e*k) - H[0][0] * sin(e*k) );


               k=3;   t[3][0] = G[1][0] + ( H[1][0] * cos(e*k) + H[1][1] * sin(e*k) );
                      t[3][1] = G[1][1] + ( H[1][1] * cos(e*k) - H[1][0] * sin(e*k) );

    	 	        
}
