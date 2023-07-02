#include <iostream>
#include "ap_int.h"
using namespace std;
typedef ap_int<8> int8;

void convert_to_float_point(float num, int8 *FP_8);

int main() {
    float num = 12.5;
    int8 FP_8[8] = {0};

    convert_to_float_point(num, FP_8);

    cout << "Float value: " << num << endl;
    cout << "Binary representation: ";
    for (int i = 0; i < 8; i++) {
        cout << FP_8[i];
    }
    cout << endl;

    return 0;
}
