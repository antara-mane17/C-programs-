/*       
	AUTHOR  : Komal Mane
	IIM LPF
*/


#include<stdio.h>
#include<math.h>
#include<stdlib.h>

Ap = input('Enter Pass Band Attenuation:')
As = input('Enter Stop Band Attenuation:')
p = input('Digital frequency for pass band in Hertz:')
s = input('Digital Frequency for stop band in Hertz:')
Fs = input('Enter Sampling Frequency:')
method_flag = input('Press "1" for IIM, Press "2" for BLT')

wp = 2*3.14*(p/Fs)
ws = 2*3.14*(s/Fs)

if method_flag == 1
  AnaP = Fs*wp
  AnaS = Fs*ws
else
  AnaP = 2*Fs*tan(wp/2)
  AnaS = 2*Fs*tan(ws/2)
end

if AnaS>AnaP
  temp1 = AnaS
  temp2 = AnaP
else 
  temp1 = AnaP
  temp2 = AnaS
end
    
N = log10(sqrt(10^(As/10)-1)/(10^(Ap/10)-1))/log10(temp1/temp2)
N = ceil(N)

cutoff = (AnaP)/((10^(Ap/10)-1)^(1/(2*N)))
[zb,pb,kb] = butter(N,cutoff,'low','s')
[a,b] = zp2tf(zb,pb,kb)

g = tf(a,b)
disp(g)

if method_flag == 1
 %IIM
 [A,B]= impinvar(a,b,Fs)
 final = tf(A,B)
 disp('Final:')
 disp(final)
 [h,w]=freqz(A,B,'whole',256)
 plot(w,abs(h))
 grid on

else 
 %BLT
 [A,B]=bilinear(a,b,Fs)
 final = tf(A,B)
 [h,w]=freqz(A,B,'whole',1024)
 plot(w,abs(h))
 grid on
 
end


