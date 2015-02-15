//
//  main.cpp
//  RSA
//
//  Created by Андрей Рычков on 22.03.13.
//  Copyright (c) 2013 Андрей Рычков. All rights reserved.
//

#include "Longint.h"
using namespace std;
#include <time.h>

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));
    
    long tic = time(NULL);
    
    Longint A("555");
    
    cout << A;
    
    cout << endl << time(NULL) - tic << endl;
    
    return 0;
}