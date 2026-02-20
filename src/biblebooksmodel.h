/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef BIBLEBOOKSMODEL_H
#define BIBLEBOOKSMODEL_H

#include <QAbstractListModel>
#include <QList>

class BibleBook;

class BibleBooksModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QString section READ section WRITE setSection NOTIFY sectionChanged)

public:
    enum Roles {
        CodeRole = Qt::UserRole + 1,
        NameRole,
        AbbreviationRole,
        ChaptersRole,
        SectionRole
    };

    explicit BibleBooksModel(QObject* parent = nullptr);
    ~BibleBooksModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    QString section() const { return m_section; }
    void setSection(const QString& section);

    Q_INVOKABLE void loadBooks();

signals:
    void sectionChanged();

private:
    void filterBooks();

    QList<BibleBook*> m_allBooks;
    QList<BibleBook*> m_filteredBooks;
    QString m_section;
    QHash<int, QByteArray> m_roles;
};

#endif // BIBLEBOOKSMODEL_H
