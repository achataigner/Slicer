import os
import sys
import traceback

from __main__ import qt, ctk, slicer

import SlicerWizard.ExtensionDescription
import SlicerWizard.ExtensionProject
import SlicerWizard.TemplateManager
import SlicerWizard.Utilities

from ExtensionWizardLib import *

#-----------------------------------------------------------------------------
def _settingsList(settings, key):
  # Return a settings value as a list (even if empty or a single value)

  value = settings.value(key)

  if isinstance(value, basestring):
    return [value]

  return [] if value is None else value

#=============================================================================
#
# ExtensionWizard
#
#=============================================================================
class ExtensionWizard:
  #---------------------------------------------------------------------------
  def __init__(self, parent):
    parent.title = "Extension Wizard"
    parent.icon = qt.QIcon(":/Icons/Medium/ExtensionWizard.png")
    parent.categories = ["Developer Tools"]
    parent.dependencies = []
    parent.contributors = ["Matthew Woehlke (Kitware)"]
    parent.helpText = """
    This module provides tools to create and manage extensions from within Slicer.
    """
    parent.acknowledgementText = """
    This work is supported by NA-MIC, NAC, BIRN, NCIGT, and the Slicer Community.
    See <a>http://www.slicer.org</a> for details."""
    self.parent = parent

    self.settingsPanel = SettingsPanel()
    slicer.app.settingsDialog().addPanel("Extension Wizard", self.settingsPanel)

