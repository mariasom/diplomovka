cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
  cmake_policy(SET CMP0071 NEW)
endif()

PROJECT(bioData)

find_package(VTK COMPONENTS
  
  vtkCommonColor
  vtkCommonCore
  vtkCommonDataModel
  vtkFiltersSources
  vtkInteractionStyle
  vtkInteractionImage
  vtkRenderingContextOpenGL2
  vtkRenderingCore
  vtkRenderingFreeType
  vtkRenderingAnnotation
  vtkRenderingGL2PSOpenGL2
  vtkRenderingOpenGL2
  vtkGUISupportQt
  vtkIOLegacy
  vtkIOXML
  vtkIOImage
  vtkFiltersGeometry
  vtkImagingSources
  vtkFiltersModeling
  QUIET
)

if (NOT VTK_FOUND)
  message("Skipping bioData: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")

if(vtkGUISupportQt_LOADED OR TARGET VTK::GUISupportQt)
  if (VTK_VERSION VERSION_LESS "8.90.0")
    # Instruct CMake to run moc automatically when needed.
    set(CMAKE_AUTOMOC ON)
  else()
     # Instruct CMake to run moc automatically when needed.
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
  endif()
  # We have ui files, this will bring in the macro: qt5_wrap_ui
  find_package(Qt5Widgets REQUIRED QUIET)
else()
  message(STATUS "GuiSupportQt not found.")
  return()
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB UI_FILES src/*.ui)
file(GLOB QT_WRAP src/*.h)
file(GLOB CXX_FILES src/*.cpp)

qt5_wrap_ui(UISrcs ${UI_FILES})

if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  # CMAKE_AUTOMOC in ON so the MOC headers will be automatically wrapped.
  add_executable(bioData MACOSX_BUNDLE
    ${CXX_FILES} ${UISrcs} ${QT_WRAP})
  qt5_use_modules(bioData Core Gui Help)
  target_link_libraries(bioData ${VTK_LIBRARIES})
else()
  # CMAKE_AUTOMOC in ON so the MOC headers will be automatically wrapped.
  add_executable(bioData MACOSX_BUNDLE
    ${CXX_FILES} ${UISrcs} ${QT_WRAP})
  qt5_use_modules(bioData Core Gui Help)
  target_link_libraries(bioData ${VTK_LIBRARIES})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS bioData
    MODULES ${VTK_LIBRARIES}
  )
endif()

add_custom_command(TARGET ${PROJECT_NAME}
                   POST_BUILD
                   COMMAND "windeployqt.exe" "$(OutDir)$(TargetName)$(TargetExt)"
                   COMMENT "Win deploy qt")