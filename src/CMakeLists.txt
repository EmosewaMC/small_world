SET(SOURCE_FILES
    "Character.cpp"
    "DirectoryLoader.cpp"
	"GameObject.cpp"
    "Loader.cpp"
	"Player.cpp"
	"Queue.cpp"
    "Room.cpp"
	"StringUtils.cpp"
)

SET(LOGGER_LIBRARY
	"Logger.cpp"
)

add_library(dSmallWorld STATIC ${SOURCE_FILES})
add_library(dLogger STATIC ${LOGGER_LIBRARY})

add_executable(small_world "Main.cpp")

target_link_libraries(small_world dSmallWorld pthread dLogger)
