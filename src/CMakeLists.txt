SET(SOURCE_FILES
	"BaseMessage.cpp"
    "Character.cpp"
    "DirectoryLoader.cpp"
	"GameObject.cpp"
	"InterfaceManager.cpp"
    "Loader.cpp"
	"Logger.cpp"
	"Player.cpp"
	"Queue.cpp"
    "Room.cpp"
	"StringUtils.cpp"
)

add_library(dSmallWorld STATIC ${SOURCE_FILES})

add_executable(small_world "Main.cpp")

target_link_libraries(small_world dSmallWorld pthread)
