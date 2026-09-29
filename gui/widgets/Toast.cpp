#include "Toast.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QTimer>

Toast::Toast(QWidget *parent) : QFrame(parent) {
    setAttribute(Qt::WA_DeleteOnClose);
    setObjectName("toast");

    setWindowFlags(
        Qt::FramelessWindowHint |
        Qt::Tool |
        Qt::WindowStaysOnTopHint
    );

    setStyleSheet(
        "QFrame#toast {"
        "background:#151D2A;"
        "border:1px solid #2B3850;"
        "border-radius:12px;"
        "}"
        "QLabel {"
        "color:#E8ECF4;"
        "}"
    );
}

void Toast::show(
    QWidget *parent,
    const QString &title,
    const QString &message,
    Type type,
    int ms
) {
    auto *toast = new Toast(parent);

    auto *layout = new QHBoxLayout(toast);
    layout->setContentsMargins(14, 10, 14, 10);

    auto *text = new QLabel(
        QStringLiteral(
            "<b>%1</b><br>"
            "<span style='color:#8F9AAF'>%2</span>"
        ).arg(
            title.toHtmlEscaped(),
            message.toHtmlEscaped()
        ),
        toast
    );

    text->setTextFormat(Qt::RichText);
    layout->addWidget(text);

    toast->adjustSize();

    const QPoint p = parent->mapToGlobal(
        QPoint(
            parent->width() - toast->width() - 22,
            parent->height() - toast->height() - 22
        )
    );

    toast->move(p);

    // Explicitly call QWidget::show() because Toast::show(...)
    // hides the inherited QWidget::show() function.
    toast->QWidget::show();

    QTimer::singleShot(
        ms,
        toast,
        &QWidget::close
    );

    Q_UNUSED(type);
}
