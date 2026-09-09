#pragma once

#include <iostream>
#include <time.h>
#include <math.h>
#include <string.h>
#include <cstdlib>  
#include <stdint.h>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>

using namespace std;

int hashfile(uint64_t key, uint64_t e, string filepath, string newfilepath) {
    ifstream file(filepath, ios::binary);
    ofstream hash(newfilepath);
    if (!file || !hash) {    return 1;}
    uint64_t bytestohash[16384];
    char buffer[131072];
    uint16_t base_index = 0;
    uint64_t epoch;
    uint64_t d;
    uint16_t nbr_cells;
    uint64_t localindex;
    uint64_t dd;

    while (file.read(buffer, sizeof(buffer))) {
        if (sizeof(buffer)- file.gcount() != 0) {
            nbr_cells = (uint64_t)(file.gcount()+7)/8;
        } else {
            nbr_cells = 16384;
        }
        memcpy(bytestohash, buffer, sizeof(bytestohash));
        base_index = (base_index + e) % nbr_cells;
        for (int j = 0; j < 4; j++) {
            epoch = (uint64_t)(time(NULL));
            d = (uint64_t)cbrt(e * key * epoch);
            dd = d*d;
            for (uint16_t k = 0; k < nbr_cells; k++) { 
                localindex = (k + base_index) % nbr_cells;
                bytestohash[localindex] = (uint64_t)(bytestohash[localindex]*(dd)+(d*key)+epoch);
                e = bytestohash[localindex];
            }
        }
        hash.write(reinterpret_cast<const char*>(&bytestohash), sizeof(bytestohash));
    }
    return 0;
}