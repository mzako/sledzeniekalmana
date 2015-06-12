# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'kalman.ui'
#
# Created: Fri Jun 12 14:52:45 2015
#      by: PyQt4 UI code generator 4.9.3
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    _fromUtf8 = lambda s: s

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName(_fromUtf8("MainWindow"))
        MainWindow.resize(1024, 768)
        self.centralwidget = QtGui.QWidget(MainWindow)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.horizontalLayout_3 = QtGui.QHBoxLayout(self.centralwidget)
        self.horizontalLayout_3.setObjectName(_fromUtf8("horizontalLayout_3"))
        self.realColumn = QtGui.QWidget(self.centralwidget)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred, QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.realColumn.sizePolicy().hasHeightForWidth())
        self.realColumn.setSizePolicy(sizePolicy)
        self.realColumn.setObjectName(_fromUtf8("realColumn"))
        self.verticalLayout = QtGui.QVBoxLayout(self.realColumn)
        self.verticalLayout.setMargin(0)
        self.verticalLayout.setObjectName(_fromUtf8("verticalLayout"))
        self.realLabel = QtGui.QLabel(self.realColumn)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.realLabel.setFont(font)
        self.realLabel.setObjectName(_fromUtf8("realLabel"))
        self.verticalLayout.addWidget(self.realLabel)
        self.real = GLViewWidget(self.realColumn)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred, QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(2)
        sizePolicy.setHeightForWidth(self.real.sizePolicy().hasHeightForWidth())
        self.real.setSizePolicy(sizePolicy)
        self.real.setCursor(QtGui.QCursor(QtCore.Qt.ArrowCursor))
        self.real.setObjectName(_fromUtf8("real"))
        self.gridLayout = QtGui.QGridLayout(self.real)
        self.gridLayout.setMargin(0)
        self.gridLayout.setObjectName(_fromUtf8("gridLayout"))
        self.realMask = QtGui.QWidget(self.real)
        self.realMask.setCursor(QtGui.QCursor(QtCore.Qt.CrossCursor))
        self.realMask.setFocusPolicy(QtCore.Qt.ClickFocus)
        self.realMask.setObjectName(_fromUtf8("realMask"))
        self.gridLayout.addWidget(self.realMask, 1, 0, 1, 1)
        self.verticalLayout.addWidget(self.real)
        self.horizontalLayout_3.addWidget(self.realColumn)
        self.trackColumn = QtGui.QWidget(self.centralwidget)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred, QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.trackColumn.sizePolicy().hasHeightForWidth())
        self.trackColumn.setSizePolicy(sizePolicy)
        self.trackColumn.setObjectName(_fromUtf8("trackColumn"))
        self.verticalLayout_2 = QtGui.QVBoxLayout(self.trackColumn)
        self.verticalLayout_2.setMargin(0)
        self.verticalLayout_2.setObjectName(_fromUtf8("verticalLayout_2"))
        self.trackLabel = QtGui.QLabel(self.trackColumn)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.trackLabel.setFont(font)
        self.trackLabel.setObjectName(_fromUtf8("trackLabel"))
        self.verticalLayout_2.addWidget(self.trackLabel)
        self.track = GLViewWidget(self.trackColumn)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred, QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(2)
        sizePolicy.setHeightForWidth(self.track.sizePolicy().hasHeightForWidth())
        self.track.setSizePolicy(sizePolicy)
        self.track.setObjectName(_fromUtf8("track"))
        self.gridLayout_2 = QtGui.QGridLayout(self.track)
        self.gridLayout_2.setMargin(0)
        self.gridLayout_2.setObjectName(_fromUtf8("gridLayout_2"))
        self.trackMask = QtGui.QWidget(self.track)
        self.trackMask.setCursor(QtGui.QCursor(QtCore.Qt.CrossCursor))
        self.trackMask.setFocusPolicy(QtCore.Qt.ClickFocus)
        self.trackMask.setAutoFillBackground(False)
        self.trackMask.setObjectName(_fromUtf8("trackMask"))
        self.gridLayout_2.addWidget(self.trackMask, 0, 0, 1, 1)
        self.verticalLayout_2.addWidget(self.track)
        self.horizontalLayout_3.addWidget(self.trackColumn)
        MainWindow.setCentralWidget(self.centralwidget)
        self.actionExit = QtGui.QAction(MainWindow)
        self.actionExit.setMenuRole(QtGui.QAction.QuitRole)
        self.actionExit.setObjectName(_fromUtf8("actionExit"))
        self.actionExit_2 = QtGui.QAction(MainWindow)
        self.actionExit_2.setSoftKeyRole(QtGui.QAction.NegativeSoftKey)
        self.actionExit_2.setIconVisibleInMenu(False)
        self.actionExit_2.setPriority(QtGui.QAction.NormalPriority)
        self.actionExit_2.setObjectName(_fromUtf8("actionExit_2"))

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QtGui.QApplication.translate("MainWindow", "MainWindow", None, QtGui.QApplication.UnicodeUTF8))
        self.realLabel.setText(QtGui.QApplication.translate("MainWindow", "Real targets", None, QtGui.QApplication.UnicodeUTF8))
        self.trackLabel.setText(QtGui.QApplication.translate("MainWindow", "Targets tracking system", None, QtGui.QApplication.UnicodeUTF8))
        self.actionExit.setText(QtGui.QApplication.translate("MainWindow", "Exit", None, QtGui.QApplication.UnicodeUTF8))
        self.actionExit_2.setText(QtGui.QApplication.translate("MainWindow", "Exit", None, QtGui.QApplication.UnicodeUTF8))

from pyqtgraph.opengl import GLViewWidget

class MainWindow(QtGui.QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None, f=QtCore.Qt.WindowFlags()):
        QtGui.QMainWindow.__init__(self, parent, f)

        self.setupUi(self)

