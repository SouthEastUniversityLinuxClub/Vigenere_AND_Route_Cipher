#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int i,j;
    for(i=1;i<27;i++)
    {
        for(j=1;j<27;j++)
        {
            square[i][j] = 63+i+j;
            if(square[i][j]>90)
                square[i][j] -= 26;
        }
    }

    ui->tabWidget->setTabText(0,"Vigenere Cipher");
    ui->tabWidget->setTabText(1,"Route Cipher");

    setWindowFlags(windowFlags() &~ Qt::WindowMinMaxButtonsHint);
}

char *MainWindow::vigenere(char key[], char word[])
{
    char* text = (char*) malloc(MAX*sizeof(char));
    int keyLength = strlen(key);
    int wordLength = strlen(word);
    int i,j,k;
    for(i=0;i<wordLength;i++)
    {
        if((word[i]>=65&&word[i]<=90)||(word[i]>=97&&word[i]<=122))
        {
            if(word[i]>=97&&word[i]<=122)
                k=word[i]-96;
            else
                k=word[i]-64;

            j=i%keyLength;
            text[i]=square[key[j]-96][k];
        }
        else
            text[i]=word[i];
    }
    text[i]='\0';
    return text;
}

char *MainWindow::antiVigenere(char key[], char *en_word)
{
    char* word = (char*) malloc(MAX*sizeof(char));
    int keyLength=strlen(key),wordLength=strlen(en_word);
    int i,k,m,n;
    for(i=0;i<wordLength;i++)
    {
        if(en_word[i]>=65&&en_word[i]<=90)
        {
            k=i%keyLength;
            m=key[k]-96;
            n=en_word[i] - square[m][1];
            if(n>=0)
                word[i] = 'a' +n;
            else
                word[i] = 'z'+n+1;
        }
        else
            word[i] = en_word[i];
    }
    word[i] = '\0';
    return word;
}

void MainWindow::route()
{
    grid = (char*) ui->PlainTextLineEdit2->text().toStdString().c_str();
    colNum =ui->ColumnNumberLineEdit->text().toInt();
    int textLength = strlen(grid);
    originalLength = strlen(grid);
    int remainder=0;
    if(colNum!=0)
    {
        remainder = textLength % colNum;
        if(remainder!=0)
        {
            int i;
            for(i=0;i<colNum-remainder;i++)
            {
                grid[textLength+i] = 'x';
            }
            grid[textLength+i] = '\0';
        }

        textLength = strlen(grid);
        //    QString test = QString::fromStdString(grid);
        //    ui->EncryptedWordLineEdit2->setText(test);

        int rowNum;
        rowNum=textLength/colNum;

        QString result = "";
        for(int i=0;i<colNum;i++)
        {
            for(int j=0;j<rowNum;j++)
            {
                result.append(QChar(grid[i+colNum*j]));
            }
        }
        ui->EncryptedWordLineEdit2->setText(result);
    }
}

void MainWindow::antiRoute()
{
    QString encrypted = ui->EncryptedWordLineEdit2->text();
    int rowNum = ui->ColumnNumberLineEdit->text().toInt();
    int colNum = encrypted.length()/rowNum;
    QString decrypted = "";
    int count = 0;
    for(int i=0;i<colNum;i++)
    {
        for(int j=0;j<rowNum;j++)
        {
            if(count<originalLength)
                decrypted.append(QChar(encrypted.at(i+colNum*j)));
            count++;
        }
    }

    ui->DecryptedWordLineEdit2->setText(decrypted);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    word = (char*)ui->PlainTextLineEdit->text().toStdString().c_str();
    key = (char*)ui->KeyLineEdit->text().toStdString().c_str();

    char* en_word = vigenere(key,word);
    std::string tempStr = en_word;
    QString encrypted = QString::fromStdString(tempStr);
    ui->EncryptedWordLineEdit->setText(encrypted);

    char* de_word = antiVigenere(key,en_word);
    tempStr = de_word;
    QString decrypted = QString::fromStdString(tempStr);
    ui->DecryptedWordLineEdit->setText(decrypted);
}

void MainWindow::on_pushButton_2_clicked()
{
    route();
    antiRoute();
}
