#include <iostream>
using namespace std;

template <typename T> T* sort (T* arr, int len)
{
    T *sort = new T[len];
    for(int i=0; i<len; i++) {
        sort[i] = arr[i];
    }
    T k;
    for(int i=0; i<len; i++) {
        for (int j=len-1; j>i; j--) {
            if (sort[j]>sort[j-1]) {
                k = sort[j-1];
                sort[j-1] = sort[j];
                sort[j] = k;
            }
        }
    }
    return sort;
}



int main(int argc, char **argv)
{
    int arr[7]= {12,13,57665,3,-14,13,123212};
    int *m = sort(arr, 7);

    for(int i=0; i<7; i++) {
        cout << m[i] << endl;
    }
    delete[] m;
    
    cout << " " << endl;

    double array[5] = {-12.3, 1.2e15, 3434.5, -9.09e-3, 1.0e20};
    double *M = sort(array,5);

    for(int i=0; i<5; i++) {
        cout << M[i] << endl;
    }
    delete[] M;

    return 0;
}
