cmake_minimum_required(VERSION 3.12)
project(NavalBattle)

add_executable(NavalBattle "src/main.cpp" "src/ServerClient.cpp" "src/ServerClient.h" "src/Board.h" "src/Board.cpp" "src/NavalBattle.h" "src/NavalBattle.cpp" "src/Player.h" "src/Player.cpp"       "src/Utils.h" "src/Utils.cpp" "src/Ship.cpp" "src/Ship.h" )
target_link_libraries(NavalBattle ws2_32)


add_executable(Server "src/Server.cpp")
target_link_libraries(Server ws2_32)
