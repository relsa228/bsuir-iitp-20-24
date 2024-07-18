#include <stdio.h>
#include <inttypes.h>

int64_t toProtectedMode();
int64_t torealmode();

int main() {
    printf("%lld\n", toProtectedMode());
    return 0;
}