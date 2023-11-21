#include <stdio.h>
#include<stdlib.h>

float calculate_ssr(float l0, float t, float s, float g, float bestssr, int *student_id, int *correct, int rows)
{
    float ssr=0.0;
    float likelihoodcorrect=0.0;
    float prevLgivenresult=0.0;
    float prevL=0.0;
    float newL=0.0;
    int prevstudent=0;

    for (int i=0; i<rows; i++){
        if(student_id[i]!=prevstudent){
            prevL=l0;
            prevstudent=student_id[i];
        }

        likelihoodcorrect = (prevL * (1.0 - s)) + ((1.0 - prevL) * g);
        ssr += (correct[i] - likelihoodcorrect) * (correct[i] - likelihoodcorrect);

        if(ssr>bestssr){
            return ssr;
        }

        if(correct[i]==1){
            prevLgivenresult = ((prevL * (1.0 - s)) / ((prevL * (1 - s)) + ((1.0 - prevL) * (g))));
        }
        else{
            prevLgivenresult = ((prevL * (s)) / ((prevL * (s)) + ((1.0 - prevL) * (1.0 - g))));
        }

        newL = prevLgivenresult + (1.0 - prevLgivenresult) * t;
        prevL = newL;
    }

    return ssr;
}

float* get_bkt_par_c(int *student_id_c, int *right_c, int rows)
{
    float bestL0 = 0.0;
    float bestT = 0.0;
    float bestG = 0.0;
    float bestS = 0.0;
    float SSR = 0.0;
    float bestSSR = 9999999.0;

    float startL0, startT, startG, startS;

    for (float L0 = 0.01; L0 <= 0.99; L0 += 0.01) {
        for (float T = 0.01; T <= 0.99; T += 0.01) {
            for (float G = 0.01; G <= 0.3; G += 0.01) {
                for (float S = 0.01; S <= 0.3; S += 0.01) {
                    SSR = calculate_ssr(L0, T, S, G, bestSSR, student_id_c, right_c, rows);
                    if (SSR < bestSSR) {
                        bestSSR = SSR;
                        bestL0 = L0;
                        bestT = T;
                        bestS = S;
                        bestG = G;
                    }
                }
            }
        }
    }

    startL0=bestL0;
    startT=bestT;
    startS=bestS;
    startG=bestG;

    for (float L0=startL0-0.009; L0<=startL0+0.009; L0+=0.001) {
        if (L0>=0.99){break;}
        for (float T=startT-0.009; T<=startT+0.009; T+=0.001) {
            if (T>=0.99){break;}
            for (float G=startG-0.009; G<=startG+0.009; G+=0.001) {
                if (G>=0.3){break;}
                for (float S=startS-0.009; S<=startS+0.009; S+=0.001) {
                    if (S>=0.3){break;}
                    SSR = calculate_ssr(L0, T, S, G, bestSSR, student_id_c, right_c, rows);
                    if (SSR < bestSSR) {
                        bestSSR = SSR;
                        bestL0 = L0;
                        bestT = T;
                        bestS = S;
                        bestG = G;
                    }
                }
            }
        }
    }   

    float* parameters_c = (float*) malloc(4*sizeof(float*));
    parameters_c[0]=bestL0;
    parameters_c[1]=bestT;
    parameters_c[2]=bestS;
    parameters_c[3]=bestG;
    
    return parameters_c;
}

void free_memory(float *parameters_c)
{
    free(parameters_c);
}
