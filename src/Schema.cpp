#include "Schema.hpp"
#include <pqxx/pqxx>

void Schema::create(Database& db) {
    pqxx::work txn{db.connection()};

    // Создаём таблицу пользователей
    txn.exec(R"(
        CREATE TABLE IF NOT EXISTS users (
            id SERIAL PRIMARY KEY,
            username TEXT NOT NULL UNIQUE,
            public_key TEXT NOT NULL UNIQUE
        );
    )");

    // Создаём таблицу кошельков
    txn.exec(R"(
        CREATE TABLE IF NOT EXISTS wallets (
            id SERIAL PRIMARY KEY,
            user_id INT REFERENCES users(id) ON DELETE CASCADE,
            balance NUMERIC(20,8) DEFAULT 0
        );
    )");

    // Создаём таблицу транзакций
    txn.exec(R"(
        CREATE TABLE IF NOT EXISTS transactions (
            id SERIAL PRIMARY KEY,
            from_wallet INT REFERENCES wallets(id) ON DELETE SET NULL,
            to_wallet INT REFERENCES wallets(id) ON DELETE SET NULL,
            amount NUMERIC(20,8) NOT NULL
        );
    )");

    // Создаём таблицу смарт-контрактов
    txn.exec(R"(
        CREATE TABLE IF NOT EXISTS contracts (
            id SERIAL PRIMARY KEY,
            owner_id INT REFERENCES users(id) ON DELETE SET NULL,
            code TEXT NOT NULL
        );
    )");

    // Создаём таблицу событий
    txn.exec(R"(
        CREATE TABLE IF NOT EXISTS events (
            id SERIAL PRIMARY KEY,
            contract_id INT REFERENCES contracts(id) ON DELETE CASCADE,
            tx_id INT REFERENCES transactions(id) ON DELETE CASCADE,
            event_type TEXT NOT NULL
        );
    )");

    txn.commit();
}