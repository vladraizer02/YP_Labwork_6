#include <iostream>
using namespace std;

class Rectangle
{
private:
    int height;
    int width;
public:
    Rectangle():height(0), width(0) {}
    Rectangle(int h, int w):height(h), width(w) {}
    int getSquare()
    {
        return height*width;
    }
    
    friend bool operator> (Rectangle s1, Rectangle s2);
};

bool operator>(Rectangle s1, Rectangle s2)
{
    return s1.getSquare() > s2.getSquare();
}

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
    Rectangle a(2, 3);
    Rectangle b(6, 4);
    Rectangle c(1, 1);

    Rectangle arr[3] = {a, b, c};
    Rectangle *m = sort(arr, 3);

    for(int i=0; i<3; i++) {
        cout << m[i].getSquare() << endl;
    }

    return 0;
}
