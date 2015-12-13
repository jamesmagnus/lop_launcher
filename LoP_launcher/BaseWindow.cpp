// Copyright © 2015,2016 Jean-loup Beaussart 
//
// This file is part of Light of Paladin Launcher.
// 
// Light of Paladin Launcher is free software : you can redistribute it and / or modify
// it under the terms of the LGPL Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Light of Paladin Launcher is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// LGPL Lesser General Public License for more details.
// 
// You should have received a copy of the LGPL Lesser General Public License
// along with Light of Paladin Launcher. If not, see < http://www.gnu.org/licenses/ >.

//! \file BaseWindow.cpp
//! \author Jean-loup Beaussart
//! \version 0.1
//! \copyright 2015,2016 Jean-loup Beaussart LGPLv3
//! \brief Source file with implementation of CBaseWindow's methods. QT code to set up the GUI.

#include "BaseWindow.h"
#include <iostream>

CBaseWindow::CBaseWindow()
{
	mpVerticalLayout = nullptr;
	mpVerticalLayout_3 = nullptr;
	mpHorizontalLayout_2 = nullptr;
	mpHorizontalSpacer_3 = nullptr;
	mpLcdNumber = nullptr;
	mpGraphicsView = nullptr;
	mpVerticalSpacer_2 = nullptr;
	mpHorizontalLayout_5 = nullptr;
	mpHorizontalSpacer_5 = nullptr;
	mpTimeEdit = nullptr;
	mpHorizontalSpacer_4 = nullptr;
	mpHorizontalLayout_4 = nullptr;
	mpHorizontalSpacer_2 = nullptr;
	mpProgressBar = nullptr;
	mpHorizontalSpacer = nullptr;
	mpHorizontalLayout = nullptr;
	mpListView = nullptr;
	mpVerticalLayout_2 = nullptr;
	mpVerticalSpacer = nullptr;
	mpHorizontalLayout_3 = nullptr;
	mpSettings_pushButton = nullptr;
	mpClose_pushButton = nullptr;
	mpPlay_pushButton = nullptr;
}


CBaseWindow::~CBaseWindow()
{
}

void CBaseWindow::SetupUi()
{
	mpVerticalLayout = new QVBoxLayout(this);
	mpVerticalLayout->setObjectName(QStringLiteral("verticalLayout"));
	mpVerticalLayout_3 = new QVBoxLayout();
	mpVerticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
	mpHorizontalLayout_2 = new QHBoxLayout();
	mpHorizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
	mpHorizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

	mpHorizontalLayout_2->addItem(mpHorizontalSpacer_3);

	mpLcdNumber = new QLCDNumber(this);
	mpLcdNumber->setObjectName(QStringLiteral("lcdNumber"));
	mpLcdNumber->setCursor(QCursor(Qt::IBeamCursor));
	mpLcdNumber->setSmallDecimalPoint(false);
	mpLcdNumber->setSegmentStyle(QLCDNumber::Flat);
	mpLcdNumber->setProperty("value", QVariant(12.15));

	mpHorizontalLayout_2->addWidget(mpLcdNumber);


	mpVerticalLayout_3->addLayout(mpHorizontalLayout_2);

	mpGraphicsView = new QGraphicsView(this);
	mpGraphicsView->setObjectName(QStringLiteral("graphicsView"));

	mpVerticalLayout_3->addWidget(mpGraphicsView);

	mpVerticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

	mpVerticalLayout_3->addItem(mpVerticalSpacer_2);

	mpHorizontalLayout_5 = new QHBoxLayout();
	mpHorizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
	mpHorizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

	mpHorizontalLayout_5->addItem(mpHorizontalSpacer_5);

	mpTimeEdit = new QTimeEdit(this);
	mpTimeEdit->setObjectName(QStringLiteral("timeEdit"));
	mpTimeEdit->setReadOnly(true);

	mpHorizontalLayout_5->addWidget(mpTimeEdit);

	mpHorizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

	mpHorizontalLayout_5->addItem(mpHorizontalSpacer_4);


	mpVerticalLayout_3->addLayout(mpHorizontalLayout_5);

	mpHorizontalLayout_4 = new QHBoxLayout();
	mpHorizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
	mpHorizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

	mpHorizontalLayout_4->addItem(mpHorizontalSpacer_2);

	mpProgressBar = new QProgressBar(this);
	mpProgressBar->setObjectName(QStringLiteral("progressBar"));
	mpProgressBar->setValue(0);
	mpProgressBar->setInvertedAppearance(false);

	mpHorizontalLayout_4->addWidget(mpProgressBar);

	mpHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

	mpHorizontalLayout_4->addItem(mpHorizontalSpacer);


	mpVerticalLayout_3->addLayout(mpHorizontalLayout_4);


	mpVerticalLayout->addLayout(mpVerticalLayout_3);


	mpHorizontalLayout = new QHBoxLayout();
	mpHorizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
	mpListView = new QListView(this);
	mpListView->setObjectName(QStringLiteral("listView"));

	mpHorizontalLayout->addWidget(mpListView);

	mpVerticalLayout_2 = new QVBoxLayout();
	mpVerticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
	mpVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

	mpVerticalLayout_2->addItem(mpVerticalSpacer);

	mpHorizontalLayout_3 = new QHBoxLayout();
	mpHorizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
	mpSettings_pushButton = new QPushButton(this);
	mpSettings_pushButton->setObjectName(QStringLiteral("settings_pushButton"));
	mpSettings_pushButton->setCursor(QCursor(Qt::PointingHandCursor));

	mpHorizontalLayout_3->addWidget(mpSettings_pushButton);

	mpClose_pushButton = new QPushButton(this);
	mpClose_pushButton->setObjectName(QStringLiteral("close_pushButton"));
	mpClose_pushButton->setCursor(QCursor(Qt::PointingHandCursor));

	mpHorizontalLayout_3->addWidget(mpClose_pushButton);

	mpPlay_pushButton = new QPushButton(this);
	mpPlay_pushButton->setObjectName(QStringLiteral("play_pushButton"));
	mpPlay_pushButton->setCursor(QCursor(Qt::PointingHandCursor));

	mpHorizontalLayout_3->addWidget(mpPlay_pushButton);


	mpVerticalLayout_2->addLayout(mpHorizontalLayout_3);


	mpHorizontalLayout->addLayout(mpVerticalLayout_2);


	mpVerticalLayout->addLayout(mpHorizontalLayout);

	QObject::connect(mpClose_pushButton, SIGNAL(released()), this, SLOT(close()));
	QObject::connect(this, SIGNAL(sigUpdateBar(int)), mpProgressBar, SLOT(setValue(int)));
	QObject::connect(mpPlay_pushButton, SIGNAL(released()), this, SLOT(slotLaunchGame()));

	QMetaObject::connectSlotsByName(this);

	this->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
	mpProgressBar->setFormat(QApplication::translate("MainWindow", "%p%", "kljkljljljl"));
	mpSettings_pushButton->setText(QApplication::translate("MainWindow", "Pr\303\251f\303\251rences", 0));
	mpClose_pushButton->setText(QApplication::translate("MainWindow", "Fermer", 0));
	mpPlay_pushButton->setText(QApplication::translate("MainWindow", "Jouer", 0));
}

void CBaseWindow::slotLaunchGame()
{
	//TODO call other process
}


