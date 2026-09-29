#pragma once

#include <QFrame>
#include <QLabel>
#include <QTimer>

class Toast final : public QFrame {
    Q_OBJECT

public:
    enum class Type {
        Info,
        Success,
        Warning,
        Error
    };

    static void show(
        QWidget *parent,
        const QString &title,
        const QString &message,
        Type type = Type::Info,
        int ms = 3200
    );

private:
    explicit Toast(QWidget *parent);
};
