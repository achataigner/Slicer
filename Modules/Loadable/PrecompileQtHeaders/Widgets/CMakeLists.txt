project(qSlicer${MODULE_NAME}ModuleWidgets)

set(KIT ${PROJECT_NAME})

set(${KIT}_EXPORT_DIRECTIVE "Q_SLICER_MODULE_${MODULE_NAME_UPPER}_WIDGETS_EXPORT")

set(${KIT}_INCLUDE_DIRECTORIES
  )

set(${KIT}_SRCS
  qSlicer${MODULE_NAME}FooBarWidget.cxx
  qSlicer${MODULE_NAME}FooBarWidget.h
  )

set(${KIT}_MOC_SRCS
  qSlicer${MODULE_NAME}FooBarWidget.h
  )

set(${KIT}_UI_SRCS
  ../Resources/UI/qSlicer${MODULE_NAME}FooBarWidget.ui
  )

set(${KIT}_RESOURCES
  ../Resources/qSlicer${MODULE_NAME}Module.qrc
  )

set(${KIT}_TARGET_LIBRARIES
  vtkSlicer${MODULE_NAME}ModuleLogic
  )

#-----------------------------------------------------------------------------
SlicerMacroBuildModuleWidgets(
  NAME ${KIT}
  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
  SRCS ${${KIT}_SRCS}
  MOC_SRCS ${${KIT}_MOC_SRCS}
  UI_SRCS ${${KIT}_UI_SRCS}
  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES}
  RESOURCES ${${KIT}_RESOURCES}
  WRAP_PYTHONQT
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

target_precompile_headers(${KIT} PUBLIC ${precompiled_headers})
