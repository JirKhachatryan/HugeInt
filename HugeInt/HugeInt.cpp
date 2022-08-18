#include "HugeInt.h"
#include <iostream>
#include <cmath>
#include <string>

HugeInt::HugeInt(int x) :length(1) {
    array = new char[length];
    array[0] = 0;

    if (x == 0) {
        sign = 0;
    }
    else {
        if (x < 0)
            sign = 1;
        else
            sign = 0;

        int k = abs(x);

        length = 0;
        while (k != 0) {
            k = k / 10;
            length++;
        }

        new_length(length, true);
        k = abs(x);
        for (int i = length - 1; i >= 0; i--) {
            array[i] = static_cast<char>(abs(k % 10));
            k /= 10;
        }

    }
}
HugeInt::HugeInt(const char* value) {
    bool errorFound = false;
    int len = 0;
    if (value[0] == '-') {
        sign = true;
        ++len;
    }
    else {
        sign = false;
    }

    while (value[len]) {
        if (value[len] < '0' || value[len] >'9') {
            errorFound = true;
        }
        ++len;
    }
    
    if (errorFound) {
        std::cout << "Error! Inexorable symbol. Please enter only numbers"<<std::endl;
        std::cin >> *this;
    }
    else {
        length = len - (sign ? 1 : 0);
        new_length(length, false);
        //********************
        //array = new char[length];
       // memcpy(array, value + (sign ? 1 : 0), length);
        for (int i = 0; i < length; ++i) {
            array[i] = value[i+ (sign ? 1 : 0)]-'0';
        }
    }
}
HugeInt::HugeInt(const HugeInt& other) {
    sign = other.sign;
    length = other.length;
    array = new char[length];
    memcpy(array, other.array, length);
}


HugeInt::~HugeInt()
{
    delete[] array;
    array = nullptr;
    length = 0;
}


HugeInt HugeInt::Huge_abs() const {
    HugeInt x;
    x.new_length(length, false);
    memcpy(x.array,array, length);
    x.sign = false;
    return x;
}



void HugeInt::new_length(int newLength, bool copy)
{
    char* newarray = new char[newLength];
    memset(newarray, 0, newLength);

    if (copy) {
        int diff = newLength - length;
        if (diff >= 0) {
            memcpy(newarray + diff, array, length);
        }
        else {
            memcpy(newarray, array - diff, newLength);
        }
    }

    std::swap(newarray, array);
    delete[] newarray;
    length = newLength;
}



HugeInt& HugeInt::operator =(const HugeInt& other) {
    if (&other != this) {
        sign = other.sign;
        new_length(other.length, false);
        memcpy(array, other.array, other.length);
    }

    return *this;
}

HugeInt& HugeInt::operator =(const long x) {
    if (x == 0) {
        new_length(1, false);
        sign = false;
        return *this;
    }
    int k = abs(x);
    length = 0;
    while (k != 0) {
        k = k / 10;
        length++;
    }

    new_length(length, true);
    k = abs(x);
    for (int i = length - 1; i >= 0; i--) {
        array[i] = static_cast<char>(abs(k % 10));
        k /= 10;
    }
    sign = (x >= 0 ? false : true);
    return *this;
}

