#ifndef PREP_H
#define PREP_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Prep {
public:
    Prep() { make_init(); flag = true; };
    void PreProc(const std::string&);
    void print();
    
private:
    typedef void(Prep::*func)(const std::string&);
    bool flag;
    std::fstream fin;
    std::fstream fout;
    std::map<std::string, func> inst;
    std::map<std::string, std::string> defines;

private:
    void make_init();
    std::vector<std::string> split(const std::string&, std::string);
    void include(const std::string&);
    void define(const std::string&);
    void undef(const std::string&);
    void ifndef(const std::string&);
    void ifdef(const std::string&);
    //void endif(const std::string&);
    void def_cut(std::string&);
};

#endif // PREP_H