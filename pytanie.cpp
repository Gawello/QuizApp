#include "pytanie.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Pytanie::Pytanie() {
    // Konstruktor domyślny
}

QList<Pytanie> Pytanie::wczytajPytaniaZPliku(const QString& filePath) {
    QList<Pytanie> pytania;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Nie udało się otworzyć pliku:" << filePath;
        return pytania;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList columns = line.split(';');

        if (columns.size() < 3) {
            qWarning() << "Nieprawidłowy format linii:" << line;
            continue;
        }

        Pytanie pytanie;
        pytanie.questionText = columns.at(0); // Pierwsza kolumna to pytanie
        pytanie.answers = columns.mid(1, columns.size() - 2); // Środkowe kolumny to odpowiedzi
        pytanie.correctAnswer = columns.last(); // Ostatnia kolumna to poprawna odpowiedź

        pytania.append(pytanie);
    }

    file.close();
    return pytania;
}

QString Pytanie::getQuestionText() const {
    return questionText;
}

QStringList Pytanie::getAnswers() const {
    return answers;
}

QString Pytanie::getCorrectAnswer() const {
    return correctAnswer;
}