std::ostream& operator<<(std::ostream& os, HugeInt& thiz) {
    if (thiz.sign) {
        os << "*";
    }
    for (int i = 0; i < thiz.length; i++) {
        auto a = thiz.array[i];
        os << (int)a<<" ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, HugeInt& other) {
    std::string s;
    is >> s;
    HugeInt hg(s.c_str());
    other = hg;
    return is;
}

bool HugeInt::operator ==(const HugeInt& other)const {
    if (sign != other.sign) { return false; }
    if (length != other.length) { return false; }

    for (int i = 0; i < length; i++) {
        if (array[i] != other.array[i]) {
            return false;
        }
    }
    return true;
}

bool HugeInt::operator !=(const HugeInt& other) const {
    return !(other == *this);
}

bool HugeInt::operator >(const HugeInt& other)const {
    //********************
    if (sign != other.sign) return (sign < other.sign);
    if (length > other.length) return !sign;
    if (length < other.length) return sign;

    for (int i = 0; i < length; i++) {
        if (array[i] > other.array[i]) return !sign;
        if (array[i] < other.array[i]) return sign;
    }
    return false;
}

bool HugeInt::operator <(const HugeInt& other)const {
    return (other > *this);
}

bool HugeInt::operator >=(const HugeInt& other) const {
    return !(other > *this);
}

bool HugeInt::operator <=(const HugeInt& other)const {
    return !(*this > other);
}




HugeInt HugeInt::operator +(const HugeInt& other) const {
    HugeInt x;
    HugeInt y;
    if (sign == other.sign) {
    x = *this;
    y = other;
    }else {
        if (Huge_abs() == other.Huge_abs()) {
            x = 0;
            return x;
        }
        else {
            x = Huge_abs() - other.Huge_abs();
            x.sign = (Huge_abs() > other.Huge_abs() ? sign : other.sign);
            return x;
        }
    }
    x.new_length(std::max(length, other.length)+1 , true);
    y.new_length(std::max(length, other.length)+1, true);

   for (int i = x.length - 1; i >= 0; i--) {
                x.array[i] += y.array[i];
            }

    for (int i = x.length - 1; i >= 0; i--) {
        
        if (x.array[i] > 9) {
            x.array[i] -= 10;
            x.array[i - 1]++;
        }
    }
       
    if (x.array[0] == 0) {
        x.new_length(x.length - 1, true);
    }

    return x;
}

HugeInt HugeInt::operator ++(int) {
    array[length - 1] += 1;
    for (int i = length - 1; i > 0; i--) {
        if (array[i] > 9) {
            array[i] -= 10;
            array[i - 1]++;
        }
    }
    if (array[0] > 9) {
        new_length(length + 1, true);
        array[1] -= 10;
        array[0]++;
    }
    return *this;
}



HugeInt HugeInt::operator-(const HugeInt& other) const {
    HugeInt x;
    HugeInt y;

    if (sign != other.sign) {
        x = (Huge_abs() + other.Huge_abs());
        x.sign = sign;
        return x;
    }

    if (*this == other){
        return x;
    }
        if (Huge_abs() < other.Huge_abs()) {
        x = other - *this;
        x.sign = !x.sign;
        return x;
    }
    x = *this;
    y = other;
        x.new_length(std::max(length, other.length) + 1, true);
        y.new_length(std::max(length, other.length) + 1, true);
    
        for (int i = x.length - 1; i >= 0; i--) {
            x.array[i] -= y.array[i];
        }
        for (int i = x.length - 1; i > 0; i--) {
            if (x.array[i] < 0) {
                x.array[i] += 10;
                x.array[i - 1]--;
            }
        }
     
        while (x.array[0] == 0) {
            x.new_length(x.length - 1, true);
        }
        x.sign = sign;
        
        return x;
}


HugeInt HugeInt::operator *(const HugeInt& other)const {
    HugeInt x;
    x.new_length(length + other.length, false);
    x.sign = !(sign == other.sign);
    
   
    for (int i = length - 1; i >= 0; i--) {
        for (int j = other.length - 1; j >= 0; j--) {
            x.array[i + j + 1] += array[i] * other.array[j];
            if (x.array[i+j+1] > 9) {
                x.array[i+j] += x.array[i+j+1] / 10;
                x.array[i+j+1] %= 10;
            }
        }
    }
    
    while (x.array[0] == 0 && x.length>1) {
        x.new_length(x.length - 1, true);

    }
    return x;
}

HugeInt HugeInt::operator /(const HugeInt& other)const {
    HugeInt x(0);
    if (Huge_abs() < other.Huge_abs()) {
        return x;
    }
    HugeInt a;
    a = *this;
    while (a >= other) {
        a = a - other;
        x++;
    }
    return x;
}

HugeInt HugeInt::operator %(const HugeInt& other)const {
    HugeInt a;
    a = *this;
    while (a >= other) {
        a = a - other;
    }
    return a;
}

