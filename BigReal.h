// File: BigReal.h
// Author:  Maya Fouad        Asmaa Atef        Fatma Ibrahim
// ID:      20220270           20221020           20220242
// TA: Mohamed Talaat Saad Farrag
// Section: 19, 20
// Date: 4 Nov 2023
#ifndef BIGREAL_H
#define BIGREAL_H
#include <bits/stdc++.h>
using namespace std;
class BigReal{
private:
    char sign;
    string integer, fraction;
    static bool ValidReal (string);
public:
    BigReal();
    BigReal(double);
    BigReal(string);
    BigReal ( BigReal& other);
    BigReal& operator= (const BigReal& other);
    BigReal sum(const BigReal n1, BigReal n2);
    BigReal sub(const BigReal n1, BigReal n2);
    BigReal  operator+(const BigReal& other);
    BigReal  operator-(const BigReal& other);
    bool operator<(BigReal& r) ;
    bool operator>(BigReal& r)  ;
    bool operator== (BigReal other);
    void print();
    void same_len(BigReal& other);
    friend ostream &operator << (ostream &out , BigReal num) ;

};

#endif
