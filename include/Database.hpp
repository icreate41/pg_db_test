#pragma once
#include <pqxx/pqxx>
#include <string>

// Класс-обёртка для подключения к PostgreSQL
class Database {
public:
    explicit Database(const std::string& conninfo);

    pqxx::connection& connection();

private:
    pqxx::connection conn_;
};