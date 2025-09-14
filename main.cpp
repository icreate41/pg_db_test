#include "Database.hpp"
#include "Schema.hpp"
#include <iostream>

int main() {
    try {
        Database db{"dbname=testdb user=testuser host=localhost"};
        Schema::create(db);

        std::cout << "Database schema created successfully" << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}