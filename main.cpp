#include<iostream>
#include"picosha2.h"

using namespace std;

int main(){
    string convertText;
    cin >> convertText;
    string newHash = picosha2::hash256_hex_string(convertText);
    cout << endl << newHash << endl;
}