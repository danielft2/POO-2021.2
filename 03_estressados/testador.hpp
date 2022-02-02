#pragma once

#include <iostream>
#include <vector>

template <typename T>
void testar(const T& A, const T& B) {
    if (A == B)
        std::cout << "ok\n";
    else
        std::cout << A << " != " << B << "\n";
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
    os << "[ ";
    for (auto i : v)
        os << i << " ";
    os << "]";
    return os;
}