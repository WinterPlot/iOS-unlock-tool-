#include "Theme.h"

namespace Theme {
QString stylesheet() {
    return QStringLiteral(R"QSS(
        * { font-family: "Inter", "Segoe UI", sans-serif; color: #E8ECF4; }
        QMainWindow, QWidget#root { background: #0B0F17; }
        QFrame#sidebar { background: #0F141E; border-right: 1px solid #202838; }
        QLabel#brand { font-size: 22px; font-weight: 800; color: #FFFFFF; }
        QLabel#brandSub { color: #7F8BA3; font-size: 11px; }
        QLabel#pageTitle { font-size: 28px; font-weight: 800; color: #FFFFFF; }
        QLabel#pageSub { color: #8995AA; font-size: 13px; }
        QPushButton#navButton { text-align: left; padding: 11px 14px; border: 0; border-radius: 10px; color: #9AA6BA; background: transparent; font-size: 13px; }
        QPushButton#navButton:hover { background: #171E2B; color: #FFFFFF; }
        QPushButton#navButton:checked { background: #1B2535; color: #FFFFFF; }
        QPushButton#primary { background: #6C63FF; color: white; border: 0; border-radius: 10px; padding: 11px 18px; font-weight: 700; }
        QPushButton#primary:hover { background: #7B73FF; }
        QPushButton#secondary { background: #151C28; color: #DCE3EF; border: 1px solid #283246; border-radius: 10px; padding: 10px 16px; }
        QPushButton#secondary:hover { background: #1B2433; border-color: #3A4760; }
        QPushButton#danger { background: #321A20; color: #FF9BA8; border: 1px solid #5A2833; border-radius: 10px; padding: 10px 16px; }
        QFrame#card { background: #111722; border: 1px solid #202A3A; border-radius: 14px; }
        QLabel#cardTitle { color: #8E9AAF; font-size: 12px; }
        QLabel#cardValue { color: #FFFFFF; font-size: 22px; font-weight: 800; }
        QLabel#pill { background: #13281F; color: #6FE0A7; border: 1px solid #214B38; border-radius: 9px; padding: 4px 9px; font-size: 11px; font-weight: 700; }
        QTextEdit, QPlainTextEdit { background: #0D131D; border: 1px solid #202A3A; border-radius: 12px; padding: 10px; color: #BFC9D9; }
        QLineEdit, QComboBox { background: #0D131D; border: 1px solid #263145; border-radius: 9px; padding: 9px 11px; color: #E8ECF4; }
        QLineEdit:focus, QComboBox:focus { border-color: #6C63FF; }
        QScrollBar:vertical { background: transparent; width: 8px; }
        QScrollBar::handle:vertical { background: #273247; border-radius: 4px; min-height: 30px; }
    )QSS");
}
}
