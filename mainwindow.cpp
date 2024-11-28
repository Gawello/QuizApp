#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "pytanie.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentQuestionIndex(0)
    , correctAnswersCount(0) // Dodane zliczanie poprawnych odpowiedzi

{
    ui->setupUi(this);

    // Hide buttons on start
    hideAnsButtons();
    ui->label->setText("ROZPOCZNIJ QUIZ!");
    ui->startBtn->setText("START!");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hideAnsButtons() {
    ui->aBtn->hide();
    ui->bBtn->hide();
    ui->cBtn->hide();
    ui->dBtn->hide();

    ui->startBtn->show();
}

void MainWindow::showAnsButtons() {
    ui->aBtn->show();
    ui->bBtn->show();
    ui->cBtn->show();
    ui->dBtn->show();

    ui->startBtn->hide();
}

void MainWindow::on_startBtn_clicked()
{
    // Wczytaj pytania z pliku CSV
    // QString filePath = "/Pytania.csv";
    QString filePath = QCoreApplication::applicationDirPath() + "/Pytania.csv";
    questions = Pytanie::wczytajPytaniaZPliku(filePath);

    if (questions.isEmpty()) {
        ui->label->setText("Brak pytań w pliku!");
        return;
    }

    currentQuestionIndex = 0; // Resetuj indeks pytań
    correctAnswersCount = 0;  // Resetuj liczbę poprawnych odpowiedzi
    loadCurrentQuestion(); // Załaduj pierwsze pytanie

    showAnsButtons();
}

void MainWindow::loadCurrentQuestion() {
    if (currentQuestionIndex >= questions.size()) {
        showFinalScore(); // Wyświetl wynik na końcu quizu
        return;
    }

    // Przywróć domyślny styl przycisków
    resetButtonStyles();

    // Pobierz bieżące pytanie
    const Pytanie& question = questions[currentQuestionIndex];
    ui->label->setText(question.getQuestionText());

    // Ustaw tekst na przyciskach odpowiedzi
    QStringList answers = question.getAnswers();
    if (answers.size() >= 4) {
        ui->aBtn->setText(answers[0]);
        ui->bBtn->setText(answers[1]);
        ui->cBtn->setText(answers[2]);
        ui->dBtn->setText(answers[3]);
    }
}

void MainWindow::checkAnswer(QPushButton* selectedButton) {
    const Pytanie& question = questions[currentQuestionIndex];
    QString selectedAnswer = selectedButton->text();

    if (selectedAnswer == question.getCorrectAnswer()) {
        // Poprawna odpowiedź
        selectedButton->setStyleSheet("background-color: green; color: white;");
        correctAnswersCount++; // Zwiększ licznik poprawnych odpowiedzi
    } else {
        // Niepoprawna odpowiedź
        selectedButton->setStyleSheet("background-color: red; color: white;");

        // Podświetl poprawny przycisk
        highlightCorrectButton(question.getCorrectAnswer());
    }

    currentQuestionIndex++;
    QTimer::singleShot(2000, this, &MainWindow::loadCurrentQuestion); // Przejdź do następnego pytania po 2 sekundach
}

void MainWindow::highlightCorrectButton(const QString& correctAnswer) {
    // Sprawdź, który przycisk zawiera poprawną odpowiedź, i podświetl go na zielono
    if (ui->aBtn->text() == correctAnswer)
        ui->aBtn->setStyleSheet("background-color: green; color: white;");
    if (ui->bBtn->text() == correctAnswer)
        ui->bBtn->setStyleSheet("background-color: green; color: white;");
    if (ui->cBtn->text() == correctAnswer)
        ui->cBtn->setStyleSheet("background-color: green; color: white;");
    if (ui->dBtn->text() == correctAnswer)
        ui->dBtn->setStyleSheet("background-color: green; color: white;");
}

void MainWindow::resetButtonStyles() {
    // Przywróć domyślny styl przycisków
    ui->aBtn->setStyleSheet("");
    ui->bBtn->setStyleSheet("");
    ui->cBtn->setStyleSheet("");
    ui->dBtn->setStyleSheet("");
}

void MainWindow::showFinalScore() {
    // Ukryj przyciski po zakończeniu quizu
    hideAnsButtons();

    // Wyświetl wynik
    int totalQuestions = questions.size();
    QString resultMessage = QString("Twój wynik: %1 z %2").arg(correctAnswersCount).arg(totalQuestions);
    ui->label->setText(resultMessage);
}

void MainWindow::on_aBtn_clicked() {
    checkAnswer(ui->aBtn);
}

void MainWindow::on_bBtn_clicked() {
    checkAnswer(ui->bBtn);
}

void MainWindow::on_cBtn_clicked() {
    checkAnswer(ui->cBtn);
}

void MainWindow::on_dBtn_clicked() {
    checkAnswer(ui->dBtn);
}
