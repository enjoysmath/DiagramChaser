# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'double_spin_dialog.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_DoubleSpinDialog(object):
    def setupUi(self, DoubleSpinDialog):
        DoubleSpinDialog.setObjectName("DoubleSpinDialog")
        DoubleSpinDialog.resize(174, 67)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/img/galaxy.ico"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        DoubleSpinDialog.setWindowIcon(icon)
        self.gridLayout = QtWidgets.QGridLayout(DoubleSpinDialog)
        self.gridLayout.setObjectName("gridLayout")
        self.doubleSpinBox = QtWidgets.QDoubleSpinBox(DoubleSpinDialog)
        self.doubleSpinBox.setObjectName("doubleSpinBox")
        self.gridLayout.addWidget(self.doubleSpinBox, 0, 0, 1, 1)
        self.buttonBox = QtWidgets.QDialogButtonBox(DoubleSpinDialog)
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtWidgets.QDialogButtonBox.Cancel|QtWidgets.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName("buttonBox")
        self.gridLayout.addWidget(self.buttonBox, 1, 0, 1, 1)

        self.retranslateUi(DoubleSpinDialog)
        self.buttonBox.accepted.connect(DoubleSpinDialog.accept)
        self.buttonBox.rejected.connect(DoubleSpinDialog.reject)
        QtCore.QMetaObject.connectSlotsByName(DoubleSpinDialog)

    def retranslateUi(self, DoubleSpinDialog):
        _translate = QtCore.QCoreApplication.translate
        DoubleSpinDialog.setWindowTitle(_translate("DoubleSpinDialog", "DoubleSpinDialog"))
import resources_rc
