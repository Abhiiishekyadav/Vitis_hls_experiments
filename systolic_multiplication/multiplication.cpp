#include <stdio.h>
#include <ap_int.h>
//Maximum Array Size
#define MAX_SIZE 16

//TRIPCOUNT identifier
const unsigned int c_size = MAX_SIZE;


typedef ap_int<8> int8 ;



extern "C" {
void mmult(  int8 *a, // Read-Only Matrix A
             int8 *b, // Read-Only Matrix B
           int8 *c,       // Output Result
           int8 a_row,    // Matrix A Row Size
           int8 a_col,    // Matrix A Col Size
           int8 b_col     // Matrix B Col Size
) {
   #pragma HLS INTERFACE m_axi port=a offset=slave bundle=gmem
   #pragma HLS INTERFACE m_axi port=b offset=slave bundle=gmem
   #pragma HLS INTERFACE m_axi port=c offset=slave bundle=gmem

   #pragma HLS INTERFACE s_axilite port=a bundle=control
   #pragma HLS INTERFACE s_axilite port=b bundle=control
   #pragma HLS INTERFACE s_axilite port=c bundle=control
   #pragma HLS INTERFACE s_axilite port=a_row bundle=control
   #pragma HLS INTERFACE s_axilite port=a_col bundle=control
   #pragma HLS INTERFACE s_axilite port=b_col bundle=control
   #pragma HLS INTERFACE s_axilite port=return bundle=control

    int8 b_row = a_col;
    int8 c_row = a_row;
    int8 c_col = b_col;

    // Local memory to store input and output matrices
    int8 localA[MAX_SIZE][MAX_SIZE];
   #pragma HLS ARRAY_PARTITION variable=localA dim=1 complete

    int8 localB[MAX_SIZE][MAX_SIZE];
   #pragma HLS ARRAY_PARTITION variable=localB dim=2 complete

    int8 localC[MAX_SIZE][MAX_SIZE];
#pragma HLS ARRAY_PARTITION variable = localC dim = 0 complete

// Burst reads on input matrices from global memory
// Read Input A
readA:
    for (int loc = 0, i = 0, j = 0; loc < a_row * a_col; loc++, j++) {
       #pragma HLS LOOP_TRIPCOUNT min=c_size*c_size max=c_size*c_size
       #pragma HLS PIPELINE II=1
        if (j == a_col) {
            i++;
            j = 0;
        }
        localA[i][j] = a[loc];
    }

// Read Input B
    readB:
        for (int loc = 0, i = 0, j = 0; loc < b_row * b_col; loc++, j++) {
    //#pragma HLS LOOP_TRIPCOUNT min = c_size* c_size max = c_size * c_size
            if (j == b_col) {
                i++;
                j = 0;
            }
            localB[i][j] = b[loc];
        }

systolic1:
    for (int k = 0; k < a_col; k++) {
       #pragma HLS LOOP_TRIPCOUNT min=c_size max=c_size
       #pragma HLS PIPELINE II=1
    int a_val;
    int b_val;
    int last ;
    systolic2:
        for (int i = 0; i < MAX_SIZE; i++) {
        systolic3:
            for (int j = 0; j < MAX_SIZE; j++) {

                // Get previous sum
            if(k == 0){
             last = 0;
            }
            else {
            last =localC[i][j];
            }
        //        int last = (k == 0) ? 0 : localC[i][j];

             if(i < a_row && k < a_col){

            a_val = localA[i][k] ;

             }else {
            a_val = 0;

             }
               // int a_val = (i < a_row && k < a_col) ? localA[i][k] : 0;
              if(k < b_row && j < b_col)
              {
             b_val =localB[k][j] ;

              }else
             b_val =0;
           //  int b_val = (k < b_row && j < b_col) ? localB[k][j] : 0;
                int result = last + a_val * b_val;

                // Write back results
                localC[i][j] = result;
            }
        }
    }

// Burst write from output matrices to global memory
// Burst write from matrix C
writeC:
    for (int loc = 0, i = 0, j = 0; loc < c_row * c_col; loc++, j++) {
       #pragma HLS LOOP_TRIPCOUNT min=c_size*c_size max=c_size*c_size
       #pragma HLS PIPELINE II=1
        if (j == c_col) {
            i++;
            j = 0;
        }
        c[loc] = localC[i][j];
    }
}
}
