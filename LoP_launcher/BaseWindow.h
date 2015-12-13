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

//! \file BaseWindow.h
//! \author Jean-loup Beaussart
//! \version 0.1
//! \copyright 2015,2016 Jean-loup Beaussart LGPLv3
//! \brief Header file for the class CBaseWindow. Base class for the main window.

#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

//! \class CBaseWindow
//! \brief This class inherits from QWidget, it's the class for the main window.
class CBaseWindow : public QWidget
{

	Q_OBJECT

public:

	//! \brief Constructor.
	CBaseWindow();

	//! \brief Virtual destructor.
	virtual ~CBaseWindow();

	//! \brief Create all the widgets, sizing and placing them in the window. Also connect the signals with the slots.
	//! \return Nothing
	void SetupUi();

public slots:

	//! \brief Slot that launch the game when activated.
	void slotLaunchGame();

signals:

	//! \brief Signal that is triggered to update the value of the progress bar.
	void sigUpdateBar(int value);

private:
	QVBoxLayout *mpVerticalLayout;
	QVBoxLayout *mpVerticalLayout_3;
	QHBoxLayout *mpHorizontalLayout_2;
	QSpacerItem *mpHorizontalSpacer_3;
	QLCDNumber *mpLcdNumber;
	QGraphicsView *mpGraphicsView;
	QSpacerItem *mpVerticalSpacer_2;
	QHBoxLayout *mpHorizontalLayout_5;
	QSpacerItem *mpHorizontalSpacer_5;
	QTimeEdit *mpTimeEdit;
	QSpacerItem *mpHorizontalSpacer_4;
	QHBoxLayout *mpHorizontalLayout_4;
	QSpacerItem *mpHorizontalSpacer_2;
	QProgressBar *mpProgressBar;
	QSpacerItem *mpHorizontalSpacer;
	QHBoxLayout *mpHorizontalLayout;
	QListView *mpListView;
	QVBoxLayout *mpVerticalLayout_2;
	QSpacerItem *mpVerticalSpacer;
	QHBoxLayout *mpHorizontalLayout_3;
	QPushButton *mpSettings_pushButton;
	QPushButton *mpClose_pushButton;
	QPushButton *mpPlay_pushButton;
};

