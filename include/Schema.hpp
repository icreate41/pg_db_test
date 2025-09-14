#pragma once
#include "Database.hpp"

// Создание схемы (5 связанных таблиц NF)
class Schema {
public:
    static void create(Database& db);
};