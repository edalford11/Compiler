//
//  Parse.cpp
//  CamThat!
//
//  Created by Eric Alford on 11/27/12.
//  Copyright (c) 2012 Eric Alford. All rights reserved.
//

#define _DEBUG

#include <iostream>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Variable.h"
#include "Block.h"

using namespace std;

string fileArray[10000];
int i, j, k, l, bodyStart, fileIndex=1, size = 0, nestIndex=0;
vector<Variable> varList;
vector<Block> blockList;

bool isOperator(int op){
    bool flag = false;
    if(op == '+' | op == '-' | op == '*' | op == '/' | op == '=')
        flag = true;
    return flag;
}

void getFile(){
    char c = getchar();
    string word = "";
    
    while(!feof(stdin)){
        word = "";
        while(isspace(c) && !feof(stdin)){
            c = getchar();
        }
        while(!isspace(c) && !feof(stdin) && c != ';' && !isOperator(c) && c != ',' && c != '(' && c != ')'){
            word += c;
            c = getchar();
        }
        if(word != ""){
            fileArray[size] = word;
            size++;
        }
        if(c == ';' || isOperator(c)){
            fileArray[size] = c;
            size++;
            c = getchar();
        }
        else
            c = getchar();
    }
}

bool isNum(string s){
    bool flag = true;
    string::const_iterator it;
    for(it=s.begin(); it<s.end(); it++){
        if(!isdigit(*it))
            flag = false;
    }
    return flag;
}

bool operatorType(string op){
    bool flag = false;
    if(op == "+" | op == "-" | op == "*" | op == "/")
        flag = true;
    return flag;
}

/*
int findVar(string str){
    int index = -1;
    for(i=0; i<varList.size(); i++){
        if(varList[i].name == str)
            index = i;
    }
    return index;
}

int compute(int r1, string op, int r2){
    if(op != "NULL"){
        if(op == "*")
            return r1*r2;
        else if(op == "/")
            return r1/r2;
        else if(op == "+")
            return r1+r2;
        else
            return r1-r2;
    }
    else{
        return r1;
    }
}

bool condition(int v1, string rel, int v2){
    bool flag = false;
    if(rel == "<"){
        if(v1 < v2)
            flag = true;
    }
    if(rel == ">"){
        if(v1 > v2)
            flag = true;
    }
    if(rel == "<>"){
        if(v1 != v2)
            flag = true;
    }
    return flag;
}

bool parseCondition(){
    bool flag = false;
    int varIndex1, varIndex2, value1, value2;
    string relop;
    fileIndex++;
    if(isNum(fileArray[fileIndex])){            //first id is a number
        stringstream(fileArray[fileIndex]) >> value1; //parse string to int
        fileIndex++;
        if(isNum(fileArray[fileIndex])){        //second id is a number
            stringstream(fileArray[fileIndex]) >> value2; //parse string to int
        }
        else{                                   //second id is a variable
            varIndex2 = findVar(fileArray[fileIndex]);
            value2 = varList[varIndex2].value;
        }
    }
    else{                                       //first id is a variable
        varIndex1 = findVar(fileArray[fileIndex]);
        value1 = varList[varIndex1].value;
        fileIndex++;
        relop = fileArray[fileIndex];
        fileIndex++;
        if(isNum(fileArray[fileIndex])){        //second id is a number
            stringstream(fileArray[fileIndex]) >> value2; //parse string to int
        }
        else{                                   //second id is a variable
            varIndex2 = findVar(fileArray[fileIndex]);
            value2 = varList[varIndex2].value;
        }
    }
    
    if(condition(value1, relop, value2)){     //if condition is true
        flag = true;
    }
    return flag;
}*/

void skipBody(){
    while(fileArray[fileIndex] != "}"){ //skip the entire body
        fileIndex++;
        if(fileArray[fileIndex] == "{")
            skipBody();
    }
    fileIndex++;
}

void parseVar(){
    while((fileArray[fileIndex] != "{")){
        while(fileArray[fileIndex] != ";"){
            Variable *var = new Variable(fileArray[fileIndex]);
            varList.push_back(*var);
            fileIndex++;
        }
        fileIndex++;
    }
    bodyStart = fileIndex+1;
}

