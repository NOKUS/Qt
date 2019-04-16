#ifndef FENCODEGENERE_H
#define FENCODEGENERE_H

#include <QDialog>
#include <QPushButton>
#include <QTextEdit>

class FenCodeGenere : public QDialog
{
    Q_OBJECT
public:
    FenCodeGenere(const QString* generateCodeText = NULL);

public slots:
    void confirmeFermeture();

private:
    QTextEdit *codeText;
    QPushButton *fermeButton;
};

#endif // FENCODEGENERE_H
