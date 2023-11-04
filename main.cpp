// File: main.cpp
// Author:  Maya Fouad        Asmaa Atef        Fatma Ibrahim
// ID:      20220270           20221020           20220242
// TA: Mohamed Talaat Saad Farrag
// Section: 19, 20
// Date: 4 Nov 2023
#include <bits/stdc++.h>
#include "BigReal.h"
using namespace std;

int main(){
    string n1; cin >> n1  ;
    BigReal num1(n1);
    num1.print();
    BigReal num2("9600000002.962474100000000000000000000");
    cout << num2;
    BigReal num3(0.999);
    cout << num3;
    BigReal num4(num1);
    BigReal num5 = num1;
    num4.print(); num5.print();
    BigReal num6 ;
    num6 = num1 + num4;
    num6.print();
    BigReal num7 ;
    num7 = num1 - num4;
    num7.print();
    BigReal num8 ;
    num8 =  num2 + num3;
    cout << num8;
    cout << (num1>num3) << endl;
    cout << (num1<num3) << endl;
    cout << (num1==num3) << endl;

}
