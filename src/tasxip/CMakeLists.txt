cmake_minimum_required(VERSION 2.8)
project(tasxip)

#set(CMAKE_VERBOSE_MAKEFILE TRUE)

#======================================================================#
# Configuration
#======================================================================#
#set(OUTPUT_BIN_DIR "bin")
set(CMAKE_BUILD_TYPE "Release")

#TEMPORARY HACK!!! (cmake stil not yet support switching to C++11)
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

#======================================================================#
# Qt supporting
#======================================================================#
find_package(Qt4 REQUIRED)
set(QT_USE_QTNETWORK TRUE)
set(QT_USE_QTSCRIPT TRUE)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
set(EXTRA_LIBS ${QT_LIBRARIES})

#======================================================================#
# UAU library (https://github.com/unixod/uau)
#======================================================================#
include_directories(../uau)

#----------------------------------------------------------------------#

set(tasxip_SOURCES
	dataparser.cpp
	jsplugin.cpp
	jspluginscontainer.cpp
	jspluginsloader.cpp
	main.cpp
	mainwindow.cpp
	mainwindow_net.cpp
	plugininfodlg.cpp
	pluginsengine.cpp
    settings.cpp
)

set(tasxip_HEADERS
	dataparser.h
	jsplugin.h
	jspluginscontainer.h
	jspluginsloader.h
	mainwindow.h
	plugin.h
	plugininfodlg.h
	pluginsengine.h
	pluginsprovider.h
    settings.h
)

set(tasxip_FORMS
	mainwindow.ui
	plugininfodlg.ui
)

set(tasxip_RESOURCES
	resources.qrc
)

QT4_WRAP_CPP(tasxip_HEADERS_MOC ${tasxip_HEADERS})
QT4_WRAP_UI(tasxip_FORMS_HEADERS ${tasxip_FORMS})
QT4_ADD_RESOURCES(tasxip_RESOURCES_RCC ${tasxip_RESOURCES})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

if(WIN32)
	SET(GUI_TYPE WIN32)
elseif(APPLE)
	SET(GUI_TYPE MACOSX_BUNDLE)
endif()

add_executable(${PROJECT_NAME} ${GUI_TYPE}
	${tasxip_SOURCES}
	${tasxip_HEADERS_MOC}
	${tasxip_FORMS_HEADERS}
	${tasxip_RESOURCES_RCC}
)

target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BIN_DIR}
		SKIP_BUILD_RPATH TRUE
		VERSION "${APP_VERSION}"
)
