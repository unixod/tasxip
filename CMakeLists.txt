cmake_minimum_required(VERSION 2.8)
project(tasxip)

#set(CMAKE_VERBOSE_MAKEFILE TRUE)

#======================================================================#
# Configuration
#======================================================================#
set(OUTPUT_BIN_DIR "bin")
set(CMAKE_BUILD_TYPE "Release")

#======================================================================#
# Qt supporting
#======================================================================#
find_package(Qt4 REQUIRED)
set(QT_USE_QTNETWORK TRUE)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
set(EXTRA_LIBS ${QT_LIBRARIES})
#----------------------------------------------------------------------#

set(tasxip_SOURCES
	dataparser.cpp
	main.cpp
	mainwindow.cpp
	mainwindow_net.cpp
)

set(tasxip_HEADERS
	mainwindow.h
	dataparser.h
	rangeset.h
)

set(tasxip_FORMS
	mainwindow.ui
)

QT4_WRAP_CPP(tasxip_HEADERS_MOC ${tasxip_HEADERS})
QT4_WRAP_UI(tasxip_FORMS_HEADERS ${tasxip_FORMS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME}
	${tasxip_SOURCES}
	${tasxip_HEADERS_MOC}
	${tasxip_FORMS_HEADERS}
)

target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BIN_DIR}
		SKIP_BUILD_RPATH TRUE
		VERSION "1.0.2"
)
