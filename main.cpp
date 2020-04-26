#include <iostream>
#include "Ranger/Tests/Test_Engine.h"

int main() {
    using namespace std;

    int error = 0;

    //Test_Color test;
    //Test_Config test;
    //Test_Shader test;
    //Test_BasicShape test;
    //Test_GLM test;
    //Test_Extensions test;


    Test_Engine test;

    test.test();

    cout << "---- exit main ----" << endl;
    return error;
}