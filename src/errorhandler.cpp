/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "errorhandler.h"
#include <QCoreApplication>
#include <QTimer>
#include <QDebug>

ErrorHandler* ErrorHandler::s_instance = nullptr;

ErrorHandler::ErrorHandler(QObject *parent)
    : QObject(parent)
{
}

ErrorHandler* ErrorHandler::instance()
{
    if (!s_instance) {
        s_instance = new ErrorHandler();
    }
    return s_instance;
}

QString ErrorHandler::getLocalizedErrorMessage(ErrorType type, const QString& details) const
{
    return getLocalizedErrorMessage(type, ErrorSeverity::Error, details);
}

QString ErrorHandler::getLocalizedErrorMessage(ErrorType type, ErrorSeverity severity, const QString& details) const
{
    QString baseMessage;
    
    switch (type) {
    case ErrorType::NetworkError:
        baseMessage = getNetworkErrorMessage(details);
        break;
    case ErrorType::DatabaseError:
        baseMessage = getDatabaseErrorMessage(details);
        break;
    case ErrorType::ParseError:
        baseMessage = getParseErrorMessage(details);
        break;
    case ErrorType::FileSystemError:
        baseMessage = getFileSystemErrorMessage(details);
        break;
    case ErrorType::UnknownError:
    default:
        baseMessage = QCoreApplication::translate("ErrorHandler", "Une erreur inconnue est survenue");
        break;
    }
    
    if (severity == ErrorSeverity::Critical) {
        baseMessage = QCoreApplication::translate("ErrorHandler", "Critique : ") + baseMessage;
    } else if (severity == ErrorSeverity::Warning) {
        baseMessage = QCoreApplication::translate("ErrorHandler", "Attention : ") + baseMessage;
    }
    
    return baseMessage;
}

QString ErrorHandler::getNetworkErrorMessage(const QString& details) const
{
    if (details.contains("timeout", Qt::CaseInsensitive)) {
        return QCoreApplication::translate("ErrorHandler", "Délai d'attente réseau dépassé. Vérifiez votre connexion.");
    } else if (details.contains("host not found", Qt::CaseInsensitive)) {
        return QCoreApplication::translate("ErrorHandler", "Serveur introuvable. Vérifiez votre connexion internet.");
    } else if (details.contains("connection refused", Qt::CaseInsensitive)) {
        return QCoreApplication::translate("ErrorHandler", "Connexion refusée. Le serveur est peut-être indisponible.");
    } else {
        return QCoreApplication::translate("ErrorHandler", "Erreur réseau : %1").arg(details);
    }
}

QString ErrorHandler::getDatabaseErrorMessage(const QString& details) const
{
    if (details.contains("no such table", Qt::CaseInsensitive)) {
        return QCoreApplication::translate("ErrorHandler", "Base de données corrompue ou incomplète.");
    } else if (details.contains("unable to open", Qt::CaseInsensitive)) {
        return QCoreApplication::translate("ErrorHandler", "Impossible d'ouvrir la base de données Bible.");
    } else {
        return QCoreApplication::translate("ErrorHandler", "Erreur de base de données : %1").arg(details);
    }
}

QString ErrorHandler::getParseErrorMessage(const QString&) const
{
    return QCoreApplication::translate("ErrorHandler", "Erreur lors de l'analyse des données reçues.");
}

QString ErrorHandler::getFileSystemErrorMessage(const QString& details) const
{
    return QCoreApplication::translate("ErrorHandler", "Erreur d'accès aux fichiers : %1").arg(details);
}

bool ErrorHandler::shouldRetry(ErrorType type, int attemptCount) const
{
    switch (type) {
    case ErrorType::NetworkError:
        return attemptCount < 3;
    case ErrorType::DatabaseError:
        return attemptCount < 2;
    case ErrorType::ParseError:
        return false;
    case ErrorType::FileSystemError:
        return attemptCount < 2;
    case ErrorType::UnknownError:
    default:
        return attemptCount < 1;
    }
}

int ErrorHandler::getRetryDelay(ErrorType type, int attemptCount) const
{
    int baseDelay = 1000;
    
    switch (type) {
    case ErrorType::NetworkError:
        return baseDelay * (1 << attemptCount);
    case ErrorType::DatabaseError:
        return baseDelay * (1 << (attemptCount - 1));
    case ErrorType::FileSystemError:
        return baseDelay * (1 << (attemptCount - 1));
    default:
        return baseDelay;
    }
}
