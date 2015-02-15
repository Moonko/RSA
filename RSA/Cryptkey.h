//
//  Header.h
//  RSA
//
//  Created by Андрей Рычков on 08.04.13.
//  Copyright (c) 2013 Андрей Рычков. All rights reserved.
//

#ifndef RSA_Header_h
#define RSA_Header_h

#include <fstream>
#include "Longint.h"

struct cryptkey
{
    Longint _first;
    Longint _second;
    
    bool loadFromFile (const char* fname)
    {
        Longint tmp("0");
        
        std::ifstream inFile(fname);
        
        if (inFile)
        {
            inFile >> tmp;
            _first = tmp;
            inFile >> tmp;
            _second = tmp;
            
            inFile.close();
            
            return true;
        }
        return false;
    }
    bool saveToFile (const char* fname)
    {
        std::ofstream outFile(fname);
        
        if (outFile)
        {
            outFile << _first << std::endl;
            outFile << _second << std::endl;
            
            outFile.close();
            
            return true;
        }
        return false;
    }
};

#endif
