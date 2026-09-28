#pragma once
#include <QFrame>
#include <QLabel>

class StatusCard final : public QFrame {
    Q_OBJECT
public:
    explicit StatusCard(const QString &title, const QString &value, QWidget *parent = nullptr);
    void setValue(const QString &value);
private:
    QLabel *valueLabel_{};
};
