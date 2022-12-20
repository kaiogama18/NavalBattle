cmake_minimum_required(VERSION 3.12)
project(NavalBattle)

add_executable(NavalBattle "src/main.cpp"   "src/Board.h" "src/Board.cpp" "src/NavalBattle.h" "src/NavalBattle.cpp" "src/Player.h" "src/Player.cpp"       "src/Utils.h" "src/Utils.cpp" "src/Ship.cpp" "src/Ship.h"  "src/Client.cpp" "src/Client.h" "src/Semaphore.h" "src/Semaphore.cpp")
target_link_libraries(NavalBattle ws2_32)


add_executable(Server "src/Server.cpp" "src/Client.cpp" "src/Client.h" "src/Semaphore.h" "src/Semaphore.cpp")
target_link_libraries(Server ws2_32)
