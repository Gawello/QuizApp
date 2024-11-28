#ifndef PYTANIE_H
#define PYTANIE_H

#include <QString>
#include <QStringList>
#include <QList>

class Pytanie {
public:
    Pytanie(); // Konstruktor
    static QList<Pytanie> wczytajPytaniaZPliku(const QString& filePath);

    QString getQuestionText() const;
    QStringList getAnswers() const;
    QString getCorrectAnswer() const;

private:
    QString questionText;
    QStringList answers;
    QString correctAnswer;
};

#endif // PYTANIE_H
