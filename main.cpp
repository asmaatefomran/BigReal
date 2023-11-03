#include <bits/stdc++.h>
#include "BigReal.h"
using namespace std;

int main(){
    string x,y;
    cin>>x>>y;
    BigReal n1(x),n2(y),n3;
    //BigReal n3 = n1 + n2;
    (n2+n1).print();
    //n3 = n3 + BigReal (0.9);
}
