#include <iostream>
using namespace std;
#include <string>
#include <array>

template <size_t N> class superlong
{
private:
    static constexpr size_t SIZE = N / 32 + (N % 32 != 0);
    std::array<uint32_t, N / 32 + (N % 32 != 0)> value;
    static std::string toHex(uint32_t u);
    std::string toHex();
public:
    superlong():value(
    {
        0
    }) {}
    superlong(const std::array<uint32_t, N / 32 + (N % 32 != 0)>& v):value(v) {}
    superlong(const std::string & s);
    superlong<N>& operator=(const superlong<N>& s);
    superlong<N> operator+(const superlong<N>& s)const;
    template <size_t X>
    friend std::ostream& operator<< (std::ostream& stream, superlong<X>& s);
};

template <size_t N>
superlong<N>::superlong(const std::string& s)
{
    int len = s.length();
    string Alfa = "0123456789abcdef";
    try {
        for (int i = 1; i<len; i++) {
            if (Alfa.find(s[i]) == string::npos) {
                throw invalid_argument("");
            }
        }
    } catch (invalid_argument) {
        cerr << "Invalid_argument" << endl;
        exit(1);
    }
    value= {0};
    int i = 0;
    auto ptr_2 = s.end();
    auto ptr_b = s.begin();
    while (ptr_b != ptr_2) {
        auto ptr_1 = ptr_2 - 8;
        if (ptr_1 < ptr_b)
            ptr_1 = ptr_b;
        value[i] = stoul(std::string(ptr_1,ptr_2),0,16);
        ptr_2 = ptr_1;
        i++;
    }
}

template <size_t N>
superlong<N>& superlong<N>::operator=(const superlong<N>& s)
{
    value = s.value;
    return *this;
}

template <size_t N>
superlong<N> superlong<N>::operator+(const superlong<N>& s)const
{
    superlong<N> sum;
    uint32_t CF=0;
    for (size_t i=0; i<SIZE; i++) {
        sum.value[i] = CF + value[i] + s.value[i];
        if (sum.value[i]<value[i])
            CF = 1;
        else
            CF = 0;
    }
    return sum;
}

template <size_t N>
std::string superlong<N>::toHex(uint32_t u)
{
    const char d[]="0123456789abcdef";
    std::string s;
    for (int i=0; i<8; i++) {
        s = d[u & 0xf]+s;
        u >>=4;
    }
    return s;
}

template <size_t N>
std::string superlong<N>::toHex()
{
    std::string s;
    for (auto e:value)
        s=superlong<N>::toHex(e) + s;
    return s;
}

template <size_t X>
std::ostream& operator<<(std::ostream& stream, superlong<X>& s)
{
    stream<<s.toHex();
    return stream;
}

int main(int argc, char **argv)
{
    const size_t SZ = 512;
    superlong<SZ> num1("abc");
    superlong<SZ> num2("abr");
    std::cout<<num1<<std::endl;
    std::cout<<num2<<std::endl;
    return 0;
}
