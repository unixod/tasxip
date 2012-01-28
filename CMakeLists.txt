cmake_minimum_required(VERSION 2.8)

#======================================================================#
# Configuration
#======================================================================#
set(OUTPUT_BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin")

# getting version number
file(STRINGS
	VERSION	APP_VERSION
	LIMIT_COUNT 1
	REGEX "^[0-9]+\\.[0-9]+\\.[0-9]$"
)

#======================================================================#
# Generation
#======================================================================#
if(APP_VERSION)
	add_definitions(-DVERSION="${APP_VERSION}")
	add_subdirectory(src)
else(APP_VERSION)
	message(FATAL_ERROR
		"Version number (in format MAJOR.MINOR.MICRO) must be specified in 'version' file."
	)
endif(APP_VERSION)

