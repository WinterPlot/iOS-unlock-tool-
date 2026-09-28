#include "AppButton.h"

AppButton::AppButton(const QString &text, QWidget *parent) : QPushButton(text, parent) {
    setCursor(Qt::PointingHandCursor);
    setMinimumHeight(40);
    setKind(QStringLiteral("secondary"));
}

void AppButton::setKind(const QString &kind) { setObjectName(kind); }
