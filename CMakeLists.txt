cmake_minimum_required(VERSION 3.12)
project(NavalBattle)


add_executable(NavalBattle "src/main.cpp" "src/Server.cpp" "src/Server.h" "src/Board.h" "src/Board.cpp" "src/NavalBattle.h" "src/NavalBattle.cpp")

target_link_libraries(NavalBattle ws2_32)


add_executable(NavalBattleClient "src/mainClient.cpp" "src/Board.h" "src/Board.cpp" "src/NavalBattle.h" "src/NavalBattle.cpp")
target_link_libraries(NavalBattleClient ws2_32)