void execute(){
    int index = 0;
    int finalIndex = blockList[0].endIndex;
    bool flag = true;
    stack<Block> whileBlocks;
    
    fileIndex = blockList[0].startIndex;
    
    while(flag){                    //flag will be false when we reach the last }
        string leftSide = fileArray[fileIndex];
        if(leftSide == "WHILE"){
            for(i=0; i<blockList.size(); i++){    //find the correct node for the block
                if(fileIndex == blockList[i].startIndex)
                    index = i;
            }
//This is the evaluation of primary relop primary. This should be a function... But we can't use functions...
            bool flag2 = false;
            int varIndex1, varIndex2, value1, value2;
            string relop;
            fileIndex++;
            if(isNum(fileArray[fileIndex])){            //first id is a number
                stringstream(fileArray[fileIndex]) >> value1; //parse string to int
                fileIndex++;
                if(isNum(fileArray[fileIndex])){        //second id is a number
                    stringstream(fileArray[fileIndex]) >> value2; //parse string to int
                }
                else{                                   //second id is a variable
                    varIndex2 = -1;
                    for(i=0; i<varList.size(); i++){
                        if(varList[i].name == fileArray[fileIndex])
                            varIndex2 = i;
                    }
                    value2 = varList[varIndex2].value;
                }
            }
            else{                                       //first id is a variable
                varIndex1 = -1;
                for(i=0; i<varList.size(); i++){
                    if(varList[i].name == fileArray[fileIndex])
                        varIndex1 = i;
                }
                value1 = varList[varIndex1].value;
                fileIndex++;
                relop = fileArray[fileIndex];
                fileIndex++;
                if(isNum(fileArray[fileIndex])){        //second id is a number
                    stringstream(fileArray[fileIndex]) >> value2; //parse string to int
                }
                else{                                   //second id is a variable
                    varIndex2 = -1;
                    for(i=0; i<varList.size(); i++){
                        if(varList[i].name == fileArray[fileIndex])
                            varIndex2 = i;
                    }
                    value2 = varList[varIndex2].value;
                }
            }
            
            bool flag3 = false;
            if(relop == "<"){
                if(value1 < value2)
                    flag3 = true;
            }
            if(relop == ">"){
                if(value1 > value2)
                    flag3 = true;
            }
            if(relop == "<>"){
                if(value1 != value2)
                    flag3 = true;
            }
            
            if(flag3){     //if condition is true
                flag2 = true;
            }
            
//End evaluation
            
            //if parsecondition is true, put fileIndex on body. Else put fileIndex at endIndex and resume execution.
            if(flag2){
                whileBlocks.push(blockList[index]); //this while block is now the current active while loop
                fileIndex = fileIndex+2;            //skip {
            }
            else{
                fileIndex = blockList[index].endIndex+1;
                //if the while block is in the stack, pop it.
                if(!whileBlocks.empty()){
                    if(whileBlocks.top().startIndex == blockList[index].startIndex)
                        whileBlocks.pop();
                }
            }
            
            
        }
        else if(leftSide == "IF"){
            for(i=0; i<blockList.size(); i++){    //find the correct node for the block
                if(fileIndex == blockList[i].startIndex)
                    index = i;
            }
            
//This is the evaluation of primary relop primary. This should be a function... But we can't use functions...
            bool flag2 = false;
            int varIndex1, varIndex2, value1, value2;
            string relop;
            fileIndex++;
            if(isNum(fileArray[fileIndex])){            //first id is a number
                stringstream(fileArray[fileIndex]) >> value1; //parse string to int
                fileIndex++;
                if(isNum(fileArray[fileIndex])){        //second id is a number
                    stringstream(fileArray[fileIndex]) >> value2; //parse string to int
                }
                else{                                   //second id is a variable
                    varIndex2 = -1;
                    for(i=0; i<varList.size(); i++){
                        if(varList[i].name == fileArray[fileIndex])
                            varIndex2 = i;
                    }
                    value2 = varList[varIndex2].value;
                }
            }
            else{                                       //first id is a variable
                varIndex1 = -1;
                for(i=0; i<varList.size(); i++){
                    if(varList[i].name == fileArray[fileIndex])
                        varIndex1 = i;
                }
                value1 = varList[varIndex1].value;
                fileIndex++;
                relop = fileArray[fileIndex];
                fileIndex++;
                if(isNum(fileArray[fileIndex])){        //second id is a number
                    stringstream(fileArray[fileIndex]) >> value2; //parse string to int
                }
                else{                                   //second id is a variable
                    varIndex2 = -1;
                    for(i=0; i<varList.size(); i++){
                        if(varList[i].name == fileArray[fileIndex])
                            varIndex2 = i;
                    }
                    value2 = varList[varIndex2].value;
                }
            }
            
            bool flag3 = false;
            if(relop == "<"){
                if(value1 < value2)
                    flag3 = true;
            }
            if(relop == ">"){
                if(value1 > value2)
                    flag3 = true;
            }
            if(relop == "<>"){
                if(value1 != value2)
                    flag3 = true;
            }
            
            if(flag3){     //if condition is true
                flag2 = true;
            }
//End evaluation
            
            if(flag2){
                fileIndex = fileIndex+2;        //skip {
            }
            else{
                fileIndex = blockList[index].endIndex+1;
            }
            
        }
        else if(leftSide == "print"){
            fileIndex++;
            int varIndex = -1;
            for(i=0; i<varList.size(); i++){
                if(varList[i].name == fileArray[fileIndex])
                    varIndex = i;
            }
            fileIndex = fileIndex+2;                        //skip ;
            if(varIndex != -1)
                cout << varList[varIndex].value << endl;
            else
                cout << "ERROR, UNRECOGNIZED VARIABLE" << endl;
        }
        else if(leftSide == "}"){
            for(i=0; i<blockList.size(); i++){    //find the correct node for the block
                if(fileIndex == blockList[i].endIndex)
                    index = i;
            }
            if(blockList[index].type == "WHILE")
                fileIndex = blockList[index].startIndex;        //send back to start for re-evaluation
            else
                fileIndex++;
        }
        else{
            int varIndex = -1;
            for(i=0; i<varList.size(); i++){
                if(varList[i].name == leftSide)
                    varIndex = i;
            }
            
            int rightSide1=0, rightSide2=0, rightVarIndex1, rightVarIndex2;
            string op = "NULL";
            fileIndex = fileIndex+2;    //skip =
            if(isNum(fileArray[fileIndex])){            //first id is a number
                stringstream(fileArray[fileIndex]) >> rightSide1; //parse string to int
                fileIndex++;
                if(fileArray[fileIndex] != ";"){       //proceed if the statement continues
                    op = fileArray[fileIndex];
                    fileIndex++;
                    if(isNum(fileArray[fileIndex])){        //second id is a number
                        stringstream(fileArray[fileIndex]) >> rightSide2; //parse string to int
                        fileIndex++;
                    }
                    else{                                   //second id is a variable
                        rightVarIndex2 = -1;
                        for(i=0; i<varList.size(); i++){
                            if(varList[i].name == fileArray[fileIndex])
                                rightVarIndex2 = i;
                        }
                        rightSide2 = varList[rightVarIndex2].value;
                        fileIndex++;
                    }
                }
                fileIndex++;        //puts fileIndex on next line
            }
            else{                                       //first id is a variable
                rightVarIndex1 = -1;
                for(i=0; i<varList.size(); i++){
                    if(varList[i].name == fileArray[fileIndex])
                        rightVarIndex1 = i;
                }
                
                rightSide1 = varList[rightVarIndex1].value;
                fileIndex++;
                if(fileArray[fileIndex] != ";"){       //proceed if the statement continues
                    op = fileArray[fileIndex];
                    fileIndex++;
                    if(isNum(fileArray[fileIndex])){        //second id is a number
                        stringstream(fileArray[fileIndex]) >> rightSide2; //parse string to int
                        fileIndex++;
                    }
                    else{                                   //second id is a variable
                        rightVarIndex2 = -1;
                        for(i=0; i<varList.size(); i++){
                            if(varList[i].name == fileArray[fileIndex])
                                rightVarIndex2 = i;
                        }
                        rightSide2 = varList[rightVarIndex2].value;
                        fileIndex++;
                    }
                }
                fileIndex++;        //puts fileIndex on next line
            }
            
            if(op != "NULL"){
                if(op == "*")
                    varList[varIndex].value = rightSide1*rightSide2;
                else if(op == "/")
                    varList[varIndex].value = rightSide1/rightSide2;
                else if(op == "+")
                    varList[varIndex].value = rightSide1+rightSide2;
                else
                    varList[varIndex].value = rightSide1-rightSide2;
            }
            else{
                varList[varIndex].value = rightSide1;
            }
            
            rightSide1 = 0;
            rightSide2 = 0;
            op = "NULL";
        }
        
        if(!whileBlocks.empty()){                   //bring control to top of loop for re-evaluation
            if(whileBlocks.top().endIndex == fileIndex){
                fileIndex = whileBlocks.top().startIndex;
            }
        }
        if(fileIndex == finalIndex){     //if we've reached end of body, exit execution.
            flag = false;
        }
    }
}

