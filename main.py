from PyQt5.QtGui import QFont
from core.app import App
import sys
from dialog.main_window import MainWindow

if __name__ == '__main__':
    app = App([])
    #app.setFont(QFont(app.font().family(), 12))
    app.setStyle('fusion')
    
    window = app.add_new_window()
    #window.add_new_language_view()
    window.show()
    
    sys.exit(app.exec_())