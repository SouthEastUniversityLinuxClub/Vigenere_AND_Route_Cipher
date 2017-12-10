#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#define MAX 100

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    char* vigenere(char key[],char word[]);
    char* antiVigenere(char key[], char* en_word);
    void route();
    void antiRoute();

    ~MainWindow();

        int square[27][27];
        char *key,*word,*en_word;

        char* grid;
        int colNum;

        int originalLength;
private slots:
        void on_pushButton_clicked();

        void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
