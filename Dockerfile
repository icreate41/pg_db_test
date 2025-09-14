# Образ Ubuntu LTS
FROM ubuntu:24.04

# Аргументы сборки
ARG DB_NAME=testdb
ARG DB_USER=testuser
ARG DB_PASS=testpass

# Установка зависимостей
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    libpqxx-dev \
    postgresql

# Рабочая директория проекта
WORKDIR /workspace

# Копируем исходники тестового задания
COPY . /workspace

# Настройка PostgreSQL с использованием переменных
RUN service postgresql start && \
    su - postgres -c "psql -c \"CREATE USER ${DB_USER} WITH PASSWORD '${DB_PASS}';\"" && \
    su - postgres -c "psql -c \"CREATE DATABASE ${DB_NAME} OWNER ${DB_USER};\"" && \
    su - postgres -c "psql -c \"GRANT ALL PRIVILEGES ON DATABASE ${DB_NAME} TO ${DB_USER};\""

# Настройка .pgpass для автоматической аутентификации
RUN echo "localhost:5432:${DB_NAME}:${DB_USER}:${DB_PASS}" > /root/.pgpass && \
    chmod 600 /root/.pgpass

# Запуск bash по умолчанию
CMD ["/bin/bash"]
