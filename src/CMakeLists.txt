SET(SOURCE_FILES
    "Character.cpp"
    "DirectoryLoader.cpp"
    "Loader.cpp"
    "Logger.cpp"
	"Player.cpp"
    "Room.cpp"
)

add_library(dSmallWorld ${SOURCE_FILES})

add_executable(small_world "Main.cpp")

target_link_libraries(small_world dSmallWorld pthread)
