#pragma once
#include <iostream>

class HugeInt {
public:
    HugeInt(int x = 0);
    HugeInt(const char* value);
    HugeInt(const HugeInt& other);

    ~HugeInt();

    bool operator ==(const HugeInt& other) const;

    bool operator !=(const HugeInt& other) const;

    bool operator >(const HugeInt& other)const;

    bool operator <(const HugeInt& other)const;

    bool operator >=(const HugeInt& other) const;

    bool operator <=(const HugeInt& other) const;

    HugeInt& operator =(const HugeInt& other);
    HugeInt& operator =(const long);

    HugeInt operator + (const HugeInt& other) const;

    HugeInt operator ++(int);

    HugeInt Huge_abs() const;



    HugeInt operator-(const HugeInt& other) const;

    HugeInt operator *(const HugeInt& other)const;

    HugeInt operator /(const HugeInt& other)const;

    HugeInt operator %(const HugeInt& other)const;

    friend std::ostream& operator<<(std::ostream& os, HugeInt& other);
    friend std::istream& operator>>(std::istream& os, HugeInt& other);
//private:
    void new_length(int newLength, bool copy);
    void exp(int n);
private:
    char* array;
    bool sign;
    int length;

};
