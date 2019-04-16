#include <QApplication>
#include <QCheckBox>
#include <QDateEdit>
#include <QFile>
#include <QFormLayout>
#include <QGridLayout>
#include <QIODevice>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTextStream>

#include <iostream>

#include "fenprincipale.h"
#include "fencodegenere.h"

FenPrincipale::FenPrincipale(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("Class Generator"));
    QGridLayout *grid = new QGridLayout;

    groupBox[0] = createDefinitionClasseGroup();
    grid->addWidget(groupBox[0], 0, 0, 1, 4);

    groupBox[1] = createOptionsGroup();
    grid->addWidget(groupBox[1], 1, 0, 1, 4);

    groupBox[2] = createCommentaireGroup();
    grid->addWidget(groupBox[2], 2, 0, 1, 4);

    generate = new QPushButton(tr("Générer !", "Permet la génération du code source"));
    quitter = new QPushButton(tr("Quitter", "On quitte le menu de remplissage des options sans/après avoir générer le code"));

    grid->addWidget(generate, 3, 2);
    grid->addWidget(quitter, 3, 3);


    this->setLayout(grid);

    QObject::connect(nom, SIGNAL(textChanged(QString)), this, SLOT(fillHeaderGuard(QString)));

    QObject::connect(generate, SIGNAL(clicked()), this, SLOT(generateCode()));
    QObject::connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));


}

QGroupBox* FenPrincipale::createDefinitionClasseGroup()
{
    QGroupBox *gBox = new QGroupBox(tr("Definition de la classe"));

        nom = new QLineEdit;
        classeMere = new QLineEdit;

        QFormLayout* formLayout = new QFormLayout;
        formLayout->addRow(tr("&Nom : "), nom);
        formLayout->addRow(tr("Classe &mère : "), classeMere);
        gBox->setLayout(formLayout);

    return  gBox;
}

/* Creation du groupBox Options */
QGroupBox* FenPrincipale::createOptionsGroup()
{
    QGroupBox *gBox = new QGroupBox(tr("Options"));

        protectionHeader = new QGroupBox(tr("Protéger le &header contre les inclusions multiples"));
            protectionHeader->setCheckable(true);
            headerGuard = new QLineEdit;
            headerGuard->setPlaceholderText(tr("HEADER_NOMCLASS"));
            QHBoxLayout *hLayout = new QHBoxLayout;
            hLayout->addWidget(headerGuard);
            protectionHeader->setLayout(hLayout);

        genConstructeurBox = new QCheckBox(tr("Générer un &constructeur par défaut"));
        genDestructeurBox = new QCheckBox(tr("Générer un &destructeur"));

        QGridLayout *grid = new QGridLayout;
        grid->addWidget(protectionHeader, 0, 0);
        grid->addWidget(genConstructeurBox, 1, 0);
        grid->addWidget(genDestructeurBox, 2, 0);

        gBox->setLayout(grid);
    return gBox;

}

/* Creation du groupBox Ajouter de commentaires */

QGroupBox* FenPrincipale::createCommentaireGroup()
{
    QGroupBox *gBox = new QGroupBox(tr("Ajouter des commentaires"));
        gBox->setCheckable(true);

        auteur = new QLineEdit;
        dateCreation = new QDateEdit;
            dateCreation->setDisplayFormat("dd/MM/yyyy");
            //dateCreation->setCalendarPopup(true);
            dateCreation->setDate(QDate::currentDate());
            dateCreation->setMinimumDate(QDate(2008, 05, 23));
        roleClasse = new QTextEdit;
        /*
            roleClasse->setPlainText(
                        "Cère un personnage de type \"Magicien\".\n"
                        "Peut être spécialisé en :\n"
                        "- MagiecieBlanc \n"
                        "- MagicienNoir");
        */
            roleClasse->setAcceptRichText(true);
            licenceGPL = new QCheckBox(tr("Inclure la licence GPL"));

        QFormLayout *formLayout = new QFormLayout;
            formLayout->addRow(tr("&Auteur%n(s) : ", ""), auteur);
            formLayout->addRow(tr("Da&te de création : "), dateCreation);
            formLayout->addRow(tr("&Role de la classe : "), roleClasse);
            formLayout->addRow(licenceGPL);
        gBox->setLayout(formLayout);
    return gBox;
}

void FenPrincipale::generateCode()
{
    /* On commence par s'assurer que au
     * moins le nom de la class est saisi */
    if (nom->text().isEmpty())
        {
            QMessageBox::critical(this, tr("Erreur"), tr("Veuillez entrer au moins un nom de classe"));
            return; // Arrêt de la méthode
        }

    QString code;

    /* On Rempli le corps de la classe en premier*/
    code += "\nclass " + nom->text();
    if (!classeMere->text().isEmpty())
        code += ": public " + classeMere->text();

    /* Remplissage du constructeur et destructeur*/
    code += "\n{\n\tpublic:";
    if (genConstructeurBox->isChecked())
        code += "\n\t\t" + nom->text() + "();";

    if (genDestructeurBox->isChecked())
        code += "\n\t\t~" + nom->text() + "();";


    code += "\n\n\tprotected:\n\n";
    code += "\tprivate:\n\n};\n";

    /* Remplissage de la protection
     * des header contre les appels multiples*/
    QString defineHeader;
    if (protectionHeader->isChecked())
    {
        defineHeader = "#ifndef " + headerGuard->text().toUpper() + "\n";
        defineHeader += "#define " + headerGuard->text().toUpper() + "\n\n";
        code = defineHeader + code;
        code += "\n#endif \t/*" + headerGuard->text().toUpper() + "*/";
    }


    if (groupBox[2]->isChecked())
        code ="/*\n"
              +tr("Auteur:\t") + (auteur->text()) + "\n"
              +tr("Date de creation :\t") + dateCreation->text() + "\n"
              +tr("Role :\n") + roleClasse->toPlainText() +"\n*/ \n\n" + code;

    if (licenceGPL->isChecked())
    {
        QFile *file = new QFile("GNUGPL.tex");
        if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
            return;
        QTextStream in(file);
        code = "/*\n" + in.readAll() +"\n*/\n\n" + code;
    }

    FenCodeGenere fenetreCode(&code);
    fenetreCode.exec();

}

void FenPrincipale::fillHeaderGuard(const QString text)
{
    headerGuard->setText("HEADER_" + text.toUpper());
}
