# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'integer_spin_dialog.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_IntegerSpinDialog(object):
    def setupUi(self, IntegerSpinDialog):
        IntegerSpinDialog.setObjectName("IntegerSpinDialog")
        IntegerSpinDialog.resize(174, 94)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/img/galaxy.ico"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        IntegerSpinDialog.setWindowIcon(icon)
        self.gridLayout = QtWidgets.QGridLayout(IntegerSpinDialog)
        self.gridLayout.setObjectName("gridLayout")
        self.spinBox = QtWidgets.QSpinBox(IntegerSpinDialog)
        self.spinBox.setObjectName("spinBox")
        self.gridLayout.addWidget(self.spinBox, 0, 0, 1, 1)
        self.buttonBox = QtWidgets.QDialogButtonBox(IntegerSpinDialog)
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtWidgets.QDialogButtonBox.Cancel|QtWidgets.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName("buttonBox")
        self.gridLayout.addWidget(self.buttonBox, 1, 0, 1, 1)

        self.retranslateUi(IntegerSpinDialog)
        self.buttonBox.accepted.connect(IntegerSpinDialog.accept)
        self.buttonBox.rejected.connect(IntegerSpinDialog.reject)
        QtCore.QMetaObject.connectSlotsByName(IntegerSpinDialog)

    def retranslateUi(self, IntegerSpinDialog):
        _translate = QtCore.QCoreApplication.translate
        IntegerSpinDialog.setWindowTitle(_translate("IntegerSpinDialog", "Integer Spin Dialog"))
import resources_rc
