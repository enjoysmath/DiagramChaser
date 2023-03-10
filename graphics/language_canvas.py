from PyQt5.QtWidgets import QGraphicsScene, QUndoStack, QApplication, QMenu
from PyQt5.QtGui import QColor, QPainter, QPen, QTransform, QDrag
from PyQt5.QtCore import QPointF, Qt, QMimeData, pyqtSignal
from functools import cmp_to_key
from graphics.text import Text
from graphics.object import Object
from graphics.collision_responsive import CollisionResponsive
import _pickle as pickle
from graphics.arrow import Arrow
from core.qt_tools import (SimpleBrush, Pen, filter_out_descendents, first_ancestor_of_type, \
                      simple_max_contrasting_color)
from graphics.container import Container
from graphics.connectable import Connectable
from graphics.control_point import ControlPoint
from dialog.canvas_grid_dialog import CanvasGridDialog
from graphics.graphics_shape import GraphicsShape
from graphics.deletable import Deletable
from dialog.color_dialog import ColorDialog
from graphics.snappable import Snappable

class LanguageCanvas(QGraphicsScene):
    mouse_pressed = pyqtSignal(QPointF)
    init_object_text = '🌍'
    init_arrow_text = '🚀'
    default_background_color = QColor(237, 255, 241)
    
    def __init__(self):
        super().__init__()
        self._backgroundBrush = None
        self.setBackgroundBrush(SimpleBrush(self.default_background_color))
        self._undoStack = QUndoStack()
        self._startPos = None
        self._movedItems = {}
        self._editText = None
        self._textBeforeEdit = None
        self._controlPoint = None
        self._controlPointSkip1Release = False
        self._gridOrigin = QPointF(0,0)
        self.grid_dialog = CanvasGridDialog()
        self.grid_dialog.redraw_canvas_background.connect(self.update)
        self.background_color_dialog = ColorDialog(title='Background color')
        self.background_color_dialog.currentColorChanged.connect(lambda col: self.setBackgroundBrush(SimpleBrush(col)))
        self.background_color_dialog.setCurrentColor(self.backgroundBrush().color())
                
    def __setstate__(self, data:dict):
        self.__init__()
        self.setBackgroundBrush(data['background brush'])
        self._gridOrigin = data['grid origin']
        self.grid_dialog._setState(data['grid dialog'])
        self.background_color_dialog._setState(data['color dialog'])
        for item in data['items']:
            self.addItem(item)
    
    def __getstate__(self):
        items = list(filter_out_descendents(self.items()))
        return {
            'background brush' : self._backgroundBrush,
            'grid origin' : self._gridOrigin,
            'grid dialog' : self.grid_dialog._getState({}),
            'items' : items,
            'color dialog' : self.background_color_dialog._getState({}),
        }
    
    def addItem(self, item:GraphicsShape):
        if isinstance(item, Deletable):
            item.delete_requested.connect(lambda: self.delete_items([item]))
        super().addItem(item)
        item.update()
    
    def setBackgroundBrush(self, brush:SimpleBrush):
        if brush != self._backgroundBrush:
            self._backgroundBrush = brush
            super().setBackgroundBrush(brush)
            self.update()
            
    def backgroundBrush(self):
        return self._backgroundBrush

    def mouseDoubleClickEvent(self, event):
        item = self.itemAt(event.scenePos(), QTransform())
        super().mouseDoubleClickEvent(event)
                        
    def _addObject(self, X:Object, parent=None):
        from core.undo_cmd import AddObject
        self._undoStack.push(AddObject(X, canvas=self, parent=parent))
        
    def _addArrow(self, f:Arrow, parent=None):
        from core.undo_cmd import AddArrow
        self._undoStack.push(AddArrow(f, canvas=self, parent=parent))
            
    def undo_command(self):
        self._undoStack.undo()
        
    def redo_command(self):
        self._undoStack.redo()
        
    def mouseMoveEvent(self, event):
        delta = event.scenePos() - event.lastScenePos()
        super().mouseMoveEvent(event)
        
    def mousePressEvent(self, event):
        self.mouse_pressed.emit(event.scenePos())        
        item = self.itemAt(event.scenePos(), QTransform())      
        super().mousePressEvent(event)
        
    #TODO: deleting an item must update each UndoCmd with items
    
    def mouseReleaseEvent(self, event):
        super().mouseReleaseEvent(event)
        
    def set_edit_text(self, text:Text):
        if self._editText != text:
            if self._editText:
                self.done_editing_text()
            self._textBeforeEdit = text.toHtml()
            self._editText = text
            
    def delete_selected(self):
        items = self.selectedItems()
        if items:
            self.delete_items(items)
            
    def delete_items(self, items):
        from core.undo_cmd import DeleteItems
        self._undoStack.push(DeleteItems(items, canvas=self))
            
    def done_editing_text(self):
        if self._editText:
            from core.undo_cmd import EditText
            self._editText.done_editing()
            self._undoStack.push(EditText(self._editText, before=self._textBeforeEdit))
            self._editText = None        
            self._textBeforeEdit = None
                       
    @staticmethod
    def pickle_items(items:list):
        items = LanguageCanvas.copy_items(items)
        items = pickle.dumps(items)
        return items
        
    @staticmethod
    def copy_items(items:list):
        data = pickle.dumps(items)    
        data = pickle.loads(data)
        return data
        
    @staticmethod
    def unpickle_items(data):
        items = pickle.loads(data)
        return items
            
    def place_control_point(self, ctrl_point, skip_release=False):
        window = QApplication.instance().topmost_main_window()
        self._collisionResponseSave = window.collision_response_enabled
        window.set_collision_response_enabled(False)        
        if ctrl_point.parentItem():
            ctrl_point.parentItem().set_at_point(ctrl_point, None)
            self._controlPoint = ctrl_point
            self._controlPointSkip1Release = skip_release
            return True
        return False
        
    def connect_arrow_by_control_point(self, items):
        parent = self._controlPoint.parentItem()
        for item in items:
            if item is not parent and isinstance(item, Connectable):
                self._controlPoint.parentItem().set_at_point(self._controlPoint, item) 
                break
        self.end_placing_control_point()
        
    def grid_sizex(self):
        return self.grid_dialog.xSpacingSpin.value()
    
    def grid_sizey(self):
        return self.grid_dialog.ySpacingSpin.value()
    
    def snap_grid_enabled(self):
        return self.grid_dialog.enabledCheck.isChecked()
    
    def snap_grid_visible(self):
        return self.grid_dialog.visibleCheck.isChecked()
    
    def grid_origin(self):
        return self._gridOrigin
       
    def drawBackground(self, painter, rect):
        super().drawBackground(painter, rect)
        if self.snap_grid_enabled() and self.snap_grid_visible():
            painter.setRenderHints(QPainter.Antialiasing)
            gridx = int(self.grid_sizex() + 0.5)
            gridy = int(self.grid_sizey() + 0.5)
            w = 0.02 * (gridx + gridy) / 2
            painter.setPen(QPen(simple_max_contrasting_color(self.backgroundBrush().color()), w))
            points = []                 # Adding to a list and then drawing is much faster
            o = self.grid_origin()
            ox = o.x() % gridx
            oy = o.y() % gridy
            left = int(rect.left()) - (int(rect.left()) % gridx)
            top = int(rect.top()) - (int(rect.top()) % gridy)
            for x in range(left, int(rect.right()), gridx):
                for y in range(top, int(rect.bottom()), gridy):
                    points.append(QPointF(x + ox, y + oy))
            if points:
                painter.drawPoints(*points)
            # Draw grid origin
            #painter.drawLine(QLineF(o.x(), o.y() - 20, o.x(), o.y() + 20))
            #painter.drawLine(QLineF(o.x() - 20, o.y(), o.x() + 20, o.y()))          
            
    def build_context_menu(self, screen_pos):
        menu = QMenu()
        menu.addAction('Snap grid...').triggered.connect(lambda b: self.show_snap_grid_dialog(screen_pos))
        menu.addAction('Background color...').triggered.connect(lambda b: self.background_color_dialog.exec_())
        return menu    
    
    def show_snap_grid_dialog(self, screen_pos):
        result = self.grid_dialog.exec_()
        if result == self.grid_dialog.Accepted:
            return
        self.grid_dialog.reset_to_previous()
                
    def contextMenuEvent(self, event):
        item = self.itemAt(event.scenePos(), QTransform())
        if not item:
            menu = self.build_context_menu(event.screenPos())        
            menu.exec_(event.screenPos())
        else:
            super().contextMenuEvent(event)
            
    @property
    def is_moving_items(self):
        return self._movedItems or self._controlPoint is not None
            
    def end_placing_control_point(self):
        if self._controlPoint:                
            point = self._controlPoint
            self._controlPoint = None
            self._controlPointSkip1Release = False
            QApplication.instance().topmost_main_window().set_collision_response_enabled(self._collisionResponseSave)
            point.parentItem().update()
            
    @property
    def items_being_moved(self):
        return self._movedItems