void parseBody(){
    int st = fileIndex+1;       //skip {
    skipBody();
    int en = fileIndex-1;       //endIndex is on the last }
    Block *b = new Block(st, en, "BODY");
    blockList.push_back(*b);
    fileIndex = bodyStart;           //put index on first line in body.
    
    while(fileIndex < en){
        string leftSide = fileArray[fileIndex];
        if(leftSide == "WHILE"){
            int start = fileIndex;
            fileIndex = fileIndex+4; //skip condition, ends up on opening {
            skipBody();
            int end = fileIndex-1;    //end is on closing }
            Block *bl = new Block(start, end, "WHILE");
            blockList.push_back(*bl);
            fileIndex = start + 5;
        }
        else if(leftSide == "IF"){
            int start = fileIndex;
            fileIndex = fileIndex+4; //skip condition, ends up on opening {
            skipBody();
            int end = fileIndex-1;
            Block *bl = new Block(start, end, "IF");
            blockList.push_back(*bl);
            fileIndex = start + 5;
        }
        else if(fileArray[fileIndex] == "}"){
            fileIndex++;
        }
        else{
            while(fileArray[fileIndex] != ";"){ //skip all print and regular statements.
                fileIndex++;
            }
            fileIndex++;
        }
    }
}

int main(){
    getFile();
    parseVar();
    parseBody();
    execute();
}