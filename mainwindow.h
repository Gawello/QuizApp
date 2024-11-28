#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pytanie.h"

#include <QList>
#include <QString>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startBtn_clicked();
    void on_aBtn_clicked();
    void on_bBtn_clicked();
    void on_cBtn_clicked();
    void on_dBtn_clicked();

private:
    Ui::MainWindow *ui;

    QList<Pytanie> questions; // Lista pytań wczytanych z pliku
    int currentQuestionIndex; // Indeks bieżącego pytania
    int correctAnswersCount; // Licznik punktów

    void hideAnsButtons();
    void showAnsButtons();
    void loadCurrentQuestion(); // Wczytaj bieżące pytanie
    void checkAnswer(QPushButton* selectedButton); // Sprawdź odpowiedź użytkownika
    void highlightCorrectButton(const QString& correctAnswer);
    void resetButtonStyles();
    void showFinalScore();

};

#endif // MAINWINDOW_H
