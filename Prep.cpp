#include "Prep.h"

void Prep::make_init() {
    inst["#include"] = &Prep::include;
    inst["#define"] = &Prep::define;
    inst["#undef"] = &Prep::undef;
    inst["#ifndef"] = &Prep::ifndef;
    inst["#ifdef"] = &Prep::ifdef;
}

void Prep::PreProc(const std::string& filename) {
    fin.open(filename);
    fout.open("output.txt");
    if (fin.is_open() && fout.is_open()) {
        while (!fin.eof()) {
            std::string line;
            getline(fin, line);
            auto vec = split(line, " ");
            if (vec[0] == "#endif") {
                fout << std::endl;
                flag = true;
                continue;
            }
            if (inst.find(vec[0]) != inst.end()) {
                (this->*inst[vec[0]])(vec[1] + " " + vec[2]);
            } else {
                if (flag) {
                    def_cut(line);
                    this->fout << line << std::endl;
                }
            }
        }
    } else {
        throw std::runtime_error("file is not open");
    }
}

void Prep::include(const std::string& path) {
    std::string ptr = "";

    for (int i = 1; path[i] != static_cast<char>(34); ++i) {
        ptr += path[i];
    }

    std::fstream f_include;
    std::string line;
    f_include.open(ptr);
    if (f_include.is_open()) {
        while (!f_include.eof()) {
            getline(f_include, line);
            auto vec = split(line, " ");
            if (inst.find(vec[0]) != inst.end()) {
                (this->*inst[vec[0]])(vec[1] + " " + vec[2]);
            } else {
                this->fout << line << std::endl;
            }
        }
    } else {
        throw std::logic_error("file is not open");
    }
}

void Prep::define(const std::string& dest) {
    auto vec = split(dest, " ");
    defines[vec[0]] = vec[1];
}

void Prep::undef(const std::string& line) {
    auto vec = split(line, " ");
    defines.erase(vec[0]);
}

void Prep::ifndef(const std::string& line) {
    fout << std::endl;
    auto vec = split(line, " ");
    if (defines.find(vec[0]) != defines.end()) {
        flag = false;
        return;
    }
    flag = true;
}

void Prep::ifdef(const std::string& line) {
    fout << std::endl;
    auto vec = split(line, " ");
    if (defines.find(vec[0]) != defines.end()) {
        flag = true;
        return;
    }
    flag = false;
}

void Prep::def_cut(std::string& line) {
    for (auto it : defines) {
        if (line.find(it.first) != std::string::npos) {
            int pos = 0;
            while ((pos = line.find(it.first, pos + 1)) != -1) {
                line.erase(line.begin() + line.find(it.first),line.begin() + line.find(it.first) + it.first.size());
                line.insert(pos, it.second);
            }
        }
    }
}

std::vector<std::string> Prep::split(const std::string& str, std::string spliter) {
    std::vector<std::string> new_str = {};
    std::string tstr = {};
    for (int i = 0; i < str.size(); ++i) {
        if (spliter.find(str[i]) != std::string::npos) {
            if (tstr != "") {
                new_str.push_back(tstr);
                tstr.clear();
                continue;
            }
            continue;
        }
        tstr.push_back(str[i]);
    }
    new_str.push_back(tstr);
    return new_str;
}

void Prep::print() {
    for (auto it : defines) {
        std::cout << it.first << " " << it.second << std::endl;
    }
}
