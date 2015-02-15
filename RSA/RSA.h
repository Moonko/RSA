//
//  RSA.h
//  RSA
//
//  Created by Андрей Рычков on 08.04.13.
//  Copyright (c) 2013 Андрей Рычков. All rights reserved.
//

#ifndef __RSA__RSA__
#define __RSA__RSA__

#include <fstream>
#include "Cryptkey.h"

class RSA
{
    // Encrypt string
    Longint static encrypt ();
    // Decrypt string
    std::string static decrypt ();
    // Extended Euclidean algorithm
    void static extEuclid (Longint, Longint, Longint&);
public:
    // Generate public and private keys
    void static genkeys (cryptkey&, cryptkey&);
    // Encrypt .txt
    void static encryptTxtFile ();
    // Decrypt .txt
    void static decryptTxtFile ();
};

#endif /* defined(__RSA__RSA__) */
