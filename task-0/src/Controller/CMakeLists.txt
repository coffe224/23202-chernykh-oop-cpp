add_library(Controller Controller.cpp Controller.h)

target_link_libraries(Controller Converter FileReader FileWriter Parser Statistics)