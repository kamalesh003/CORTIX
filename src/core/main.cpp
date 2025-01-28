#include "cortix_processor.hpp"
#include <iostream>

int main() {
    CortiXProcessor implant("PT-1138");
    while (true) {
        std::this_thread::sleep_for(std::chrono::hours(24));
        implant.update_knowledge(
            "INSERT DATA { "
            "   <http://cortix/patient/PT-1138> :lastMeal :SpicyFood ; "
            "                                    :currentStressLevel 68 . "
            "}"
        );
    }
    return 0;
}
