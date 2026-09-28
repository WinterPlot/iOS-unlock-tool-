#pragma once
#include <QPushButton>

class AppButton final : public QPushButton {
    Q_OBJECT
public:
    explicit AppButton(const QString &text, QWidget *parent = nullptr);
    void setKind(const QString &kind);
};
