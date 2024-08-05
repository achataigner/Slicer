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

#ifndef __qSlicerPrecompileVtkHeadersModuleWidget_h
#define __qSlicerPrecompileVtkHeadersModuleWidget_h

// Slicer includes
#include "qSlicerAbstractModuleWidget.h"

#include "qSlicerPrecompileVtkHeadersModuleExport.h"

class qSlicerPrecompileVtkHeadersModuleWidgetPrivate;
class vtkMRMLNode;

class Q_SLICER_QTMODULES_PRECOMPILEVTKHEADERS_EXPORT qSlicerPrecompileVtkHeadersModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerPrecompileVtkHeadersModuleWidget(QWidget *parent=0);
  virtual ~qSlicerPrecompileVtkHeadersModuleWidget();

public slots:


protected:
  QScopedPointer<qSlicerPrecompileVtkHeadersModuleWidgetPrivate> d_ptr;

  void setup() override;

private:
  Q_DECLARE_PRIVATE(qSlicerPrecompileVtkHeadersModuleWidget);
  Q_DISABLE_COPY(qSlicerPrecompileVtkHeadersModuleWidget);
};

#endif
