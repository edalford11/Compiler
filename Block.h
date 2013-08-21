//
//  Nested.h
//  Proj4
//
//  Created by Eric Alford on 12/4/12.
//  Copyright (c) 2012 Eric Alford. All rights reserved.
//

#ifndef __Proj4__Block__
#define __Proj4__Block__

#include <iostream>
#include <vector>

using namespace std;

class Block{
public:
    int startIndex, endIndex;
    string type;
    
    Block(int startIndex, int endIndex, string type){
        this->startIndex = startIndex;
        this->endIndex = endIndex;
        this->type = type;
    }
    ~Block(){}
};

#endif /* defined(__Proj4__Block__) */
