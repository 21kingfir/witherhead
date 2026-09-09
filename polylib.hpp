#pragma once

#include <cstdint>
#include <iostream>

using namespace std;

void gennoise(uint64_t noise) {
    for (int i = noise; i>(1/((int)noise)); i-= 1) {
        cout << noise%(i*i) << endl;
    }
}