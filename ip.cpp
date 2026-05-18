#include "ip.h"
#include <iostream>
#include <stddef.h>
#include "string.h"
const int MAX = 256;
const int ERROR = -1;
const int LENGTH = 2;
const int SLASH = 1; //there one slash in the ip address
const int ONE = 1;
const int AFTER_SLASH_MAX = 32;
const int BYTES = 8;


//constructor//

ip::ip(String ipType):ipType(ipType){}

bool ip::set_value(String value) {

    // we need the variables for split //
    size_t size;
    String* ip;
    char delimiters[] = "./";;

    // now we use the split the we create in string.h//
    value.split(delimiters, &ip, &size);
    if (size != POINTS + SLASH) {
        return false;
    }

    // now we check if the number after the slash is
    //between 0-32
    // then we check if the numbers before the slash
    //between 0-255

    for (int i = 0; i < (int)size - SLASH; i++) {
        ruleIP[i] = ip[i].to_integer();
        if (ruleIP[i] > MAX || ruleIP[i] < 0) {
            delete[] ip;
            return false;
        }
    }
    subnet_mask = ip[size - SLASH].to_integer();
    delete[] ip;

    if (subnet_mask < 0 || subnet_mask>32)
        return false;
    return true;
}


// this function will help us to check if the number 
// is legal after we know the subnet mask 
//the number after slash
int Check_helper(int num_bits, int value) {
    int tmp = value;

    while (num_bits < BYTES) {
        tmp >>= 1;   //div by 2
        num_bits++;
    }

    return tmp;
}


bool ip::aux_match(String ip) {
   
    char delimeter_dots[] = ".";
    ip = ip.trim();
    String* points;
    size_t points_num;

    ip.split(delimeter_dots, &points, &points_num);

    if (points_num != POINTS) {
        delete[] points;
        return true;
    }
    int packetIP[POINTS];
    for (int i = 0; i < POINTS; i++) {
        packetIP[i] = points[i].to_integer();
        if (packetIP[i] > MAX || packetIP[i] < 0) {
            delete[] points;
            return false;
        }
    }
    delete[] points;
    int byteToCheck = subnet_mask / 8;
    for (int i = 0; i < byteToCheck; i++) {
        if (packetIP[i] != ruleIP[i]) {
            return false;
        }
    }
    if (byteToCheck == POINTS) {
        return true;
    }
    int bitsToCheck = subnet_mask % 8;

    if (packetIP[byteToCheck] >> (BYTES - bitsToCheck) != 
    (ruleIP[byteToCheck] >> (BYTES - bitsToCheck))) {
        return false;
    }
    return true;
}


bool ip::match(String packet) {
    size_t size;
    bool value = false;
    String* after_split;

    packet.split("=, ", &after_split, &size);
    if (!size) {
        delete[] after_split;
        return false;
    }
    for (size_t i = 0; i < size; i += LENGTH)
    {
        if (ipType.equals(after_split[i])) {
            value = aux_match(after_split[i + ONE]);
            break;
        }
    }
    delete[] after_split;
    return value;
}
