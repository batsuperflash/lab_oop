FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y g++ make cmake git && \
    rm -rf /var/lib/apt/lists/*

# Устанавливаем Google Test
RUN git clone https://github.com/google/googletest.git /gtest && \
    cd /gtest && mkdir build && cd build && cmake .. && make && make install

WORKDIR /app
COPY . /app

RUN mkdir build
WORKDIR /app/build
RUN cmake .. && make

# По умолчанию запускаем тесты
CMD ["./BinaryTests"]
