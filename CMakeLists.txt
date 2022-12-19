cmake_minimum_required(VERSION 3.12)
project(NavalBattle)

add_executable(NavalBattle "src/main.cpp" "src/Server.cpp" "src/Server.h" "src/Board.h" "src/Board.cpp" "src/NavalBattle.h" "src/NavalBattle.cpp" "src/Player.h" "src/Player.cpp"       "src/Utils.h" "src/Utils.cpp" "src/Ship.cpp" "src/Ship.h" )
target_link_libraries(NavalBattle ws2_32)


add_executable(ServerNB "src/mainServer.cpp")
target_link_libraries(ServerNB ws2_32)
