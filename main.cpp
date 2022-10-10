#include "Prep.h"

int main(int argc, char* argv[]) {
    Prep obj;
    argc == 2 ? obj.PreProc(argv[1]) : throw std::invalid_argument("The count of elements is wrong");
}