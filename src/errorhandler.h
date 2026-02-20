/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QObject>
#include <QString>

enum class ErrorType {
    NetworkError,
    DatabaseError,
    ParseError,
    FileSystemError,
    UnknownError
};

enum class ErrorSeverity {
    Warning,
    Error,
    Critical
};

class ErrorHandler : public QObject
{
    Q_OBJECT

public:
    static ErrorHandler* instance();
    
    QString getLocalizedErrorMessage(ErrorType type, const QString& details = QString()) const;
    QString getLocalizedErrorMessage(ErrorType type, ErrorSeverity severity, const QString& details = QString()) const;
    
    bool shouldRetry(ErrorType type, int attemptCount) const;
    int getRetryDelay(ErrorType type, int attemptCount) const;

signals:
    void errorOccurred(ErrorType type, ErrorSeverity severity, const QString& message);

private:
    explicit ErrorHandler(QObject *parent = nullptr);
    static ErrorHandler* s_instance;
    
    QString getNetworkErrorMessage(const QString& details) const;
    QString getDatabaseErrorMessage(const QString& details) const;
    QString getParseErrorMessage(const QString&) const;
    QString getFileSystemErrorMessage(const QString& details) const;
};

#endif // ERRORHANDLER_H
