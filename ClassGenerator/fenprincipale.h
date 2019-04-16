#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QCheckBox>
#include <QDateEdit>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QTextEdit>
#include <QWidgetSet>

#define NUMGROUPBOX 3

class FenPrincipale : public QWidget
{
    Q_OBJECT
public:
    explicit FenPrincipale(QWidget *parent = nullptr);

public slots:
    void generateCode();
    void fillHeaderGuard(const QString);

private:
    QGroupBox* createDefinitionClasseGroup();
    QGroupBox* createOptionsGroup();
    QGroupBox* createCommentaireGroup();

    QGroupBox *groupBox[NUMGROUPBOX];

    /* Définition de la classe */
    QLineEdit *nom;
    QLineEdit *classeMere;

    /* La liste de includes */
    QCheckBox *includeQObjet;
    QCheckBox *includeQWidget;
    QCheckBox *includeQDialog;

    /* Options */
    QGroupBox *protectionHeader;
    QLineEdit *headerGuard;
    QCheckBox *genConstructeurBox;
    QCheckBox *genDestructeurBox;
    QCheckBox *licenceGPL;

    /* Ajout de commentaires */
    QLineEdit *auteur;
    QDateEdit *dateCreation;
    QTextEdit *roleClasse;

    /* Générer, quitter */
    QPushButton *generate;
    QPushButton *quitter;


};

#endif // FENPRINCIPALE_H
