#include "fencodegenere.h"
#include <QVBoxLayout>
#include <QMessageBox>

FenCodeGenere::FenCodeGenere(const QString* generateCodeString)
{

    QVBoxLayout *vbox = new QVBoxLayout;

        codeText = new QTextEdit;
        codeText->clear();
        codeText->setPlainText(*generateCodeString);
            codeText->setReadOnly(true);
            codeText->setOverwriteMode(true);
            codeText->setFont(QFont("Courier"));
        fermeButton = new QPushButton;
        fermeButton->setText(tr("Fermer"));
        vbox->addWidget(codeText);
        vbox->addWidget(fermeButton);

        this->setLayout(vbox);
        this->resize(350, 500);

        QObject::connect(fermeButton, SIGNAL(clicked()), this, SLOT(confirmeFermeture()));
}

void FenCodeGenere::confirmeFermeture()
{
    int reponse = QMessageBox::question(this, tr("Confirmation"), tr("Êtes-vous sûr de vouloit fermer cette fenêtre ?"), QMessageBox::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes)
        this->done(QDialog::Accepted);
}
