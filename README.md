# PG_DB_TEST

Проект демонстрирует работу C++ с PostgreSQL через библиотеку `libpqxx`.
Для удобства запуск и проверка осуществляются в Docker-образе.

## Сборка и проверка

1. Сборка образа
    В папке проекта выполнить:
    ```bash
    docker build -t ubuntu_pg_test .
    ```

2. Запуск контейнера

    ```bash
    docker run --rm -it ubuntu_pg_test
    ```

3. Запуск PostgreSQL внутри контейнера
    ```bash
    service postgresql start
    ```

4. Сборка и запуск проекта
    ```bash
    cmake .
    make
    ./pg_db_test
    ```
    Ожидаемый вывод: `Database schema created successfully`

5. Проверка структуры базы данных
    ```bash
    su - postgres -c "psql -d testdb -c '\d'"
    ```
