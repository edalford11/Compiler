//
//  Variable.h
//  Proj4
//
//  Created by Eric Alford on 11/27/12.
//  Copyright (c) 2012 Eric Alford. All rights reserved.
//

#ifndef __Proj4__Variable__
#define __Proj4__Variable__

#include <iostream>

using namespace std;

class Variable{
public:
    int value;
    string name;
    
    
    Variable(string name){
        this->name = name;
        value = 0;
    }
    ~Variable(){}
};

#endif /* defined(__Proj4__Variable__) */
