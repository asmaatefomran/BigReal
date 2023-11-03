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
    BigReal(string);
    BigReal();
    BigReal (const BigReal& other);
    BigReal operator= (BigReal& other);
    BigReal operator+ (BigReal& other); 
    BigReal operator- (BigReal& other); 
    bool operator<  (BigReal other);
    bool operator>  (BigReal other);
    bool operator== (BigReal other);
    void print();
    void same_len(BigReal& other);

};

#endif
