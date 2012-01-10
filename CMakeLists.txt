project (MuddyReality)

file(GLOB_RECURSE muddyreality_SOURCES "src/*.cpp")
file(GLOB_RECURSE muddyreality_HEADERS "src/*.h")

set (muddyreality_INCLUDE_DIRS "")
foreach (_headerFile ${muddyreality_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND muddyreality_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES muddyreality_INCLUDE_DIRS)

include_directories(${muddyreality_INCLUDE_DIRS})
add_executable (muddyreality ${muddyreality_SOURCES})
