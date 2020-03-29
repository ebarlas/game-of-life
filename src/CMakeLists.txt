add_executable(gameoflife util/ClockTimer.cpp util/FpsLogger.cpp util/BitMatrix.cpp main.cpp game/Game.cpp util/Dimension.cpp)
target_link_libraries(gameoflife ${SDL2_LIBRARIES})