#include "stdafx.h"
#include "MainWindow.h"
#include <QtWidgets/QApplication>

// TODO remove - test code
#include "Node.h"
#include "DiagramEditorScene.h"
#include "GraphicsViewZoom.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    // TODO Remove - Test code
    auto view = new QGraphicsView();
    GraphicsViewZoom zoom(view);
    view->setScene(new DiagramEditorScene());
    view->scene()->setItemIndexMethod(QGraphicsScene::ItemIndexMethod::NoIndex);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    auto scene = view->scene();
    auto node = new Node();
    scene->addItem(node);

    node->update();
    auto node1 = new Node();
    node1->setParentItem(node);
    node1->update();
    node->update();
    node1->setBrush(QBrush(QColor(0, 0, 255)));
    node1->setToolTip("Blah sucka");

    auto node2 = new Node();
    node2->setParentItem(node);
    node2->update();
    node->update();
    node2->setBrush(QBrush(QColor(0, 0, 255)));
    node2->setToolTip("Blah sucka2");

    w.setCentralWidget(view);
    return a.exec();
}
