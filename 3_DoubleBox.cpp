#include <iostream>
using namespace std;
#include <string>

template <typename T1, typename T2> class DoubleBox
{
private:
    T1 content1 = T1(); // инициализация атрибута при объявлении, стандарт C++11
    T2 content2 = T2();
public:
    DoubleBox() {}
    DoubleBox(const T1 value1, const T2 value2):content1(value1), content2(value2) {}
    T1 getContent1() const
    {
        return content1;
    }
    void setContent1(const T1 value1)
    {
        content1 = value1;
    }
    T2 getContent2() const
    {
        return content2;
    }
    void setContent2(const T2 value2)
    {
        content2 = value2;
    }
};


int main(int argc, char **argv)
{
    DoubleBox<double, string> Box1(3.45, "hello");
    cout<<Box1.getContent1()<<endl;
    cout<<Box1.getContent2()<<endl;
    Box1.setContent1(25.3);
    Box1.setContent2("world");
    cout<<Box1.getContent1()<<endl;
    cout<<Box1.getContent2()<<endl;

    return 0;
}
