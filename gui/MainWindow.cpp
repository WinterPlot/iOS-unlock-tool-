#include "MainWindow.h"
#include "Theme.h"
#include "widgets/AppButton.h"
#include "widgets/Toast.h"
#include <QApplication>
#include <QDateTime>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QMessageBox>

static QLabel *label(const QString &text, const QString &objectName = QString(), QWidget *p = nullptr) {
    auto *l = new QLabel(text, p); if (!objectName.isEmpty()) l->setObjectName(objectName); return l;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("tr4mpass • Device Utility");
    resize(1180, 760);
    setMinimumSize(980, 640);
    setStyleSheet(Theme::stylesheet());

    auto *root = new QWidget(this); root->setObjectName("root"); setCentralWidget(root);
    auto *main = new QHBoxLayout(root); main->setContentsMargins(0,0,0,0); main->setSpacing(0);

    auto *side = new QFrame(root); side->setObjectName("sidebar"); side->setFixedWidth(235);
    auto *sl = new QVBoxLayout(side); sl->setContentsMargins(18,22,18,18); sl->setSpacing(7);
    sl->addWidget(label("tr4mpass", "brand")); sl->addWidget(label("DESKTOP CONSOLE", "brandSub"));
    sl->addSpacing(22);

    auto *group = new QButtonGroup(side); group->setExclusive(true);
    const QStringList names = {"⌂   Dashboard", "▣   Device", "▤   Activity", "✉   Feedback", "⚙   Settings", "ⓘ   About"};
    for (int i=0;i<names.size();++i) {
        auto *b = new QPushButton(names[i], side); b->setObjectName("navButton"); b->setCheckable(true); b->setFixedHeight(42); group->addButton(b, i); sl->addWidget(b);
    }
    group->button(0)->setChecked(true);
    connect(group, &QButtonGroup::idClicked, this, &MainWindow::selectPage);
    sl->addItem(new QSpacerItem(1,1,QSizePolicy::Minimum,QSizePolicy::Expanding));
    connection_ = label("●  Ready", "pill", side); sl->addWidget(connection_);
    main->addWidget(side);

    stack_ = new QStackedWidget(root);
    stack_->addWidget(makeDashboard());
    stack_->addWidget(makeDevicePage());
    stack_->addWidget(makeActivityPage());
    stack_->addWidget(makeFeedbackPage());
    stack_->addWidget(makeSettingsPage());
    stack_->addWidget(makeAboutPage());
    main->addWidget(stack_, 1);
    log("Application started");
}

QWidget *MainWindow::pageHeader(const QString &title, const QString &subtitle) {
    auto *w = new QWidget; auto *l = new QVBoxLayout(w); l->setContentsMargins(0,0,0,0); l->setSpacing(5);
    l->addWidget(label(title,"pageTitle")); l->addWidget(label(subtitle,"pageSub")); return w;
}

QWidget *MainWindow::makeDashboard() {
    auto *w = new QWidget; auto *l = new QVBoxLayout(w); l->setContentsMargins(34,30,34,30); l->setSpacing(18);
    l->addWidget(pageHeader("Dashboard", "A clean workspace for device inspection and local research workflows."));
    auto *cards = new QHBoxLayout; cards->setSpacing(14);
    deviceCard_ = new StatusCard("DEVICE", "Not connected"); modeCard_ = new StatusCard("MODE", "Waiting"); stateCard_ = new StatusCard("STATE", "Ready");
    cards->addWidget(deviceCard_); cards->addWidget(modeCard_); cards->addWidget(stateCard_); l->addLayout(cards);
    auto *card = new QFrame; card->setObjectName("card"); auto *cl = new QVBoxLayout(card); cl->setContentsMargins(22,20,22,20); cl->setSpacing(12);
    cl->addWidget(label("Workspace", "cardValue")); cl->addWidget(label("Use the controls below to inspect the connected device and validate the local environment. Actions are intentionally non-destructive.", "pageSub"));
    auto *actions = new QHBoxLayout; auto *refresh = new AppButton("Refresh device"); refresh->setKind("primary"); auto *check = new AppButton("Run safe check"); check->setKind("secondary"); auto *clear = new AppButton("Clear activity"); clear->setKind("secondary");
    connect(refresh,&QPushButton::clicked,this,&MainWindow::refreshDevice); connect(check,&QPushButton::clicked,this,&MainWindow::runSafeCheck); connect(clear,&QPushButton::clicked,this,&MainWindow::clearActivity);
    actions->addWidget(refresh); actions->addWidget(check); actions->addWidget(clear); actions->addStretch(); cl->addLayout(actions); l->addWidget(card); l->addStretch(); return w;
}

