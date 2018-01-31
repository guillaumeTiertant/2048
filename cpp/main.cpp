#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include "./cpp/contexte.h"


int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    Contexte* myApp= new Contexte;

    QQuickView view;
    view.resize(400, 800);
    view.setMinimumSize(QSize(400,600));
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    QQmlContext* ctx = view.rootContext();
    myApp->setContext( ctx );

    view.setSource(QUrl("qrc:///qml/main.qml"));
    view.show();

    return a.exec();
}
