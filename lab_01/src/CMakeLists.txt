# делаем либу core из functions.cpp.
add_library(core STATIC functions.cpp)  
# теперь любой исполняемый файл (main/тесты) может линковаться с core
# и исп-ть countVowels без копир-ия .cpp файлов

# подключаем хедеры 
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) #прописываетс
#что при использовании core нужно видеть заголовочные файлы из src/.

# создаётся исполнй main из main.cpp.
add_executable(main main.cpp)

# линковка , но можно поменять PUBLIC на PRIVATE
# тепепь main  может использовать countVowels 
target_link_libraries(main PRIVATE core)