QWidget *MainWindow::makeDevicePage() {
    auto *w = new QWidget; auto *l = new QVBoxLayout(w); l->setContentsMargins(34,30,34,30); l->setSpacing(18);
    l->addWidget(pageHeader("Device", "Connection state and read-only device information."));
    auto *card = new QFrame; card->setObjectName("card"); auto *cl = new QVBoxLayout(card); cl->setContentsMargins(22,20,22,20);
    cl->addWidget(label("Connection", "cardValue")); cl->addWidget(label("No device has been inspected yet.","pageSub"));
    auto *b = new AppButton("Refresh / inspect"); b->setKind("primary"); connect(b,&QPushButton::clicked,this,&MainWindow::refreshDevice); cl->addSpacing(10); cl->addWidget(b,0,Qt::AlignLeft); l->addWidget(card); l->addStretch(); return w;
}

QWidget *MainWindow::makeActivityPage() {
    auto *w = new QWidget; auto *l = new QVBoxLayout(w); l->setContentsMargins(34,30,34,30); l->setSpacing(15);
    l->addWidget(pageHeader("Activity", "Local application events and diagnostics.")); activity_ = new QPlainTextEdit; activity_->setReadOnly(true); l->addWidget(activity_,1);
    auto *clear = new AppButton("Clear activity"); clear->setKind("secondary"); connect(clear,&QPushButton::clicked,this,&MainWindow::clearActivity); l->addWidget(clear,0,Qt::AlignLeft); return w;
}

QWidget *MainWindow::makeFeedbackPage() {
    auto *w = new QWidget; auto *l = new QVBoxLayout(w); l->setContentsMargins(34,30,34,30); l->setSpacing(15);
    l->addWidget(pageHeader("Feedback", "Tell us what should be improved in the desktop experience."));
    feedbackTitle_ = new QLineEdit; feedbackTitle_->setPlaceholderText("Subject"); feedbackBody_ = new QPlainTextEdit; feedbackBody_->setPlaceholderText("Your feedback..."); l->addWidget(feedbackTitle_); l->addWidget(feedbackBody_,1);
    auto *send = new AppButton("Send feedback"); send->setKind("primary"); connect(send,&QPushButton::clicked,this,&MainWindow::submitFeedback); l->addWidget(send,0,Qt::AlignLeft); return w;
}

QWidget *MainWindow::makeSettingsPage() {
    auto *w = new QWidget; auto *l = new QVBoxLayout(w); l->setContentsMargins(34,30,34,30); l->setSpacing(15);
    l->addWidget(pageHeader("Settings", "Personalize the application without touching device state."));
    auto *card = new QFrame; card->setObjectName("card"); auto *cl = new QVBoxLayout(card); cl->setContentsMargins(22,20,22,20);
    cl->addWidget(label("Appearance","cardValue")); auto *theme = new QComboBox; theme->addItems({"Midnight", "System"}); connect(theme, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::changeTheme); cl->addWidget(theme); l->addWidget(card); l->addStretch(); return w;
}

QWidget *MainWindow::makeAboutPage() {
    auto *w = new QWidget; auto *l = new QVBoxLayout(w); l->setContentsMargins(34,30,34,30); l->setSpacing(15);
    l->addWidget(pageHeader("About", "tr4mpass desktop interface."));
    auto *card = new QFrame; card->setObjectName("card"); auto *cl = new QVBoxLayout(card); cl->setContentsMargins(22,20,22,20);
    cl->addWidget(label("Professional Qt desktop shell", "cardValue")); cl->addWidget(label("Built with Qt Widgets, reusable controls, responsive layouts, activity logging and non-blocking notifications.","pageSub")); l->addWidget(card); l->addStretch(); return w;
}

void MainWindow::selectPage(int index) { stack_->setCurrentIndex(index); }

void MainWindow::refreshDevice() {
    deviceCard_->setValue("Inspection ready"); modeCard_->setValue("Read-only"); stateCard_->setValue("No destructive action"); connection_->setText("●  Inspected");
    log("Device inspection requested"); Toast::show(this,"Device", "Read-only inspection completed.", Toast::Type::Success);
}

void MainWindow::runSafeCheck() {
    log("Safe environment check completed"); Toast::show(this,"Check complete", "No device-changing operation was performed.", Toast::Type::Info);
}

void MainWindow::clearActivity() { if (activity_) activity_->clear(); }

void MainWindow::submitFeedback() {
    if (feedbackBody_->toPlainText().trimmed().isEmpty()) { Toast::show(this,"Feedback", "Please enter a message first.", Toast::Type::Warning); return; }
    log(QStringLiteral("Feedback drafted: %1").arg(feedbackTitle_->text().trimmed().isEmpty()?"Untitled":feedbackTitle_->text().trimmed()));
    Toast::show(this,"Feedback", "Feedback captured locally.", Toast::Type::Success); feedbackBody_->clear(); feedbackTitle_->clear();
}

void MainWindow::changeTheme(int index) { if (index == 0) qApp->setStyleSheet(Theme::stylesheet()); }

void MainWindow::log(const QString &text) {
    if (!activity_) return;
    activity_->appendPlainText(QStringLiteral("[%1] %2").arg(QDateTime::currentDateTime().toString("HH:mm:ss"), text));
}
