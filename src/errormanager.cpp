/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "errormanager.h"

ErrorManager::ErrorManager(QObject* parent) : QObject(parent), m_showRetry(false) {
}

void ErrorManager::showError(const QString& error, bool showRetry) {
    if (m_error == error && m_showRetry == showRetry) {
        return;
    }

    m_error = error;
    m_showRetry = showRetry;

    emit errorChanged();
    emit showRetryChanged();
}

void ErrorManager::clearError() {
    if (!m_error.isEmpty()) {
        m_error.clear();
        m_showRetry = false;

        emit errorChanged();
        emit showRetryChanged();
    }
}

void ErrorManager::retry() {
    emit retryRequested();
    clearError();
}
