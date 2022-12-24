cmake_minimum_required(VERSION 3.15)

project(pmc)

# OPTIONS
# ----------------------------------------------

option(_OPENMP "enable openmp" OFF)


# Export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the output folder where your program will be created
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/out)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/out)


# Detect operating system
# ----------------------------------------------
message(STATUS "We are on a ${CMAKE_SYSTEM_NAME} system")
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(IS_LINUX ON)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set(IS_MAC ON)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(IS_WINDOWS ON)
endif()

# Find OMP
# ----------------------------------------------
if(_OPENMP)
    find_package(OpenMP REQUIRED)
endif()

# Set Compiler flags
# ----------------------------------------------
set(CMAKE_POSITION_INDEPENDENT_CODE ON)  # -fPIC

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")



# Set sources and includes
# ----------------------------------------------
add_subdirectory (src)
add_subdirectory (include)



# Create shared library
# ----------------------------------------------

add_library (pmc SHARED ${pmc_src} ${pmc_headers})

target_include_directories(pmc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# define the public API
set_target_properties(pmc PROPERTIES PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/libpmc.h)

# link OpenMP if enabled
if(_OPENMP)
    target_link_libraries(pmc PUBLIC OpenMP::OpenMP_CXX)
endif()

# Install pmc shared library
install(TARGETS pmc
	EXPORT  ${PROJECT_NAME}
            LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"
)
