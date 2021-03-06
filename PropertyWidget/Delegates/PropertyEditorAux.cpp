/*
 * Copyright (c) 2012 - 2014, the Qtinuum project.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * <qtinuum.team@gmail.com>
 */

#include "PropertyEditorAux.h"
#include "PropertyDelegate.h"

#include <QHBoxLayout>
#include <QKeyEvent>

QtnLineEditBttn::QtnLineEditBttn(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    lineEdit = new QLineEdit(this);
    layout->addWidget(lineEdit);

    toolButton = new QToolButton(this);
    toolButton->setText("...");
    toolButton->setFocusPolicy(Qt::StrongFocus);
    layout->addWidget(toolButton);

    setFocusProxy(lineEdit);
    setAutoFillBackground(true);
}

bool qtnAcceptForLineEdit(QKeyEvent *keyEvent)
{
    if (keyEvent->type() != QEvent::KeyPress)
        return false;

    // any printable key press is acceptable
    QString text = keyEvent->text();
    return (text.size() == 1 && text[0].isPrint());
}

void qtnInitLineEdit(QLineEdit *lineEdit, QtnInplaceInfo *inplaceInfo)
{
    if (!lineEdit || !inplaceInfo)
        return;

    if (!lineEdit->isReadOnly() && (inplaceInfo->activationEvent->type() == QEvent::KeyPress))
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(inplaceInfo->activationEvent);
        if (qtnAcceptForLineEdit(keyEvent))
        {
            lineEdit->setText(keyEvent->text());
            return;
        }
    }
    else
    {
        lineEdit->selectAll();
    }
}
