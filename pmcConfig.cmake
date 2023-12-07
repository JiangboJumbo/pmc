get_filename_component(PMC_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

message(${PMC_CMAKE_DIR})

set(PMC_INCLUDE_DIRS "${PMC_CMAKE_DIR}/../../../include")

set(PMC_DIRS
	"${PMC_CMAKE_DIR}/../../../lib/libpmc.so"
	)