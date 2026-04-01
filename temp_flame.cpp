#include <iostream>
#include <cstdint>
#include <array>
#include <vector>
void swap(int32_t  &a, int32_t  &b)  {
    int32_t c=b;
     b=a;
     a=c;
}
;
struct cool {
    int32_t x=0;
    void inc()  {
        x++;
        return;
    }
;
};
int32_t main()  {
    int32_t f=-3;
    int32_t d=-2;
    swap(f, d);
    std::cout << f << std::endl;
    return (0);
}
;
