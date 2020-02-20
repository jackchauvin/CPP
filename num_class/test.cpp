#include "numb_classify.cpp"

int main(){

    cout << "Input a number, in form \"0#0000\" (ie. 0b0101), to test\n";

    int testnum = 6;

    switch (testnum){
    
    case 1:
    {
        string to_test;
        cin >> to_test;
        cout << valid_hex(to_test) << endl;
        break;
    }

    case 2:
    {
        string to_test;
        cin >> to_test;
        cout << valid_octal(to_test) << endl;
        break;
    }

    case 3:
    {
        string to_test;
        cin >> to_test;
        cout << valid_binary(to_test) << endl;
        break;
    }

    case 4:
    {
        string to_test;
        cin >> to_test;
        cout << valid_float(to_test) << endl;
        break;
    }

    case 5:
    {
        string to_test;
        cin >> to_test;
        cout << valid_int(to_test) << endl;
        break;
    }

    case 6:
    {
        string to_test;
        cin >> to_test;
        cout << classify_string(to_test) << endl;
        break;
    }
    } 
}