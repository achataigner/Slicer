
#-----------------------------------------------------------------------------
set(MODULE_NAME PrecompileQtHeaders)

string(TOUPPER ${MODULE_NAME} MODULE_NAME_UPPER)

#-----------------------------------------------------------------------------
add_subdirectory(Logic)
add_subdirectory(Widgets)

#-----------------------------------------------------------------------------
set(MODULE_EXPORT_DIRECTIVE "Q_SLICER_QTMODULES_${MODULE_NAME_UPPER}_EXPORT")

# Current_{source,binary} and Slicer_{Libs,Base} already included
set(MODULE_INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_SOURCE_DIR}/Logic
  ${CMAKE_CURRENT_BINARY_DIR}/Logic
  ${CMAKE_CURRENT_SOURCE_DIR}/Widgets
  ${CMAKE_CURRENT_BINARY_DIR}/Widgets
  )

set(MODULE_SRCS
  qSlicer${MODULE_NAME}Module.cxx
  qSlicer${MODULE_NAME}Module.h
  qSlicer${MODULE_NAME}ModuleWidget.cxx
  qSlicer${MODULE_NAME}ModuleWidget.h
  )

set(MODULE_MOC_SRCS
  qSlicer${MODULE_NAME}Module.h
  qSlicer${MODULE_NAME}ModuleWidget.h
  )

set(MODULE_UI_SRCS
  Resources/UI/qSlicer${MODULE_NAME}ModuleWidget.ui
  )

set(MODULE_TARGET_LIBRARIES
  vtkSlicer${MODULE_NAME}ModuleLogic
  qSlicer${MODULE_NAME}ModuleWidgets
  )

set(MODULE_RESOURCES
  Resources/qSlicer${MODULE_NAME}Module.qrc
  )

#-----------------------------------------------------------------------------
slicerMacroBuildLoadableModule(
  NAME ${MODULE_NAME}
  EXPORT_DIRECTIVE ${MODULE_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${MODULE_INCLUDE_DIRECTORIES}
  SRCS ${MODULE_SRCS}
  MOC_SRCS ${MODULE_MOC_SRCS}
  UI_SRCS ${MODULE_UI_SRCS}
  TARGET_LIBRARIES ${MODULE_TARGET_LIBRARIES}
  RESOURCES ${MODULE_RESOURCES}
  WITH_GENERIC_TESTS
  )

get_property(qt_core_lib_file_path TARGET "Qt5::Core" PROPERTY LOCATION_RELEASE)
get_filename_component(qt_core_lib_dir ${qt_core_lib_file_path} PATH)

set(qt_core_include_dir "${qt_core_lib_dir}/../include/QtCore")
set(qt_widgets_include_dir "${qt_core_lib_dir}/../include/QtWidgets")

  # Precompile only low level most common headers because header precompilation takes time
set(precompiled_headers
"${qt_core_include_dir}/QDateTime"
"${qt_core_include_dir}/QDebug"
"${qt_core_include_dir}/QDir"
"${qt_core_include_dir}/QFile"
"${qt_core_include_dir}/QFileInfo"
"${qt_core_include_dir}/QHash"
"${qt_core_include_dir}/QList"
"${qt_core_include_dir}/QMap"
"${qt_core_include_dir}/QMetaType"
"${qt_core_include_dir}/QObject"
"${qt_core_include_dir}/QPointer"
"${qt_core_include_dir}/QSettings"
"${qt_core_include_dir}/QSharedPointer"
"${qt_core_include_dir}/QString"
"${qt_core_include_dir}/QStringList"
"${qt_core_include_dir}/QTimer"
"${qt_core_include_dir}/QUrl"
"${qt_core_include_dir}/QVariant"

"${qt_widgets_include_dir}/QAction"
"${qt_widgets_include_dir}/QApplication"
"${qt_widgets_include_dir}/QDialog"
"${qt_widgets_include_dir}/QLabel"
"${qt_widgets_include_dir}/QMessageBox"
"${qt_widgets_include_dir}/QVBoxLayout"
"${qt_widgets_include_dir}/QWidget"
)

target_precompile_headers(${lib_name} PUBLIC ${precompiled_headers})
  

#-----------------------------------------------------------------------------
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()
