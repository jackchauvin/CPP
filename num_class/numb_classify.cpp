// January 2019 - Jack Chauvin

#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<string>
using std::string;
#include<cctype>
using std::isdigit; using std::isalpha;

// Determines whether an input is a proper hexidecimal value
bool valid_hex(string str){
    if( str[0] == '-' ){
        str.erase(0,1);  // Erases the -
    }
    // Makes sure the 0x prefix is present and only 0-9 and a-f are used
    if( str.find("0x") != string::npos ){
        for( string::size_type i = str.find("0x") + 2; i < str.size(); ++i){
            if( isalpha(str[i]) && str[i] > 'f' ){
                return false;
            }
            if( !isalnum(str[i]) ){
                return false;
            }
        }
        return true;
    }
    return false;
}

// Determines whether an input is a proper octal value
bool valid_octal(string str){
    if( str[0] == '-' ){
        str.erase(0,1);
    }
    // Makes sure the 0 prefix is present and only 0-7 is used
    if( str[0] == '0' ){
        for(auto chr : str){
            if( chr > '7' || chr < '0' ){
                return false;
            }
        }
        return true;
    }
    return false;
}

// Determines whether an input is a proper binary value
bool valid_binary(string str){
    if(str[0] == '-'){
        str.erase(0,1);
    }
    // Makes sure 0b prefix is present and only 0-1 is used
    if(str.find("0b") != string::npos){
        for(string::size_type i = 2; i < str.size(); ++i){
            if( str[i] < '0' || str[i] > '1' ){
                return false;
            }
        }
        return true;
    }
    return false;
}

// Determines whether an input is a proper integer value
bool valid_int(string str){
    if( str[0] == '-' ){
        str.erase(0,1);
    }
    // Makes sure the number does not begin with 0
    // Only digits are used, with no decimals
    if( str[0] != '0' ){
        for( auto chr : str ){
            if( chr == '.' || !isdigit(chr) ){
                return false;
            }
        }
        return true;
    }
    return false;
}

// Determines whether an input is a proper float value
bool valid_float(string str){
    int count = 0;
    int e_found = false;
    if(str[0] == '-'){
        str.erase(0,1);
    }
    // Makes sure only digits, decimals, and e are used
    for ( auto chr : str ){
        if ( isdigit(chr) ){
            continue;
        // No more than one decimal in a floating point
        }else if( chr == '.' ){
            if(e_found){
                return false;
            }
            count++;
            if ( count == 2 ){
              return false;
            }
            continue;
        // If e
        }else if( chr == 'e' ){
            if(e_found){
                // Can't have 2 "e"s
                return false;
            }
            e_found = true;
            continue;
        }else{
            return false;
        }
    }
    return true;
}

// Determines the type of a given input
string classify_string(string str){
    if( valid_hex(str) ){
        return "hexidecimal";
    }
    if( valid_octal(str) ){
        return "octal";
    }
    if( valid_binary(str) ){
        return "binary";
    }
    if( valid_int(str) ){
        return "integer";
    }
    if( valid_float(str) ){
        return "float";
    }
    return "false";
}