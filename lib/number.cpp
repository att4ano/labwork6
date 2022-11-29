#include "number.h"
#include <cstring>
#include <iomanip>
#include <stdexcept>


uint2022_t from_uint(uint32_t i) {
    std::string str_i = std::to_string(i);
    size_t n = (str_i.length() % 9 == 0) ? str_i.length() / 9 : str_i.length() / 9 + 1;
    uint2022_t number;
    number.num.reserve(68);
    for (int j = 0; j < n; j++){
        number.num.push_back(i % number.discharge);
        i = i / number.discharge;
    }
    return number;
}

bool checkLimit(const uint2022_t& number){
    uint2022_t limit;
    limit.num = {507874304, 969913778, 774576546, 725012875, 191406452, 303829940, 881442030, 954961376, 274169543, 834615428, 547524361, 773223140, 481542519, 537288393, 541295792, 751341651, 173279750, 670958716, 240845924, 223507647, 839959347, 787178135, 892906992, 452928068, 163567159, 780797071, 467547461, 367810693, 336814855, 168904426, 682647773, 247882082, 31629150, 246692573, 740867054, 544896131, 733384278, 973951695, 683886781, 325582710, 589632190, 457687591, 633901300, 432508865, 131240610, 413834190, 579813164, 8949136, 139877256, 947069992, 521812209, 110959089, 375642882, 34484602, 367106052, 758326916, 751394401, 231009526, 437689024, 873322306, 884163925, 263414417, 322714142, 625631274, 922703235, 684800786, 916771158, 481560};
    if (limit > number){
        return true;
    }else{
        return false;
    }
}


uint2022_t from_string(const char* buff) {
    uint2022_t number;
    number.num.reserve(68);
    char sub_arr[9];
    int current_str = strlen(buff);
    while(current_str > 0){
        if (current_str >= 9) {
            for(int i = 0; i < 9; i++){
                sub_arr[i] = buff[current_str - 9 + i];
            }
            number.num.push_back(std::atoi(sub_arr));
        }else{
            char sub_arr2[current_str];
            for(int i = 0; i < current_str; i++) {
                sub_arr2[i] = buff[i];
            }
            number.num.push_back(std::atoi(sub_arr2));
        }
        current_str = current_str - 9;
    }
    if(checkLimit(number)){
        return number;
    } else {
        throw std::invalid_argument("Undefined behaviour");
    }
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t number;
    number.num.reserve(68);
    std::vector <unsigned int> arr1 = (lhs.num.size() >= rhs.num.size() ? lhs.num : rhs.num);
    std::vector <unsigned int> arr2 = (lhs.num.size() < rhs.num.size() ? lhs.num : rhs.num);
    while(arr2.size() < arr1.size()){
        arr2.push_back(0);
    }
    int current_block = 0;
    int ost = 0;
    while(current_block < arr1.size()){
        unsigned int first_prt = arr1[current_block];
        unsigned int second_prt = arr2[current_block];
        arr1[current_block] = (first_prt + second_prt + ost) % lhs.discharge;
        ost = (first_prt + second_prt + ost) / lhs.discharge;
        current_block++;
    }
    if (ost != 0){
        arr1.push_back(ost);
    }
    number.num = arr1;
    if (checkLimit(number)){
        return number;
    }else{
        throw std::invalid_argument("Undefined behaviour");
    }
}

bool operator>(const uint2022_t& lhs, const uint2022_t& rhs){
    if (lhs.num.size() > rhs.num.size()){
        return true;
    }else{
        for(int i = lhs.num.size() - 1; i >= 0; i++){
            if(lhs.num[i] > rhs.num[i]){
                return true;
            }else if (lhs.num[i] <= rhs.num[i]){
                return false;
            }else{
                continue;
            }
        }
    }
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t number;
    number.num.reserve(68);
    if (lhs == rhs){
        number.num.push_back(0);
        return number;
    }else {
        if (lhs > rhs) {
            std::vector<unsigned int> ex_arr1 = lhs.num;
            std::vector<unsigned int> ex_arr2 = rhs.num;
            while(ex_arr2.size() < ex_arr1.size()){
                ex_arr2.push_back(0);
            }
            int i = 0;
            while(i < ex_arr1.size()){
                if (ex_arr1[i] - ex_arr2[i] < 0){
                    ex_arr1[i + 1] -= 1;
                    ex_arr1[i] = ex_arr1[i] - ex_arr2[i] + 1;
                }else{
                    ex_arr1[i] = ex_arr1[i] - ex_arr2[i];
                }
                i++;
            }
            number.num = ex_arr1;
            return number;
        }else{
            throw std::invalid_argument("Undefined behaviour");
        }
    }
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t number = from_uint(0);
    if (lhs == from_uint(0) || rhs == from_uint(0)){
        return number;
    } else {
        uint2022_t number;
        number.num.reserve(68);
        uint2022_t temporary_number;
        for (int i = 0; i > lhs.num.size() + rhs.num.size(); i++) {
            number.num.push_back(0);
        }
        std::vector<unsigned int> first_mul = ((lhs.num.size() >= rhs.num.size()) ? lhs.num : rhs.num);
        std::vector<unsigned int> second_mul = ((lhs.num.size() < rhs.num.size()) ? lhs.num : rhs.num);
        std::vector<unsigned int> temporary_num;

        for (int i = 0; i < second_mul.size(); i++) {
            for (int j = 0; j < first_mul.size(); j++) {
                temporary_num.push_back(0);
            }
            unsigned long long temporary_value = 0;
            long ost = 0;
            for (int j = 0; j < i; j++) {
                temporary_num.push_back(0);
            }
            for (int j = 0; j < first_mul.size(); j++) {
                temporary_value = (unsigned long long) first_mul[j] * (unsigned long long) second_mul[i] + ost;
                temporary_num[i + j] = temporary_value % number.discharge;
                ost = temporary_value / number.discharge;
                temporary_value = 0;
            }
            if (ost != 0) {
                temporary_num.push_back(ost);
            }
            temporary_number.num = temporary_num;
            if (temporary_num[temporary_num.size() - 1] == 0) {
                temporary_num.pop_back();
            }
            number = number + temporary_number;
            temporary_num.clear();
        }
        if (number.num[number.num.size() - 1] == 0) {
            number.num.pop_back();
        }
        if (checkLimit(number)){
            return number;
        } else {
            throw std::invalid_argument("Undefined behaviour");
        }
    }
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    return uint2022_t();
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    if (lhs.num.size() != rhs.num.size()) {
        return false;
    } else {
        bool flag = true;
        for (int i = 0; i < lhs.num.size(); i++) {
            if (lhs.num[i] != rhs.num[i]) {
                flag = false;
                break;
            }
        }
        return flag;
    }
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    if (lhs == rhs) {
        return false;
    } else {
        return true;
    }
}
std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    if (value.num.empty()){
        stream << 0;
    }else{
        for(int i = value.num.size() - 1; i >= 0; i--) {
            if (i != value.num.size() - 1) {
                stream << std::setfill('0') << std::setw(9) << value.num[i];
            }else{
                stream << value.num[i];
            }
        }
    }
    return stream;
}
