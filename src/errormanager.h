/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

#include <QObject>
#include <QString>

class ErrorManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)
    Q_PROPERTY(bool hasError READ hasError NOTIFY errorChanged)
    Q_PROPERTY(bool showRetry READ showRetry NOTIFY showRetryChanged)

  public:
    explicit ErrorManager(QObject* parent = nullptr);

    Q_INVOKABLE void showError(const QString& error, bool showRetry = false);
    Q_INVOKABLE void clearError();
    Q_INVOKABLE void retry();

    QString error() const {
        return m_error;
    }
    bool hasError() const {
        return !m_error.isEmpty();
    }
    bool showRetry() const {
        return m_showRetry;
    }

  signals:
    void errorChanged();
    void showRetryChanged();
    void retryRequested();

  private:
    QString m_error;
    bool m_showRetry;
};

#endif // ERRORMANAGER_H
