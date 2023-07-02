
#include <stdio.h>
#include <math.h>
#include "ap_int.h"
#define BIAS 7
typedef ap_int<8> int8;
void exp_cal(int ,int * ,int *, int *, int8 * , int);
void  cal(int result, int *out, int *sum, int *i) {
    while (result != 0) {
        *out = result % 2;
        *sum = *sum + (*out) * pow(10, (*i));
        result = result / 2;
        (*i)++;
    }
    //return sum ;
}

void exp_cal(int result, int *out, int *sum, int *i, int8 *FP_8, int l) {
    while (result != 0) {
        *out = result % 2;
        FP_8[l] = *out;
        *sum = *sum + (*out) * pow(10, (*i));
        result = result / 2;
        (*i)++;
        l--;
    }
    //return sum ;
}
#pragma hls_design top
void convert_to_float_point(float num, int8 FP_8[8]) {
//#pragma HLS INTERFACE s_axilite port=num bundle=CTRL_BUS
  // #pragma HLS INTERFACE s_axilite port=FP_8 bundle=CTRL_BUS
#pragma HLS INTERFACE ap_none port=num
#pragma HLS INTERFACE ap_none port=FP_8[8]


#pragma HLS INTERFACE ap_ctrl_none port=return
    int jj;
    for (jj = 0; jj <= 7; jj++) {
    	  FP_8[jj] = 0;
    }

    int result = floor(num);
    float part = num - floor(num);

    if (num < 0) {
        FP_8[0] = 1;
    } else {
    	   FP_8[0] = 0;
    }

    int sum = 0;
    int i = 0;
    int out;
    int floor_bin;
    cal(result, &out, &sum, &i);
    floor_bin = sum;

    float partt;
    float j = 0.1;
    float summ = 0;
    for (i = 1; i <= 10; i++) {
        if (part == 1) {
            summ = summ + partt * j;
            break;
        } else {
            part = part * 2;
            partt = floor(part);
            part = part - partt;
            summ = summ + partt * j;
            j = j / 10;
        }
    }

    float mmmm = floor_bin + summ;
    int n_1 = floor(mmmm);
    float m_1;
    int exponent;

    if ((n_1 / 1 == 10) || (n_1 / 1 == 11)) {
        m_1 = mmmm / 10;
        exponent = BIAS + 1;
        goto come_here;
    }

    if ((n_1 / 1 == 100) || (n_1 / 1 == 101) || (n_1 / 1 == 110) || (n_1 / 1 == 111)) {
        m_1 = mmmm / 100;
        exponent = BIAS + 2;
        goto come_here;
    }

    if ((n_1 / 1 == 1000) || (n_1 / 1 == 1001) || (n_1 / 1 == 1010) || (n_1 / 1 == 1011) || (n_1 / 1 == 1100) || (n_1 / 1 == 1101) || (n_1 / 1 == 1110) || (n_1 / 1 == 1111)) {
        m_1 = mmmm / 1000;
        exponent = BIAS + 3;
        goto come_here;
    }  else if(n_1/1 == 1)
{
	m_1 = mmmm/1;
	exponent = BIAS;
	goto come_here;
}
else if(n_1/1 == 0)
{
	m_1 = mmmm *10;
   	n_1 = floor(m_1);
   	if(n_1/1 == 1)
   	{
   		exponent = BIAS - 1;
   		goto come_here;
	   }


	m_1 = mmmm *100;
   	n_1 = floor(m_1);

	   if(n_1/1 == 1)
   	{
   		exponent = BIAS -2;
   		goto come_here;
	   }

	m_1 = mmmm *1000;
   	n_1 = floor(m_1);

	   if(n_1/1 == 1)
   	{
   		exponent = BIAS - 3;
   		goto come_here;
	   }

	m_1 = mmmm *10000;
   	n_1 = floor(m_1);

	   if(n_1/1 == 1)
   	{
   		exponent = BIAS - 4;
   		goto come_here;
	   }
}

come_here :
int final = m_1 * 1000;
out = 0;
i = 0;
sum = 0;
int l = 4;
 exp_cal(exponent,&out,&sum,&i,FP_8 ,l);

 jj = 7;
for(int kk=0;kk<=2;kk++)
{
	int o_t = final%10;
	final = final/10;

	FP_8[jj] = o_t;
	--jj;
}
}

