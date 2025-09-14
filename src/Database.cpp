#include "Database.hpp"
#include <stdexcept>

Database::Database(const std::string& conninfo)
    : conn_(conninfo)
{
    if (!conn_.is_open()) {
        throw std::runtime_error("Failed to connect to database");
    }
}

pqxx::connection& Database::connection() {
    return conn_;
}