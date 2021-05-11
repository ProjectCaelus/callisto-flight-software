#include <flight/modules/lib/Util.hpp>
#include <flight/modules/mcl/Flag.hpp>
#include <flight/modules/lib/logger_util.hpp>

#ifdef DESKTOP
    #include <chrono>
#else
    #include "Arduino.h"
#endif


StaticJsonDocument<20000> Util::doc;

vector<string> Util::split(const string &s, const string &delimiter){
    string temp = s;
    vector<string> result;

    size_t pos = 0;
    std::string token;
    while ((pos = temp.find(delimiter)) != std::string::npos) {
        token = temp.substr(0, pos);
        result.push_back(token);
        temp.erase(0, pos + delimiter.length());
    }
    return result;
}

string Util::replaceAll(string str, const string& from, const string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

template <typename T> int Util::getIndex(vector<T> arr, T val){
// int Util::getIndex(vector<int> arr, int val){
    for(unsigned int i = 0; i < arr.size(); i++){
        if(arr[i] == val){
            return i; 
        }
    }
    return -1;
}

int Util::getMaxIndex(string str, string val) {
    // Gets index of last occurence of a string in another string. Only supports 1-char strings.
    int ind = -1;
    char ch = val[0];
    for(unsigned int i = 0; i < str.size(); i++) {
        if (str[i] == ch) {
            ind = i;
        }
    }
    return ind;
}

template int Util::getIndex<int>(vector<int>, int); // Instantiate the template for type int
template int Util::getIndex<float>(vector<float>, float); // Instantiate the template for type int

double Util::min(double a, double b){
    if(a < b){
        return a;
    }
    return b;
}

double Util::max(double a, double b){
    if(a > b){
        return a;
    }
    return b;
}

/*
long getMiliTimestampLong(const Flag& flag) {
    return static_cast<long>(Util::getTime() - flag.general.mcl_start_time);
}

string getMiliTimestampStr(const Flag& flag) {
    // Returns hexadecimal representation string 
    long millisecond_timestamp = static_cast<long>(Util::getTime() - flag.general.mcl_start_time);
    return Util::int_to_hex(millisecond_timestamp);
}

template<typename T> string int_to_hex(T num) {
    stringstream stream;
    stream << "0x"
        << std::setfill('0') << std::setw(sizeof(T)*2) 
        << std::hex << num;
    return stream.str();
}
*/

string Util::to_string(bool b) {
    return b ? "true" : "false";   
}

string Util::to_string(int i) {
    return to_string((long int) i);
}

string Util::to_string(double d) {
    return to_string((long double) d);
}

string Util::to_string(long int i) {
    if(i == 0) {
        return string("0");
    }

    long int temp = abs(i);
    string ret = "";
    while (temp > 0) {
        ret = (char) ('0' + temp % 10) + ret;
        temp /= 10;
    }
    string test = "";

    if(i < 0) {
        return string("-") + ret;
    }

    return ret;
}

string Util::to_string(long double d) {
    // Algorithm: take the double, multiply it by 10 until there are no decimals (or until integer overflow - 17 digits), 
    // Convert that int to a string, place the decimal point back where it belongs
    // TODO: Doesn't handle small numbers, such as 0.00123; it just converts it to 0.123

    long double temp = d;
    unsigned long int dot = to_string((long int) temp).length();

    while((long int) round(temp) != temp && abs(temp / 1000000000000000000) < 1) { // handles integer overflow if there are more than 17 digits
        temp *= 10;
    }

    long int expanded_temp = (long int) temp;

    string output = to_string(expanded_temp);

    if(0 < d && d < 1) { // make sure 0.9 doesn't become 9
        dot--;
    }

    if(dot != output.length()) {
        output = output.substr(0, dot) + "." + output.substr(dot);
    }

    return output;
}

string Util::hex(long w) {
    bool negative = false;
    if(w < 0){
        w = -w;
        negative = true;
    }
    size_t hex_len = sizeof(long) << 1;
    static const char* digits = "0123456789ABCDEF";
    std::string ret(hex_len,'0');
    
    for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4) {
        ret[i] = digits[(w >> j) & 0x0f];
    }
    
    int start = 0;
    
    while(ret[start] == '0') {
        start++;
    }
    
    string to_return_final = ret.substr(start);
    
    if(to_return_final == "") {
        return "0";
    } 
    else {
        if(negative){
            to_return_final = "-" + to_return_final;
        }
        return to_return_final;
    }
}

long double Util::getTime(){
    #ifdef DESKTOP
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    #else
        return millis();
    #endif
}

void Util::pause(int millis){
    #ifdef DESKTOP
        long double curr_time = getTime();
        while(getTime() < curr_time + millis);
    #else
        delay(millis);
    #endif
}

void Util::terminate(){
    print("Terminating program");
    #ifdef DESKTOP
        int a = 1;
        int b = 0;
        int c = a / b;
    #else
        while(true){

        }
    #endif
}
