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
#include "qSlicerPrecompileVtkHeadersModuleWidget.h"
#include "ui_qSlicerPrecompileVtkHeadersModuleWidget.h"

//-----------------------------------------------------------------------------
class qSlicerPrecompileVtkHeadersModuleWidgetPrivate: public Ui_qSlicerPrecompileVtkHeadersModuleWidget
{
public:
  qSlicerPrecompileVtkHeadersModuleWidgetPrivate();
};

//-----------------------------------------------------------------------------
// qSlicerPrecompileVtkHeadersModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerPrecompileVtkHeadersModuleWidgetPrivate::qSlicerPrecompileVtkHeadersModuleWidgetPrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerPrecompileVtkHeadersModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerPrecompileVtkHeadersModuleWidget::qSlicerPrecompileVtkHeadersModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerPrecompileVtkHeadersModuleWidgetPrivate )
{
}

//-----------------------------------------------------------------------------
qSlicerPrecompileVtkHeadersModuleWidget::~qSlicerPrecompileVtkHeadersModuleWidget()
{
}

//-----------------------------------------------------------------------------
void qSlicerPrecompileVtkHeadersModuleWidget::setup()
{
  Q_D(qSlicerPrecompileVtkHeadersModuleWidget);
  d->setupUi(this);
  this->Superclass::setup();
}
