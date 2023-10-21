#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLabel>

#include "game.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "RPG_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }*/
    Game::dungeon;
    MainWindow w;
    w.setSize();
    QTimer::singleShot(40,&w,SLOT(show()));
    return a.exec();
}
