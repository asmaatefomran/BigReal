#include <bits/stdc++.h>
#include "BigReal.h"
using namespace std;

int main(){
    string x,y;
    cin>>x>>y;
    BigReal n1(x),n2(y);

    BigReal n3= n2 + n2;
    n3.print();
    //n3 = n3 + BigReal (0.9);
}
