#include <iostream>

void mmult( int *a, // Read-Only Matrix A
          int *b, // Read-Only Matrix B
        int *c,       // Output Result
        int a_row,    // Matrix A Row Size
        int a_col,    // Matrix A Col Size
        int b_col ) ;

int main() {
    int a_row = 3;
    int a_col = 3;
    int b_col =3;

    int a[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int b[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int c[3][3] = {0};

    mmult(&a[0][0], &b[0][0], &c[0][0],a_row,a_col,b_col);

    std::cout << "Result:" << std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << c[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

void mmult( int *a,
          int *b,
        int *c,
        int a_row,
        int a_col,
        int b_col ) {

    for (int i=0; i<a_row; i++) {
        for (int j=0; j<b_col; j++) {
            *(c+i*b_col+j) = 0;
            for (int k=0; k<a_col; k++) {
                *(c+i*b_col+j) += *(a+i*a_col+k) * *(b+k*b_col+j);
            }
        }
    }
}
