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

// Qt includes
#include <QDebug>

// Slicer includes
#include "qSlicerPrecompileQtHeadersModuleWidget.h"
#include "ui_qSlicerPrecompileQtHeadersModuleWidget.h"

//-----------------------------------------------------------------------------
class qSlicerPrecompileQtHeadersModuleWidgetPrivate: public Ui_qSlicerPrecompileQtHeadersModuleWidget
{
public:
  qSlicerPrecompileQtHeadersModuleWidgetPrivate();
};

//-----------------------------------------------------------------------------
// qSlicerPrecompileQtHeadersModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerPrecompileQtHeadersModuleWidgetPrivate::qSlicerPrecompileQtHeadersModuleWidgetPrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerPrecompileQtHeadersModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerPrecompileQtHeadersModuleWidget::qSlicerPrecompileQtHeadersModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerPrecompileQtHeadersModuleWidgetPrivate )
{
}

//-----------------------------------------------------------------------------
qSlicerPrecompileQtHeadersModuleWidget::~qSlicerPrecompileQtHeadersModuleWidget()
{
}

//-----------------------------------------------------------------------------
void qSlicerPrecompileQtHeadersModuleWidget::setup()
{
  Q_D(qSlicerPrecompileQtHeadersModuleWidget);
  d->setupUi(this);
  this->Superclass::setup();
}
