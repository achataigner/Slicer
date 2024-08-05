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
#include "qSlicerPrecompileItkHeadersModuleWidget.h"
#include "ui_qSlicerPrecompileItkHeadersModuleWidget.h"

//-----------------------------------------------------------------------------
class qSlicerPrecompileItkHeadersModuleWidgetPrivate: public Ui_qSlicerPrecompileItkHeadersModuleWidget
{
public:
  qSlicerPrecompileItkHeadersModuleWidgetPrivate();
};

//-----------------------------------------------------------------------------
// qSlicerPrecompileItkHeadersModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerPrecompileItkHeadersModuleWidgetPrivate::qSlicerPrecompileItkHeadersModuleWidgetPrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerPrecompileItkHeadersModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerPrecompileItkHeadersModuleWidget::qSlicerPrecompileItkHeadersModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerPrecompileItkHeadersModuleWidgetPrivate )
{
}

//-----------------------------------------------------------------------------
qSlicerPrecompileItkHeadersModuleWidget::~qSlicerPrecompileItkHeadersModuleWidget()
{
}

//-----------------------------------------------------------------------------
void qSlicerPrecompileItkHeadersModuleWidget::setup()
{
  Q_D(qSlicerPrecompileItkHeadersModuleWidget);
  d->setupUi(this);
  this->Superclass::setup();
}
