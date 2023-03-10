# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'canvas_grid_dialog.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_CanvasGridDialog(object):
    def setupUi(self, CanvasGridDialog):
        CanvasGridDialog.setObjectName("CanvasGridDialog")
        CanvasGridDialog.resize(284, 126)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/img/galaxy.ico"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        CanvasGridDialog.setWindowIcon(icon)
        CanvasGridDialog.setModal(False)
        self.gridLayout_2 = QtWidgets.QGridLayout(CanvasGridDialog)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.enabledCheck = QtWidgets.QCheckBox(CanvasGridDialog)
        self.enabledCheck.setChecked(True)
        self.enabledCheck.setObjectName("enabledCheck")
        self.gridLayout_2.addWidget(self.enabledCheck, 2, 0, 1, 1)
        self.groupBox = QtWidgets.QGroupBox(CanvasGridDialog)
        self.groupBox.setObjectName("groupBox")
        self.gridLayout = QtWidgets.QGridLayout(self.groupBox)
        self.gridLayout.setObjectName("gridLayout")
        self.label_2 = QtWidgets.QLabel(self.groupBox)
        self.label_2.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.label_2.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label_2.setObjectName("label_2")
        self.gridLayout.addWidget(self.label_2, 1, 1, 1, 1)
        self.ySpacingSpin = QtWidgets.QSpinBox(self.groupBox)
        self.ySpacingSpin.setAccelerated(True)
        self.ySpacingSpin.setMinimum(10)
        self.ySpacingSpin.setMaximum(1000)
        self.ySpacingSpin.setSingleStep(10)
        self.ySpacingSpin.setProperty("value", 100)
        self.ySpacingSpin.setObjectName("ySpacingSpin")
        self.gridLayout.addWidget(self.ySpacingSpin, 1, 2, 1, 1)
        self.label = QtWidgets.QLabel(self.groupBox)
        self.label.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.label.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label.setObjectName("label")
        self.gridLayout.addWidget(self.label, 0, 1, 1, 1)
        self.xyLockedCheck = QtWidgets.QCheckBox(self.groupBox)
        self.xyLockedCheck.setChecked(True)
        self.xyLockedCheck.setObjectName("xyLockedCheck")
        self.gridLayout.addWidget(self.xyLockedCheck, 0, 3, 1, 1)
        self.xSpacingSpin = QtWidgets.QSpinBox(self.groupBox)
        self.xSpacingSpin.setAccelerated(True)
        self.xSpacingSpin.setMinimum(10)
        self.xSpacingSpin.setMaximum(1000)
        self.xSpacingSpin.setSingleStep(10)
        self.xSpacingSpin.setProperty("value", 100)
        self.xSpacingSpin.setObjectName("xSpacingSpin")
        self.gridLayout.addWidget(self.xSpacingSpin, 0, 2, 1, 1)
        self.gridLayout_2.addWidget(self.groupBox, 0, 1, 7, 2)
        self.visibleCheck = QtWidgets.QCheckBox(CanvasGridDialog)
        self.visibleCheck.setChecked(True)
        self.visibleCheck.setObjectName("visibleCheck")
        self.gridLayout_2.addWidget(self.visibleCheck, 3, 0, 1, 1)
        self.buttonBox = QtWidgets.QDialogButtonBox(CanvasGridDialog)
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtWidgets.QDialogButtonBox.Cancel|QtWidgets.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName("buttonBox")
        self.gridLayout_2.addWidget(self.buttonBox, 7, 0, 1, 3)

        self.retranslateUi(CanvasGridDialog)
        self.buttonBox.accepted.connect(CanvasGridDialog.accept)
        self.buttonBox.rejected.connect(CanvasGridDialog.reject)
        QtCore.QMetaObject.connectSlotsByName(CanvasGridDialog)

    def retranslateUi(self, CanvasGridDialog):
        _translate = QtCore.QCoreApplication.translate
        CanvasGridDialog.setWindowTitle(_translate("CanvasGridDialog", "2D Snap Grid"))
        self.enabledCheck.setText(_translate("CanvasGridDialog", "Enabled"))
        self.groupBox.setTitle(_translate("CanvasGridDialog", "Spacing"))
        self.label_2.setText(_translate("CanvasGridDialog", "Y-axis:"))
        self.ySpacingSpin.setSuffix(_translate("CanvasGridDialog", "  pixels"))
        self.label.setText(_translate("CanvasGridDialog", "X-axis:"))
        self.xyLockedCheck.setText(_translate("CanvasGridDialog", "Locked"))
        self.xSpacingSpin.setSuffix(_translate("CanvasGridDialog", "  pixels"))
        self.visibleCheck.setText(_translate("CanvasGridDialog", "Visible"))
import resources_rc
