#include <flight/modules/lib/logger_util.hpp> // external logging utility
#include <flight/modules/mcl/Supervisor.hpp> // Includes 'Supervisor' type

using namespace std; // allows access to standard library utilities

int main(int argc, char** argv) { // argc = len(argv) in python; char** argv = actual arguments
    print("INFO: Starting Application"); 
    
    Supervisor supervisor; // Creates a new instance of 'Supervisor'
    supervisor.initialize();
    supervisor.run();

    print("INFO: Created supervisor");

    return 0; // return exit code (0=application completed successfully)
}
