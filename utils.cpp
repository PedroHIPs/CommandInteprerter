#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "utils.h"
#include "commands.h"

std::string getCommand(std::string sentence) {
    std::vector<std::string> textVector;
    std::istringstream iss(sentence);
    std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(textVector));
    return textVector[0];
}

std::string getArg1(std::string sentence) {
    std::vector<std::string> textVector;
    std::istringstream iss(sentence);
    std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(textVector));
    if(textVector.size() > 1){
        return textVector[1];
    }else{
        return "";
    }
}

std::string getArg2(std::string sentence) {
    std::vector<std::string> textVector;
    std::istringstream iss(sentence);
    std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(textVector));
    if(textVector.size() > 1){
        return textVector[2];
    }else{
        return "";
    }
}

std::string getTextToInsert(std::string sentence) {
    std::vector<std::string> textVector;
    std::istringstream iss(sentence);
    std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(textVector));
    if(textVector.size() > 1){
        std::string text;
        text = sentence.substr(textVector[0].length()+textVector[1].length()+2,sentence.length());
        return text;
    }else{
        return "";
    }
}

std::string to_upper(std::string str){
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}