#=============================================================================
#
# ExtensionWizardWidget
#
#=============================================================================
class ExtensionWizardWidget:
  #---------------------------------------------------------------------------
  def __init__(self, parent = None):
    if not parent:
      self.parent = qt.QWidget()
      self.parent.setLayout(qt.QVBoxLayout())

    else:
      self.parent = parent

    self.layout = self.parent.layout()

    if not parent:
      self.setup()
      self.parent.show()

    self.extensionProject = None
    self.extensionDescription = None
    self.extensionLocation = None

    self.templateManager = None
    self.setupTemplates()

  #---------------------------------------------------------------------------
  def setup(self):
    # Instantiate and connect widgets ...

    icon = self.parent.style().standardIcon(qt.QStyle.SP_ArrowForward)
    iconSize = qt.QSize(22, 22)

    def createToolButton(text):
      tb = qt.QToolButton()

      tb.text = text
      tb.icon = icon

      font = tb.font
      font.setBold(True)
      font.setPixelSize(14)
      tb.font = font

      tb.iconSize = iconSize
      tb.toolButtonStyle = qt.Qt.ToolButtonTextBesideIcon
      tb.autoRaise = True

      return tb

    def createReadOnlyLineEdit():
      le = qt.QLineEdit()
      le.readOnly = True
      le.frame = False
      le.styleSheet = "QLineEdit { background:transparent; }"
      le.cursor = qt.QCursor(qt.Qt.IBeamCursor)
      return le

    #
    # Tools Area
    #
    self.toolsCollapsibleButton = ctk.ctkCollapsibleButton()
    self.toolsCollapsibleButton.text = "Extension Tools"
    self.layout.addWidget(self.toolsCollapsibleButton)

    self.createExtensionButton = createToolButton("Create Extension")
    self.createExtensionButton.connect('clicked(bool)', self.createExtension)

    self.selectExtensionButton = createToolButton("Select Extension")
    self.selectExtensionButton.connect('clicked(bool)', self.selectExtension)

    toolsLayout = qt.QVBoxLayout(self.toolsCollapsibleButton)
    toolsLayout.addWidget(self.createExtensionButton)
    toolsLayout.addWidget(self.selectExtensionButton)

    #
    # Editor Area
    #
    self.editorCollapsibleButton = ctk.ctkCollapsibleButton()
    self.editorCollapsibleButton.text = "Extension Editor"
    self.editorCollapsibleButton.enabled = False
    self.editorCollapsibleButton.collapsed = True
    self.layout.addWidget(self.editorCollapsibleButton)

    self.extensionNameField = createReadOnlyLineEdit()
    self.extensionLocationField = createReadOnlyLineEdit()
    self.extensionRepositoryField = createReadOnlyLineEdit()

    self.extensionContentsModel = qt.QFileSystemModel()
    self.extensionContentsView = qt.QTreeView()
    self.extensionContentsView.setModel(self.extensionContentsModel)
    self.extensionContentsView.sortingEnabled = True
    self.extensionContentsView.hideColumn(3)

    self.createExtensionModuleButton = createToolButton("Add Module to Extension")
    self.createExtensionModuleButton.connect('clicked(bool)',
                                             self.createExtensionModule)

    self.editExtensionMetadataButton = createToolButton("Edit Extension Metadata")
    self.editExtensionMetadataButton.connect('clicked(bool)',
                                             self.editExtensionMetadata)

    editorLayout = qt.QFormLayout(self.editorCollapsibleButton)
    editorLayout.addRow("Name:", self.extensionNameField)
    editorLayout.addRow("Location:", self.extensionLocationField)
    editorLayout.addRow("Repository:", self.extensionRepositoryField)
    editorLayout.addRow("Contents:", self.extensionContentsView)
    editorLayout.addRow(self.createExtensionModuleButton)
    editorLayout.addRow(self.editExtensionMetadataButton)

    # Add vertical spacer
    self.layout.addStretch(1)

  #---------------------------------------------------------------------------
  def cleanup(self):
    pass

  #---------------------------------------------------------------------------
  def setupTemplates(self):
    self.templateManager = SlicerWizard.TemplateManager()

    builtinPath = builtinTemplatePath()
    if builtinPath is not None:
      try:
        self.templateManager.addPath(builtinPath)
      except:
        qt.qWarning("failed to add built-in template path %r" % builtinPath)
        qt.qWarning(traceback.format_exc())

    # Read base template paths
    s = qt.QSettings()
    for path in _settingsList(s, userTemplatePathKey()):
      try:
        self.templateManager.addPath(path)
      except:
        qt.qWarning("failed to add template path %r" % path)
        qt.qWarning(traceback.format_exc())

    # Read per-category template paths
    s.beginGroup(userTemplatePathKey())
    for c in s.allKeys():
      for path in _settingsList(s, c):
        try:
          self.templateManager.addCategoryPath(c, path)
        except:
          mp = (c, path)
          qt.qWarning("failed to add template path %r for category %r" % mp)
          qt.qWarning(traceback.format_exc())

  #---------------------------------------------------------------------------
  def createExtension(self):
    dlg = CreateComponentDialog("extension", self.parent.window())
    dlg.setTemplates(self.templateManager.templates("extensions"))

    while dlg.exec_() == qt.QDialog.Accepted:
      try:
        path = self.templateManager.copyTemplate(
                 dlg.destination, "extensions",
                 dlg.componentType, dlg.componentName)

      except:
        md = qt.QMessageBox(self.parent.window())
        md.icon = qt.QMessageBox.Critical
        md.text = "An error occurred while trying to create the extension."
        md.detailedText = traceback.format_exc()
        md.standardButtons = qt.QMessageBox.Retry | qt.QMessageBox.Close
        if md.exec_() != qt.QMessageBox.Retry:
          return

        continue

      if self.selectExtension(path):
        self.editExtensionMetadata()

      return

  #---------------------------------------------------------------------------
  def selectExtension(self, path=None):
    if path is None or isinstance(path, bool):
      path = qt.QFileDialog.getExistingDirectory(
               self.parent.window(), "Select Extension...",
               self.extensionLocation)

    if not len(path):
      return False

    # Attempt to open extension
    try:
      repo = SlicerWizard.Utilities.getRepo(path)

      if repo is None:
        xd = SlicerWizard.ExtensionDescription(sourcedir=path)

      else:
        xd = SlicerWizard.ExtensionDescription(repo=repo)
        path = SlicerWizard.Utilities.localRoot(repo)

      xp = SlicerWizard.ExtensionProject(path)

    except:
      md = qt.QMessageBox(self.parent.window())
      md.icon = qt.QMessageBox.Critical
      md.text = "Failed to open extension '%s'." % path
      md.detailedText = traceback.format_exc()
      md.standardButtons = qt.QMessageBox.Close
      md.exec_()
      return False

    # Enable and show edit section
    self.editorCollapsibleButton.enabled = True
    self.editorCollapsibleButton.collapsed = False

    # Populate edit information
    self.extensionNameField.text = xp.project
    self.extensionLocationField.text = path

    if xd.scmurl == "NA":
      if repo is None:
        repoText = "(none)"
      elif hasattr(repo, "remotes"):
        repoText = "(local git repository)"
      else:
        repoText = "(unknown local repository)"

      self.extensionRepositoryField.clear()
      self.extensionRepositoryField.placeholderText = repoText

    else:
      self.extensionRepositoryField.text = xd.scmurl

    ri = self.extensionContentsModel.setRootPath(path)
    self.extensionContentsView.setRootIndex(ri)

    w = self.extensionContentsView.width
    self.extensionContentsView.setColumnWidth(0, (w * 4) / 9)

    # Prompt to load scripted modules from extension
    self.loadModules(path)

    # Store extension location, project and description for later use
    self.extensionProject = xp
    self.extensionDescription = xd
    self.extensionLocation = path
    return True

  #---------------------------------------------------------------------------
  def loadModules(self, path, depth=1):
    # Get list of modules in specified path
    modules = ModuleInfo.findModules(path, depth)

    # Determine which modules in above are not already loaded
    factory = slicer.app.moduleManager().factoryManager()
    loadedModules = factory.instantiatedModuleNames()

    candidates = [m for m in modules if m.key not in loadedModules]

    # Prompt to load additional module(s)
    if len(candidates):
      dlg = LoadModulesDialog(self.parent.window())
      dlg.setModules(candidates)

      if dlg.exec_() == qt.QDialog.Accepted:
        modulesToLoad = dlg.selectedModules

        # Add module(s) to permanent search paths, if requested
        if dlg.addToSearchPaths:
          settings = slicer.app.revisionUserSettings()
          rawSearchPaths = list(_settingsList(settings, "Modules/AdditionalPaths"))
          searchPaths = [qt.QDir(path) for path in rawSearchPaths]
          modified = False

          for module in modulesToLoad:
            rawPath = os.path.dirname(module.path)
            path = qt.QDir(rawPath)
            if not path in searchPaths:
              searchPaths.append(path)
              rawSearchPaths.append(rawPath)
              modified = True

          if modified:
            settings.setValue("Modules/AdditionalPaths", rawSearchPaths)

        # Register requested module(s)
        failed = []

        for module in modulesToLoad:
          factory.registerModule(qt.QFileInfo(module.path))
          if not factory.isRegistered(module.key):
            failed.append(module)

        if len(failed):
          md = qt.QMessageBox(self.parent.window())
          md.icon = qt.QMessageBox.Critical
          md.standardButtons = qt.QMessageBox.Close
          md.windowTitle = "Module loading failed"

          if len(failed) > 1:
            md.text = "The following modules could not be registered:"

          else:
            md.text = "The '%s' module could not be registered:" % failed[0].key

          failedFormat = "<ul><li>%(key)s<br/>(%(path)s)</li></ul>"
          md.informativeText = "".join(
            [failedFormat % m.__dict__ for m in failed])

          md.exec_()
          return

        # Instantiate and load requested module(s)
        if not factory.loadModules([module.key for module in modulesToLoad]):
          md = qt.QMessageBox(self.parent.window())
          md.icon = qt.QMessageBox.Critical
          md.standardButtons = qt.QMessageBox.Close
          md.windowTitle = "Error loading module(s)"
          md.text = ("The module factory manager reported an error. "
                     "One or more of the requested module(s) and/or "
                     "dependencies thereof may not have been loaded.")
          md.exec_()

  #---------------------------------------------------------------------------
  def createExtensionModule(self):
    if (self.extensionLocation is None):
      # Action shouldn't be enabled if no extension is selected, but guard
      # against that just in case...
      return

    dlg = CreateComponentDialog("module", self.parent.window())
    dlg.setTemplates(self.templateManager.templates("modules"),
                     default="scripted")
    dlg.showDestination = False

    while dlg.exec_() == qt.QDialog.Accepted:
      name = dlg.componentName

      try:
        self.templateManager.copyTemplate(self.extensionLocation, "modules",
                                          dlg.componentType, name)

      except:
        md = qt.QMessageBox(self.parent.window())
        md.icon = qt.QMessageBox.Critical
        md.text = "An error occurred while trying to create the module."
        md.detailedText = traceback.format_exc()
        md.standardButtons = qt.QMessageBox.Retry | qt.QMessageBox.Close
        if md.exec_() != qt.QMessageBox.Retry:
          return

        continue

      try:
        self.extensionProject.addModule(name)
        self.extensionProject.save()

      except:
        md = qt.QMessageBox(self.parent.window())
        md.icon = qt.QMessageBox.Critical
        md.text = "An error occurred while adding the module to the extension."
        md.informativeText = "The module has been created, but the extension" \
                             " CMakeLists.txt could not be updated. In order" \
                             " to include the module in the extension build," \
                             " you will need to update the extension" \
                             " CMakeLists.txt by hand."
        md.detailedText = traceback.format_exc()
        md.standardButtons = qt.QMessageBox.Close
        md.exec_()

      self.loadModules(os.path.join(self.extensionLocation, name), depth=0)
      return

  #---------------------------------------------------------------------------
  def editExtensionMetadata(self):
    xd = self.extensionDescription
    xp = self.extensionProject

    dlg = EditExtensionMetadataDialog(self.parent.window())
    dlg.project = xp.project
    dlg.category = xd.category
    dlg.description = xd.description
    dlg.contributors = xd.contributors

    if dlg.exec_() == qt.QDialog.Accepted:
      # Update cached metadata
      xd.category = dlg.category
      xd.description = dlg.description
      xd.contributors = dlg.contributors

      # Write changes to extension project file (CMakeLists.txt)
      xp.project = dlg.project
      xp.setValue("EXTENSION_CATEGORY", xd.category)
      xp.setValue("EXTENSION_DESCRIPTION", xd.description)
      xp.setValue("EXTENSION_CONTRIBUTORS", xd.contributors)
      xp.save()

      # Update the displayed extension name
      self.extensionNameField.text = xp.project
