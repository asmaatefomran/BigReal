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
    cout << num <<"\n";
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
    cout << sign << integer << fraction <<"\n";
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
    //substracte the fractions
    for(int i= n1.fraction.size()-1 ;i>=0;i--){
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
    BigReal temp,now,other;
    other=otherr;
    now.sign=sign;
    now.integer=integer;
    now.fraction=fraction;

    while(now.integer.size()>other.integer.size())'0'+other.integer;
    while(now.integer.size()<other.integer.size())'0'+now.integer;
    while(now.fraction.size()>other.fraction.size())other.fraction+'0';
    while(now.fraction.size()<other.fraction.size())now.fraction+'0';
    if(now.sign==other.sign){
       temp.integer=sum(now,other).integer;
       temp.fraction=sum(now,other).fraction;
       temp.sign=now.sign;
    }
    else if(now.sign == '-' && other.sign=='+'){
        if(other.integer >= now.integer||(other.integer == now.integer && other.fraction >= now.fraction)){
            temp.integer=sub(other,now).integer;
            temp.fraction=sub(other,now).fraction;
            temp.sign='+';
        }
        else {
            temp.integer = sub(now,other).integer;
            temp.fraction = sub(now,other).fraction;
            temp.sign='-';
        }
    }
    else if(now.sign == '+' && other.sign=='-'){
        if(other.integer > now.integer||(other.integer == now.integer && other.fraction > now.fraction)){
            temp.integer=sub(other,now).integer;
            temp.fraction=sub(other,now).fraction;
            temp.sign='-';
        }
        else {
            temp.integer = sub(now,other).integer;
            temp.fraction = sub(now,other).fraction;
            temp.sign='+';
        }
    }
    return temp;
}
//----------------------------------------------------------------------------------------------------------------------
//operator overloading + to get the sum of two bigreals
BigReal BigReal :: operator-(const BigReal& otherr) {
    BigReal temp;
    BigReal now,other;
    other=otherr;
    now.sign = sign;
    now.integer = integer;
    now.fraction = fraction;

    while (now.integer.size() > other.integer.size())'0' + other.integer;
    while (now.integer.size() < other.integer.size())'0' + now.integer;
    while (now.fraction.size() > other.fraction.size())other.fraction + '0';
    while (now.fraction.size() < other.fraction.size())now.fraction + '0';

    if (now.sign != other.sign) {
        temp.integer = sum(now, other).integer;
        temp.fraction = sum(now, other).fraction;
        temp.sign = '+';
    }
    else if(now.sign==other.sign=='+'){
        if(now.integer >= other.integer||(now.integer == other.integer &&now.fraction >= other.fraction)){
            temp.integer = sub(now,other).integer;
            temp.fraction = sub(now,other).fraction;
            temp.sign='+';
        }
        else {
            temp.integer=sub(other,now).integer;
            temp.fraction=sub(other,now).fraction;
            temp.sign='-';
        }
    }
    else if(now.sign==other.sign=='-'){
        if(now.integer > other.integer||(now.integer == other.integer &&now.fraction > other.fraction)) {
            temp.integer = sub(now, other).integer;
            temp.fraction = sub(now, other).fraction;
            temp.sign = '-';
        }
        else {
            temp.integer=sub(other,now).integer;
            temp.fraction=sub(other,now).fraction;
            temp.sign='+';
        }
    }
    return temp;

}
