#include <QApplication>
#include <QTranslator>

#include "fencodegenere.h"
#include "fenprincipale.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Récupère le code 2 lettres ("fr_FR" ici) de la langue du PC.
    QString local = QLocale::system().name().section('_', 0, 0);

    QTranslator *translator = new QTranslator;
    translator->load(QString("classgenerator_") + local);
    app.installTranslator(translator);

    FenPrincipale fenetre;

    fenetre.show();

    return app.exec();
}
