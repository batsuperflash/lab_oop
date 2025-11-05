# базовый образ ubuntu 22.04
FROM ubuntu:22.04

# обновляем пакеты и ставим cmake, g++, make, git
RUN apt-get update && \
    apt-get install -y cmake g++ make git wget unzip && \
    rm -rf /var/lib/apt/lists/*

# рабочая директория
WORKDIR /app

# копируем файлы проекта
COPY . .

# создаем папку build
RUN mkdir build

# сборка проекта через cmake
WORKDIR /app/build
RUN cmake .. -DCMAKE_BUILD_TYPE=Release && cmake --build .

# команда по умолчанию: запуск main
CMD ["./main"]
