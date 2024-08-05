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

// PrecompileItkHeaders Logic includes
#include <vtkSlicerPrecompileItkHeadersLogic.h>

// PrecompileItkHeaders includes
#include "qSlicerPrecompileItkHeadersModule.h"
#include "qSlicerPrecompileItkHeadersModuleWidget.h"

//-----------------------------------------------------------------------------
class qSlicerPrecompileItkHeadersModulePrivate
{
public:
  qSlicerPrecompileItkHeadersModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerPrecompileItkHeadersModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerPrecompileItkHeadersModulePrivate::qSlicerPrecompileItkHeadersModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerPrecompileItkHeadersModule methods

//-----------------------------------------------------------------------------
qSlicerPrecompileItkHeadersModule::qSlicerPrecompileItkHeadersModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerPrecompileItkHeadersModulePrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerPrecompileItkHeadersModule::~qSlicerPrecompileItkHeadersModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerPrecompileItkHeadersModule::helpText() const
{
  return "This is a loadable module that can be bundled in an extension";
}

//-----------------------------------------------------------------------------
QString qSlicerPrecompileItkHeadersModule::acknowledgementText() const
{
  return "This work was partially funded by NIH grant NXNNXXNNNNNN-NNXN";
}

//-----------------------------------------------------------------------------
QStringList qSlicerPrecompileItkHeadersModule::contributors() const
{
  QStringList moduleContributors;
  moduleContributors << QString("John Doe (AnyWare Corp.)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerPrecompileItkHeadersModule::icon() const
{
  return QIcon(":/Icons/PrecompileItkHeaders.png");
}

//-----------------------------------------------------------------------------
QStringList qSlicerPrecompileItkHeadersModule::categories() const
{
  return QStringList() << "Examples";
}

//-----------------------------------------------------------------------------
QStringList qSlicerPrecompileItkHeadersModule::dependencies() const
{
  return QStringList();
}

//-----------------------------------------------------------------------------
void qSlicerPrecompileItkHeadersModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation* qSlicerPrecompileItkHeadersModule
::createWidgetRepresentation()
{
  return new qSlicerPrecompileItkHeadersModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerPrecompileItkHeadersModule::createLogic()
{
  return vtkSlicerPrecompileItkHeadersLogic::New();
}
