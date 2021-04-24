#include <iostream>
using namespace std;
#include <string>
#include <array>
#include <cmath>

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
    superlong<N> operator*(const superlong<N>& s)const;
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
superlong<N> superlong<N>::operator*(const superlong<N>& s)const
{
    superlong<N> s1(*this);
    superlong<N> s2(s);
    auto r1 = s1.toHex();
    auto r2 = s2.toHex();
    int k1 = 0;
    int k2 = 0;
    while (r1[k1] == '0') {
        k1++;
    }
    while (r2[k2] == '0') {
        k2++;
    }
    string n_s1 = "";
    string n_s2 = "";
    for (k1; k1<r1.length(); k1++) {
        n_s1.insert(n_s1.begin(), r1[k1]);
    }
    for (k2; k2<r2.length(); k2++) {
        n_s2.insert(n_s2.begin(), r2[k2]);
    }
    string Alfa = "0123456789abcdef";
    int len1 = n_s1.length();
    int len2 = n_s2.length();
    int len;
    if (len1 > len2) {
        len = len1*2+1;
    } else {
        len = len1*2+1;;
    }
    int proizv[len] = {0};
    int mas_ch1[len1];
    int mas_ch2[len2];
    for (int i=0; i<len1; i++) {
        int k1 = 0;
        while (Alfa[k1] != n_s1[i]) {
            k1++;
        }
        mas_ch1[i] = k1;
    }
    for (int i=0; i<len2; i++) {
        int k2 = 0;
        while (Alfa[k2] != n_s2[i]) {
            k2++;
        }
        mas_ch2[i] = k2;
    }
    for (int i=0; i<len1; i++) {
        for (int j=0; j<len2; j++) {
            proizv[i+j] = (proizv[i+j] + (mas_ch1[i]*mas_ch2[j]));
        }
    }
    for (int i=0; i<len; i++) {
        proizv[i+1]=proizv[i+1]+proizv[i]/16;
        proizv[i] = proizv[i]%16;
    }
    int k = 0;
    while (proizv[k] == 0) {
        k++;
    }
    string kon_str = "";
    for (k; k<len; k++) {
        kon_str.insert(kon_str.begin(), Alfa[proizv[k]]);
    }
    return kon_str;
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
    superlong<SZ> num1;
    superlong<SZ> num2("bec15ad12");
    superlong<SZ> num3("4993bfe12");
    num1 = num3;
    num1 = num1 * num2;
    std::cout<<num3<<std::endl;
    std::cout<<num2<<std::endl;
    std::cout<<num1<<std::endl;
    return 0;
}
