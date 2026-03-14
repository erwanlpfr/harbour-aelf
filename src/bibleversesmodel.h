/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef BIBLEVERSESMODEL_H
#define BIBLEVERSESMODEL_H

#include <QAbstractListModel>
#include <QList>

class BibleVerse;

class BibleVersesModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QString bookCode READ bookCode WRITE setBookCode NOTIFY bookCodeChanged)
    Q_PROPERTY(int chapter READ chapter WRITE setChapter NOTIFY chapterChanged)
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

  public:
    enum Roles { VerseNumberRole = Qt::UserRole + 1, TextRole };

    explicit BibleVersesModel(QObject* parent = nullptr);
    ~BibleVersesModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    QString bookCode() const {
        return m_bookCode;
    }
    void setBookCode(const QString& bookCode);

    int chapter() const {
        return m_chapter;
    }
    void setChapter(int chapter);

    Q_INVOKABLE void loadVerses();

  signals:
    void bookCodeChanged();
    void chapterChanged();
    void countChanged();

  private:
    QList<BibleVerse*> m_verses;
    QString m_bookCode;
    int m_chapter;
    QHash<int, QByteArray> m_roles;
};

#endif // BIBLEVERSESMODEL_H
