/*
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-2014, Open Source Modelica Consortium (OSMC),
 * c/o Linköpings universitet, Department of Computer and Information Science,
 * SE-58183 Linköping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF GPL VERSION 3 LICENSE OR
 * THIS OSMC PUBLIC LICENSE (OSMC-PL) VERSION 1.2.
 * ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES
 * RECIPIENT'S ACCEPTANCE OF THE OSMC PUBLIC LICENSE OR THE GPL VERSION 3,
 * ACCORDING TO RECIPIENTS CHOICE.
 *
 * The OpenModelica software and the Open Source Modelica
 * Consortium (OSMC) Public License (OSMC-PL) are obtained
 * from OSMC, either from the above address,
 * from the URLs: http://www.ida.liu.se/projects/OpenModelica or
 * http://www.openmodelica.org, and in the OpenModelica distribution.
 * GNU version 3 is obtained from: http://www.gnu.org/copyleft/gpl.html.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without
 * even the implied warranty of  MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE, EXCEPT AS EXPRESSLY SET FORTH
 * IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE CONDITIONS OF OSMC-PL.
 *
 * See the full OSMC Public License conditions for more details.
 *
 */
/*
 * @author Adeel Asghar <adeel.asghar@liu.se>
 */

#include "Util/Utilities.h"


#include <QApplication>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QStylePainter>
#include <QPainter>
#include <QColorDialog>



Label::Label(QWidget *parent, Qt::WindowFlags flags)
  : QLabel(parent, flags), mElideMode(Qt::ElideNone), mText("")
{
  setTextInteractionFlags(Qt::TextSelectableByMouse);
}

Label::Label(const QString &text, QWidget *parent, Qt::WindowFlags flags)
  : QLabel(text, parent, flags), mElideMode(Qt::ElideNone), mText(text)
{
  setTextInteractionFlags(Qt::TextSelectableByMouse);
  setToolTip(text);
}

QSize Label::minimumSizeHint() const
{
  if (pixmap() != NULL || mElideMode == Qt::ElideNone) {
    return QLabel::minimumSizeHint();
  }
  const QFontMetrics &fm = fontMetrics();
  QSize size(fm.width("..."), fm.height()+5);
  return size;
}

QSize Label::sizeHint() const
{
  if (pixmap() != NULL || mElideMode == Qt::ElideNone)
    return QLabel::sizeHint();
  const QFontMetrics& fm = fontMetrics();
  QSize size(fm.width(mText), fm.height()+5);
  return size;
}

void Label::setText(const QString &text)
{
  mText = text;
  setToolTip(text);
  QLabel::setText(text);
}

void Label::resizeEvent(QResizeEvent *event)
{
  if (mElideMode != Qt::ElideNone) {
    QFontMetrics fm(fontMetrics());
    QString str = fm.elidedText(mText, mElideMode, event->size().width());
    QLabel::setText(str);
  }
  QLabel::resizeEvent(event);
}

Label* Utilities::getHeadingLabel(QString heading)
{
  Label *pHeadingLabel = new Label(heading);
 //pHeadingLabel->setFont(QFont(Helper::systemFontInfo.family(), Helper::headingFontSize));
  pHeadingLabel->setFont(QFont("Monospace", 18));

  return pHeadingLabel;
}
QFrame* Utilities::getHeadingLine()
{
  QFrame *pHeadingLine = new QFrame();
  pHeadingLine->setFrameShape(QFrame::HLine);
  pHeadingLine->setFrameShadow(QFrame::Sunken);
  return pHeadingLine;
}

