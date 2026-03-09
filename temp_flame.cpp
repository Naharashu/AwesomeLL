#include <iostream>
#include <cstdint>
using namespace std;
int main() {
 int32_t i=0;
 while((i < 4))  {
    std::cout << i << std::endl;
    if((i == 2)) {
        break;
    };
     i=(i + 1);
};
return 0;
}
