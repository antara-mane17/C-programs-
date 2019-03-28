
 
/*       
	AUTHOR  : Komal Mane
	HPF-LPF
*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>


selector = strtod(input("0 for HPF, 1 for LPF: ", "string"))
if selector < 1 then    // High Pass Filter
    Ap = strtod(input("Enter pass band attenuation Ap: ", "string"))
    As = strtod(input("Enter stop band attenuation As: ", "string"))
    Wp = strtod(input("Enter pass band frequency Wp: ", "string"))
    Ws = strtod(input("Enter stop band frequency Ws: ", "string"))
    F = strtod(input("Enter sampling frequency F: ", "string"))
    1
    OmegaP = 2*F*tan(Wp/2)
    OmegaS = 2*F*tan(Ws/2)

    //Calculate Filter Order
    N = ceil(log10(sqrt((10^(As/10) - 1)/(10^(Ap/10) - 1)))/log10(OmegaP/OmegaS))

    disp("Filter Order: ")
    disp(N)

    OmegaC = OmegaP/(10^(Ap/10) - 1)^(1/(2*N))

    disp("OmegaC: ")
    disp(OmegaC)

    Fc = 2*atan(OmegaC/(2*F))/(2*%pi)

    disp("Fc:  ")
    disp(Fc)

    H_z = iir(N, 'hp', 'butt', Fc, [])

    disp("Hz: ")
    disp(H_z)

    point_count = 1024
    [xm,fr]=frmag(H_z, point_count)
    plot(fr, xm)
    xtitle('Discrete IIR filter: High Pass');
    
else    //Low Pass Filter
    Ap = strtod(input("Enter pass band attenuation Ap: ", "string"))
    As = strtod(input("Enter stop band attenuation As: ", "string"))
    Wp = strtod(input("Enter pass band frequency Wp: ", "string"))
    Ws = strtod(input("Enter stop band frequency Ws: ", "string"))
    F = strtod(input("Enter sampling frequency F: ", "string"))

    OmegaP = 2*F*tan(Wp/2)
    OmegaS = 2*F*tan(Ws/2)

    //Calculate Filter Order

    N = ceil(log10(sqrt((10^(As/10) - 1)/(10^(Ap/10) - 1)))/log10(OmegaS/OmegaP))

    disp("Filter Order: ")
    disp(N)

    OmegaC = OmegaP/(10^(Ap/10) - 1)^(1/(2*N))

    disp("OmegaC: ")
    disp(OmegaC)

    Fc = 2*atan(OmegaC/(2*F))/(2*%pi)

    disp("Fc:  ")
    disp(Fc)

    H_z = iir(N, 'lp', 'butt', Fc, [])

    disp("Hz: ")
    disp(H_z)

    point_count = 1024
    [xm,fr]=frmag(H_z, point_count)
    plot(fr, xm)
    xtitle('Discrete IIR filter: Low Pass');
end

Fp = Wp/(2*%pi)
disp("Fp: ")
disp(Fp)
Fs = Ws/(2*%pi)
disp("Fs: ")
disp(Fs)

for i = 1:(point_count - 1)
    if (fr(i) < Fp) && (fr(i+1) >= Fp) then
        Ap_obs = log10(xm(i))*20
        disp("Ap_observed: ")
        disp(Ap_obs)   
    end

    if (fr(i) < Fs) && (fr(i+1) >= Fs) then
        As_obs = log10(xm(i))*20
        disp("As_observed: ")
        disp(As_obs)    
    end 
end






