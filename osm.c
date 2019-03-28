// Linear Covolution by Overlap Save Method


/
Author: Komal Mane (TE ETRX, 2015110023)
/

#include<stdio.h>
#include<math.h>
#define max 64		//Defining constant 

//initialize functions required for calculations

void Fast_Circular_Convolution(float *x, int N, float *h, float *y); //LC by CC by FFT
void DITFFT_8_Point( int N, float x[8][2], float t[8][2]);    //8 point FFT function defined
void DITFFT_4_Point( int N, float x[4][2], float t[4][2]);    //4 point FFT function defined

main()
{
    int i,j,k,SigLen,M,N,L;
    float x[max],p[max],t[max],y[max];
    float h[max];

	//initialize variables and arrays
	
    for(i=0;i<max;i++) // Initialize the value of arrays to zero 
    {
       x[i]=0; h[i]=0; y[i]=0; p[i]=0;
    }
  
  
    //Take input from user 

    printf("\n Enter the length of x[n] = : ");         //length of long input signal
    scanf("%d",&SigLen);
    
    
    printf( "\n Enter the values of x[n] : ");

    for(i=0;i<SigLen;i++)
    {
	 scanf("%f",&x[i]);                      //entering the values of x[n] in respective array
    }
    
    printf("\n\n Enter the length of h[n] M = : ");
    scanf("%d",&M);                                     //length of h[n]
    
    printf( "\n Enter the values of h[n] : ");

    for(i=0;i<M;i++)
    {
	scanf("%f",&h[i]);                      //entering the values of h[n] in respective array
    }

    //Calculation procedure for OSM begins here 
    	
    N = 8; // Assume the value of N
    
    L = N - M; // Length of decomposed x[n]
    //priniting the length of the input and output signal
    printf( "\n\n length of decomposed input Signal  : L = %d ", L);
    printf( "\n\n length of decomposed output Signal : N = %d ", N);
    
    
    for(i=0; i<L; i++)    
	
	p[i+M] = x[i]; // Splitting of x[n] as first signal with initial zeros
    
    j = 0;    //initializing the counter
    int d = 0;
        
    for (k=0; k<SigLen; k+=L)
    {
    
              
    	Fast_Circular_Convolution(p, N, h, t); 
		// Call functionfor Linear Convolution by Circular Convolution by FFT 
    	
    	for(i=0; i<L; i++)  
    	{
    		y[k+i] = t[i+M]; // Overap Save here
        }
    	
    	j++;  //increment counter
    	
    	printf("\n\n\n x%d[n] = ", j );   // Obtain decomposed x[n]
        for(i=0;i< N; i++)    
    	printf("  %4.2f  ",p[i]);  //printing the decomposed signal with 4 significant figures and two decimal places
	
	printf("\n\n y%d[n] = ",j );  // Obtain decomposed y[n]
        for(i=0;i< N;i++)    
    	printf("  %4.2f  ",t[i]);   //printing the temporary output with 4 significant figures and two decimal places
        
        d = k+L-M;
        for(i=0; i<N; i++)    p[i] = x[d+i]; // Splitting of x[n] with  previous M values 
        
     }
     

 //print the obtained results for overlap save method

  
    printf("\n\n Linear Convolution Output using Over Save Method  " );
    printf("\n y[n] = " );  // Result of LC
    for(i=0;i<(SigLen+M-1);i++)    
    	printf("  %4.2f  ",y[i]);
    	//printing the final output
    printf("\n\n");

}

//function for Circular Convolution 

