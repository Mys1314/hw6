#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <vector>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        std::string hstr = k;
        std::vector<HASH_INDEX_T> nums;
        HASH_INDEX_T w[5] {0,0,0,0,0};
        HASH_INDEX_T hnum = 0;
        for(HASH_INDEX_T i = 0; i < k.size(); i++){
            //std::cout << k[i] << std::endl;
            nums.push_back(letterDigitToNumber(k[i]));
        }
        int j = 4;
        int i = 0;
        int mult = 1;
        HASH_INDEX_T num = 0;
        while(nums.size() > 0){
            if(i%6 == 0){
                if(num != 0){
                    w[j] = num;
                    //std::cout << "w[" << j << "] = " << w[j] << std::endl;
                    j--;
                }
                mult = 1;
                num = 0;
            }
            //std::cout <<  nums[nums.size() - 1] << std::endl;
            num += nums[nums.size() - 1]*mult;
            nums.erase(nums.begin() + nums.size() - 1);
            mult *= 36;
            i++;
        }
        w[j] = num;
        //std::cout << "w[" << j << "] = " << w[j] << std::endl;
        for(i = 0; i < 5; i++){
            hnum += rValues[i]*w[i];
        }
        return hnum;
    }
    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T num = 0;
        if(letter >= 'A' && letter <= 'Z'){
            num = (HASH_INDEX_T)(letter - 'A');
        }else if(letter >= 'a' && letter <= 'z'){
            num = (HASH_INDEX_T)(letter - 'a');
        }else{
            num = (HASH_INDEX_T)(letter - '0') + 26;
        }
        return num;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
