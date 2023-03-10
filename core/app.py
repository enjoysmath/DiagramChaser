from PyQt5.QtWidgets import QApplication, QDialog
from dialog.main_window import MainWindow
from PyQt5.QtCore import Qt
from dialog.font_dialog import FontDialog

class App(QApplication):    
   def __init__(self, *args, **kwargs):
      super().__init__(*args, **kwargs)
      self._windows = []
      self._appFontDialog = FontDialog()
      self._appFontDialog.font_changed.connect(self.setFont)
      self._appFontDialog.setWindowTitle('Set app font')

   def show_app_font_dialog(self):
      self._appFontDialog.exec_()

   def topmost_main_window(self):
      topLevel = self.topLevelWidgets()
      for widget in topLevel:
         if isinstance(widget, MainWindow):
            return widget

   def add_new_window(self):
      window = MainWindow()
      self._windows.append(window)
      window.show()
      return window

   def setFont(self, font):
      super().setFont(font)
      for window in self._windows:
         for langView in window.language_views():
            for item in langView.scene().items():
               if isinstance(item, Text):
                  item.setFont(font)
      self._appFontDialog.set_font(font)