/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

// PrecompileVtkHeaders Logic includes
#include <vtkSlicerPrecompileVtkHeadersLogic.h>

// PrecompileVtkHeaders includes
#include "qSlicerPrecompileVtkHeadersModule.h"
#include "qSlicerPrecompileVtkHeadersModuleWidget.h"

//-----------------------------------------------------------------------------
class qSlicerPrecompileVtkHeadersModulePrivate
{
public:
  qSlicerPrecompileVtkHeadersModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerPrecompileVtkHeadersModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerPrecompileVtkHeadersModulePrivate::qSlicerPrecompileVtkHeadersModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerPrecompileVtkHeadersModule methods

//-----------------------------------------------------------------------------
qSlicerPrecompileVtkHeadersModule::qSlicerPrecompileVtkHeadersModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerPrecompileVtkHeadersModulePrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerPrecompileVtkHeadersModule::~qSlicerPrecompileVtkHeadersModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerPrecompileVtkHeadersModule::helpText() const
{
  return "This is a loadable module that can be bundled in an extension";
}

//-----------------------------------------------------------------------------
QString qSlicerPrecompileVtkHeadersModule::acknowledgementText() const
{
  return "This work was partially funded by NIH grant NXNNXXNNNNNN-NNXN";
}

//-----------------------------------------------------------------------------
QStringList qSlicerPrecompileVtkHeadersModule::contributors() const
{
  QStringList moduleContributors;
  moduleContributors << QString("John Doe (AnyWare Corp.)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerPrecompileVtkHeadersModule::icon() const
{
  return QIcon(":/Icons/PrecompileVtkHeaders.png");
}

//-----------------------------------------------------------------------------
QStringList qSlicerPrecompileVtkHeadersModule::categories() const
{
  return QStringList() << "Examples";
}

//-----------------------------------------------------------------------------
QStringList qSlicerPrecompileVtkHeadersModule::dependencies() const
{
  return QStringList();
}

//-----------------------------------------------------------------------------
void qSlicerPrecompileVtkHeadersModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation* qSlicerPrecompileVtkHeadersModule
::createWidgetRepresentation()
{
  return new qSlicerPrecompileVtkHeadersModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerPrecompileVtkHeadersModule::createLogic()
{
  return vtkSlicerPrecompileVtkHeadersLogic::New();
}
