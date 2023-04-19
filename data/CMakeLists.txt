add_subdirectory(rooms)

get_filename_component(thisFolderName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
list(TRANSFORM ROOMS_TO_COPY PREPEND "${thisFolderName}/")

set(ROOMS_TO_COPY ${ROOMS_TO_COPY} PARENT_SCOPE)
