


# базовый образ
FROM gcc:14  

# ставим cmake
RUN apt-get update && \
    apt-get install -y cmake \
    && rm -rf /var/lib/apt/lists/*


# рабочая папка внутри контейнера
WORKDIR /app

# копируем всё (надо бы .dockerignore)
COPY . .


# собираем 
RUN cmake -S src -B build 
RUN cmake --build build


# по умолчанию запускаем main (если собрался)
CMD ["./build/main"]

