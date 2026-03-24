#include <iostream>
#include <cstdint>
#include <array>
int32_t add(int32_t a, int32_t b)  {
    return ((a + b));
}
int32_t add_(std::array<int32_t ,3>a)  {
    return ((a[0] + a[1]));
}
std::array<int32_t ,3>array_()  {
    std::array<int32_t ,3>a={1, 2, 3};
    return (a);
}
int32_t main()  {
    std::array<int32_t ,3>i=array_();
    std::array<int32_t ,2>j={1, 2};
    int32_t f=-3;
    std::cout << i << std::endl;
    std::cout << "Hi ^^" << std::endl;
    return (0);
}
