#pragma once
#include <QMainWindow>
#include <QStackedWidget>
#include <QLabel>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QButtonGroup>
#include "widgets/StatusCard.h"

class MainWindow final : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
private slots:
    void selectPage(int index);
    void refreshDevice();
    void runSafeCheck();
    void clearActivity();
    void submitFeedback();
    void changeTheme(int index);
private:
    QWidget *makeDashboard();
    QWidget *makeDevicePage();
    QWidget *makeActivityPage();
    QWidget *makeFeedbackPage();
    QWidget *makeSettingsPage();
    QWidget *makeAboutPage();
    QWidget *pageHeader(const QString &title, const QString &subtitle);
    void log(const QString &text);

    QStackedWidget *stack_{};
    QPlainTextEdit *activity_{};
    QLabel *connection_{};
    StatusCard *deviceCard_{};
    StatusCard *modeCard_{};
    StatusCard *stateCard_{};
    QLineEdit *feedbackTitle_{};
    QPlainTextEdit *feedbackBody_{};
};
