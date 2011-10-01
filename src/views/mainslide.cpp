/*
    This file is part of open-pdf-presenter.

    open-pdf-presenter is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    open-pdf-presenter is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with open-pdf-presenter.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mainslide.h"

#include <QDesktopWidget>
#include <QApplication>

MainSlideViewImpl::MainSlideViewImpl(int usableWidth, QWidget * parent) : QWidget(parent) {
	this->usableWidth = usableWidth;
	this->layout = new QVBoxLayout(this);
	this->setLayout(this->layout);
	this->layout->setSpacing(0);
	this->layout->setMargin(0);
	this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	this->blackBlankScreen = new QWidget(this);
	this->blackBlankScreen->setStyleSheet("background-color: black;");
	this->blackBlankScreen->setVisible(false);
	this->layout->addWidget(this->blackBlankScreen);
	this->whiteBlankScreen = new QWidget(this);
	this->whiteBlankScreen->setStyleSheet("background-color: white;");
	this->whiteBlankScreen->setVisible(false);
	this->layout->addWidget(this->whiteBlankScreen);

	this->slideLabel = new QLabel(this);
	this->layout->addWidget(this->slideLabel);
	this->slideLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	this->slideLabel->setAlignment(Qt::AlignCenter);
}

void MainSlideViewImpl::setCurrentSlide(QPixmap slide, bool scale) {
	this->blackBlankScreen->setVisible(false);
	this->whiteBlankScreen->setVisible(false);
	this->slideLabel->setVisible(true);

	if (scale)
		this->slideLabel->setPixmap(slide.scaledToWidth(this->usableWidth, Qt::SmoothTransformation));
	else
		this->slideLabel->setPixmap(slide);
}

void MainSlideViewImpl::setBlackBlankScreen() {
	this->whiteBlankScreen->setVisible(false);
	this->slideLabel->setVisible(false);
	QDesktopWidget * desktopwidget = QApplication::desktop();
	this->blackBlankScreen->setGeometry(desktopwidget->screenGeometry(this->slideLabel));
	this->blackBlankScreen->setVisible(true);
}

void MainSlideViewImpl::setWhiteBlankScreen() {
	this->blackBlankScreen->setVisible(false);
	this->slideLabel->setVisible(false);
	QDesktopWidget * desktopwidget = QApplication::desktop();
	this->whiteBlankScreen->setGeometry(desktopwidget->screenGeometry(this->slideLabel));
	this->whiteBlankScreen->setVisible(true);
}

QWidget * MainSlideViewImpl::asWidget() {
	return this;
}
