#include <iostream>
#include <cstdint>
int32_t pow2(int32_t a)  {
    return ((a * a));
}
int32_t main()  {
     for( int32_t i=0;(i < 100);i += 2) {
        std::cout << pow2(i) << std::endl;
    };
     int32_t a=0;
    a += 2;
    std::cout << a << std::endl;
    return (0);
}
