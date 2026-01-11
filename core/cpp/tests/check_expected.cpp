#include <expected>
#include <iostream>

int main() {
#ifdef __cpp_lib_expected
    std::cout << "std::expected supported" << std::endl;
#else
    std::cout << "std::expected NOT supported" << std::endl;
#endif
    return 0;
}
