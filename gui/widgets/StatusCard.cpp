#include "StatusCard.h"
#include <QVBoxLayout>

StatusCard::StatusCard(const QString &title, const QString &value, QWidget *parent) : QFrame(parent) {
    setObjectName("card");
    auto *l = new QVBoxLayout(this);
    l->setContentsMargins(18, 16, 18, 16);
    l->setSpacing(7);
    auto *t = new QLabel(title, this); t->setObjectName("cardTitle");
    valueLabel_ = new QLabel(value, this); valueLabel_->setObjectName("cardValue");
    l->addWidget(t); l->addWidget(valueLabel_);
}
void StatusCard::setValue(const QString &value) { valueLabel_->setText(value); }
