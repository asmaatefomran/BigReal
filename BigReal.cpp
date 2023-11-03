#include <bits/stdc++.h>
#include "BigReal.h"
using namespace std;

BigReal :: BigReal(){
    sign = '+';
    integer = "0";
    fraction = ".0";
}

BigReal :: BigReal(string num){
    int start;
    if(num[0] == '-'){
        sign ='-'; start = 1;
    }
    else if (num[0] == '+'){
        sign ='+'; start = 1;
    }
    else{
        sign ='+'; start = 0;
    }
    int len = num.length();
    int point = -1;
    for(int i = start; i < len; i++){
        if(num[i] == '.'){
            point = i; fraction.push_back('.'); continue;
        }
        if(point == -1){
            integer.push_back(num[i]);
        }
        if(point != -1){
            fraction.push_back(num[i]);
        }
    }
    if(ValidReal(num)){
        cout <<"It's Real Number\n";
    }
    else cout <<"It's not a Real Number\n";

}

bool BigReal :: ValidReal (string num){
    int positive = 0, negative = 0, dot = 0, digit = 0, charct = 0;
    int len = num.length();
    int start;
    if(num[0] == '-'){
        negative++; start = 1;
    }
    else if (num[0] == '+'){
        positive++; start = 1;
    }
    else{
        positive++; start = 0;
    }
    for(int i = start; i < len; i++){
        if(num[i] == '+'){
            positive++;
        }
        else if(num[i] == '-'){
            negative++;
        }
        else if(num[i] == '.'){
            dot++;
        }
        else if(num[i]-'0' <= 9){
            digit++;
        }
        else if(num[i]-'0' > 9){
            charct++;
        }
    }
    // cout << charct << digit << dot << positive << negative;
    if(charct == 0 && digit >= 1 && dot <= 1 ){
        bool f1 = (positive <=1 && negative == 0);
        bool f2 = (negative == 1 && positive == 0);
        return (f1 || f2);
    }
    else return false;
}

void BigReal :: print(){
    cout << sign << integer << fraction <<"\n";
}

bool BigReal :: operator== (BigReal other){
    return (other.sign == sign  && other.integer == integer && other.fraction == fraction);
}
//----------------------------------------------------------------------------------------------------------------------
//operator overloading + to get the sum of two bigreals
BigReal BigReal :: operator+(BigReal &other) {
    BigReal temp;
    while(integer.size()>other.integer.size())'0'+other.integer;
    while(integer.size()<other.integer.size())'0'+integer;
    while(fraction.size()>other.fraction.size())other.fraction+'0';
    while(fraction.size()<other.fraction.size())fraction+'0';

}
