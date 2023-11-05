// File: BigReal.cpp
// Author:  Maya Fouad        Asmaa Atef        Fatma Ibrahim
// ID:      20220270           20221020           20220242
// TA: Mohamed Talaat Saad Farrag
// Section: 19, 20
// Date: 4 Nov 2023
#include <bits/stdc++.h>
#include "BigReal.h"
using namespace std;

BigReal :: BigReal(){
    sign = '+';
    integer = "0";
    fraction = ".0";
}

BigReal :: BigReal(double number){
    string num = to_string(number);
    num.pop_back();
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

}

BigReal :: BigReal(string num){

    if(!ValidReal(num)){
        cout << "It's not a Real Number\n";
        num = "0.0";
    }

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


}

BigReal :: BigReal ( BigReal& other){
    sign = other.sign;
    integer = other.integer;
    fraction = other.fraction;
}

BigReal& BigReal :: operator= (const BigReal& other){
    BigReal ob=*this;
    sign = other.sign;
    integer = other.integer;
    fraction = other.fraction;
    return *this;
}

bool BigReal :: ValidReal (string num){
    int positive = 0, negative = 0, dot = 0, digit = 0, charct = 0;
    int len = num.length();

    for(int i = 0; i < len; i++){
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
    if(sign == '-') cout << sign ;
    cout << integer << fraction <<"\n";
}

void BigReal :: same_len(BigReal& other){
    int len = max(integer.length(), other.integer.length());
    int len1 = integer.length();
    int len2 = other.integer.length();
    for(int i = len1; i < len; i++){
        integer = "0" + integer;
    }
    for(int i = len2; i < len; i++){
        other.integer = "0" + other.integer;
    }

    int f = max(fraction.length(), other.fraction.length()) ;
    int f1 = fraction.length() ;
    int f2 = other.fraction.length() ;
    for(int i = f1; i < f; i++){
        fraction.push_back('0');
    }
    for(int i = f2; i < f; i++){
        other.fraction.push_back('0');
    }
}

bool BigReal :: operator== (BigReal other){
    return (other.sign == sign  && other.integer == integer && other.fraction == fraction);
}
//----------------------------------------------------------------------------------------------------------------------
//function to do basic addition between two bigreals with the same sign
BigReal BigReal :: sum(const  BigReal n1, BigReal n2){
    int reminder=0;
    BigReal ans;
    ans.integer.clear();
    ans.fraction.clear();
    //sum the fractions
    for(int i= n1.fraction.size()-1;i>=1 ;i--){
        reminder= (n1.fraction[i]-'0')+(n2.fraction[i]-'0')+reminder;
        ans.fraction= char((reminder%10)+'0')+ans.fraction;
        reminder/=10;
    }
    ans.fraction= '.'+ans.fraction;
    //sum the integers
    for(int i= n1.integer.size()-1;i>=0 ;i--){
        reminder= (n1.integer[i]-'0')+(n2.integer[i]-'0')+reminder;
        ans.integer= char((reminder%10)+'0')+ans.integer;
        reminder/=10;
    }
    if(reminder)ans.integer='1'+ans.integer;
    return ans;
}
//----------------------------------------------------------------------------------------------------------------------
//function to do basic substraction between two bigreals with the same sign
BigReal BigReal :: sub(const BigReal n1, BigReal n2){
    int carry=0;
    BigReal ans;
    ans.integer.clear();
    ans.fraction.clear();
    //substracte the fractions
    for(int i= n1.fraction.size()-1 ;i>=1;i--){
        int a=(n1.fraction[i]-'0')-(n2.fraction[i]-'0')-carry;
        if(a<0) {
            carry = 1;
            a += 10;
        }
        else carry=0;
        ans.fraction=char(a+'0')+ans.fraction;
    }
    ans.fraction= '.'+ans.fraction;
    //substracte the integers
    for(int i= n1.integer.size()-1 ;i>=0;i--){
        int a=(n1.integer[i]-'0')-(n2.integer[i]-'0')-carry;
        if(a<0) {
            carry = 1;
            a += 10;
        }
        else carry=0;
        ans.integer=char(a+'0')+ans.integer;
    }
    return ans;
}
//----------------------------------------------------------------------------------------------------------------------
//operator overloading + to get the sum of two bigreals
BigReal BigReal :: operator+(const BigReal& otherr) {
    BigReal temp;
    BigReal now, other;
    other = otherr;
    same_len(other);
    now = *this;

    if (now.sign == other.sign) {
        temp= sum(now, other);
        //temp.sign = now.sign;
    }
    else if (now.sign == '-' && other.sign == '+') {
        if (other.integer >= now.integer || (other.integer == now.integer && other.fraction >= now.fraction)) {
            temp = sub(other, now);
            temp.sign = '+';
        } else {
            temp = sub(now, other);
            temp.sign = '-';
        }
    }
    else if (now.sign == '+' && other.sign == '-') {
        if (other.integer > now.integer || (other.integer == now.integer && other.fraction > now.fraction)) {
            temp = sub(other, now);
            temp.sign = '-';
        }
        else {
            temp = sub(now, other);
            temp.sign = '+';
        }
    }
    return temp;
}
//----------------------------------------------------------------------------------------------------------------------
//operator overloading + to get the sum of two bigreals
BigReal BigReal :: operator-(const BigReal& otherr) {
    BigReal temp;
    BigReal now, other;
    other = otherr;
    same_len(other);
    now = *this;

    if (now.sign =='-' &&other.sign=='+') {
        temp = sum(now, other);
        temp.sign = '-';
    }
    else if (now.sign =='+' &&other.sign=='-') {
        temp = sum(now, other);
        temp.sign = '+';
    }
    else if (now.sign == other.sign &&other.sign== '+') {
        if (now.integer >= other.integer || (now.integer == other.integer && now.fraction >= other.fraction)) {
            temp = sub(now, other);
            temp.sign = '+';
        }
        else {
            temp =sub(other,now);
            temp.sign='-';
        }
    }
    else if (now.sign == other.sign && other.sign== '-') {
        if (now.integer > other.integer || (now.integer == other.integer && now.fraction > other.fraction)) {
            temp = sub(now, other);
            temp.sign = '-';
        }
        else {
            temp =sub(other,now);
            temp.sign='+';
        }
    }
    return temp;

}
bool BigReal ::operator>( BigReal& r) {
    same_len(r) ;
    integer = sign + integer ;
    r.integer = r.sign + r.integer ;
    if(integer[0] == '-' and r.integer[0] == '+') return false ;
    if(integer[0] == '+' and r.integer[0] == '-') return true ;
    if(integer == r.integer and fraction == r.fraction) return false ;
    for(int i = 1 ; i < integer.size() ; ++i){
        if(integer[i] > r.integer[i]) return true ;
        else if(integer[i] < r.integer[i]) return false ;
    }
    for(int i = 1 ; i < fraction.size() ; ++i){
        if(fraction[i] > r.integer[i]) return true ;
        else if(integer[i] < r.integer[i]) return false ;
    }
    return true ;
}
bool BigReal ::operator<( BigReal& r)  {
    same_len(r) ;
    integer = sign + integer ;
    r.integer = r.sign + r.integer ;
    if(integer[0] == '-' and r.integer[0] == '+') return true ;
    if(integer[0] == '+' and r.integer[0] == '-') return false ;
    if(integer == r.integer and fraction == r.fraction) return true ;
    for(int i = 1 ; i < integer.size() ; ++i){
        if(integer[i] > r.integer[i]) return false ;
        else if(integer[i] < r.integer[i]) return true ;
    }
    for(int i = 1 ; i < fraction.size() ; ++i){
        if(fraction[i] > r.integer[i]) return false ;
        else if(integer[i] < r.integer[i]) return true ;
    }
    return false ;
}
ostream &operator << (ostream &out , BigReal num){
    if(num.sign == '-') cout << num.sign ;
    out << num.integer << num.fraction << endl;
    return out ;
}
