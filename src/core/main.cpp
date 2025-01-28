#include "cortix_processor.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    CortiXProcessor implant("PT-1138");
    while (true) {
        std::this_thread::sleep_for(std::chrono::hours(24));

        try {
            // Update patient data
            implant.update_knowledge(
                "INSERT DATA { "
                "   <http://cortix/patient/PT-1138> :lastMeal :SpicyFood ; "
                "                                    :currentStressLevel 68 . "
                "}"
            );

            // Print success message
            std::cout << "Success: Patient data updated for PT-1138!" << std::endl;
        } catch (const std::exception& e) {
            // Handle errors
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}