void Fast_Circular_Convolution(float *x, int N, float *h, float *y)
{
     
        int i,j,k;
        float X[max][2],H[max][2],Y[max][2],t[max][2],p[max][2];
        
  	
	for(k=0; k<N; k++)  // Initialize the value of arrays to zero
        {
              
              X[k][0] = 0;    X[k][1] = 0;
              H[k][0] = 0;    H[k][1] = 0;
              Y[k][0] = 0;    Y[k][1] = 0;
        }
        
        
        for(i=0;i<N;i++) // Copy x[n] to t[n][0]
        {
        
              t[i][0] = x[i]; t[i][1] = 0;
         
        
        }
        
        // To find X[k] and check whether signal is 4 point or 8 point and then call the function for DITFFT accordingly
        
        if ( N == 4 ) 
             DITFFT_4_Point(N,t,X);  
        else if ( N == 8 )    
             DITFFT_8_Point(N,t,X);  
       
       
       
        for(i=0;i<N;i++)  // Copy h[n] to t[n][0]	
        {
        
              t[i][0] = h[i]; t[i][1] = 0;
        
        }
        
        
        // Find H[k] and check whether signal is 4 point or 8 point and then call the function for DITFFT accordingly
        
         if ( N == 4 ) 
             DITFFT_4_Point(N,t,H);  
         else if ( N == 8 )    
             DITFFT_8_Point(N,t,H);  
       
       
       // Find Y[k] and check whether signal is 4 point or 8 point and then call the function for DITFFT accordingly
        
        for(k=0; k<N; k++)  
        {
              float a,b,c,d;
              
              a = X[k][0];   b = X[k][1];
              c = H[k][0];   d = H[k][1];
              
              Y[k][0] = (a * c) - (b * d);
              Y[k][1] = (b * c) + (a * d);
              
        }
    
    
       // Find Y*[k] and check whether signal is 4 point or 8 point and then call the function for DITFFT accordingly
     
     	for (k=0; k< N; k++)
     	{
        	 Y[k][1] = Y[k][1] * (-1);
     	
     	}
     
       // Find FFT{Y*[k]} and check whether signal is 4 point or 8 point and then call the function for DITFFT accordingly
       
        if ( N == 4 ) 
             DITFFT_4_Point(N,Y,p);  
        else if ( N == 8 )    
             DITFFT_8_Point(N,Y,p);  
       
       
           
        // find p[n] = {  FFT{Y*[k]} / N  }* 
    
   	
	for(i=0;i<N;i++)
	{
		p[i][0] = p[i][0]/N;
		p[i][1] = (-1) * p[i][1]/N;
	}

       for(i=0;i<N;i++)  // Copy p[][] to y[n]
       {
		y[i] = p[i][0];

	}

      
        

}

//function for circular convolution 

void DITFFT_8_Point( int N, float x[8][2], float t[8][2])
{

     	
     	int i,j,k;
      	float e;
        float X1[4][2], X2[4][2], G[4][2], H[4][2];
	
	 
	
	for(i = 0; i < 4; i++)
	{
        	X1[i][0] = x[2*i][0];    X1[i][1] = x[2*i][1];  
               
                X2[i][0] = x[2*i+1][0];  X2[i][1] = x[(2*i)+1][1];  
        }
        
	  
	DITFFT_4_Point(4,X1,G);
	
	DITFFT_4_Point(4,X2,H);

	
	 
	// X[k] = G[k] + W H[k] 
           	
        e = 6.283185307179586/N;   	//calculations for twiddle factor 
        
        for(k=0; k<4; k++)
        {
        
                t[k][0] = G[k][0] + ( H[k][0] * cos(e*k) + H[k][1] * sin(e*k) );
                t[k][1] = G[k][1] + ( H[k][1] * cos(e*k) - H[k][0] * sin(e*k) );

        }
        
        for(k=0; k<4; k++)
        {
                d = k + 4;
                t[d][0] = G[k][0] + ( H[k][0] * cos(e*d) + H[k][1] * sin(e*d) );
                t[d][1] = G[k][1] + ( H[k][1] * cos(e*d) - H[k][0] * sin(e*d) );

        }
        
              
	 	        
}

//function to calculate 4 point DITFFT

void DITFFT_4_Point( int N, float x[4][2], float t[4][2])
{
     		     	
	int i,j,k,n;
     	float e;
        float G[4][2], H[4][2];
	
	
	for(n=0; n<N; n++)
	{
		t[n][0] = 0; t[n][1] = 0;
		G[n][0] = 0; G[n][1] = 0;
		H[n][0] = 0; H[n][1] = 0;
		
	}

	  // Stage-1 calculations for Twiddle Factor
	 
	 
		 G[0][0] = x[0][0] + x[2][0];    G[0][1] = x[0][1] + x[2][1];
		
		 G[1][0] = x[0][0] - x[2][0];    G[1][1] = x[0][1] - x[2][1];
		 
		 H[0][0] = x[1][0] + x[3][0];    H[0][1] = x[1][1] + x[3][1];
		
		 H[1][0] = x[1][0] - x[3][0];    H[1][1] = x[1][1] - x[3][1];
	
	  	
		  
        
          // Stage-2 calculations for Twiddle Factor
          
	  e = 6.283185307179586/N;
         	
         
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

