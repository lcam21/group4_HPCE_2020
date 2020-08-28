/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *I_LeftRaw;
    QPushButton *B_LeftImgPickBtn;
    QListWidget *CamerList;
    QPushButton *B_RightImgPickBtn;
    QLabel *L_LRawImg;
    QLabel *L_AvailableImg;
    QLabel *I_RightRaw;
    QLabel *L_RRawImg;
    QLabel *I_GT;
    QLabel *L_GT;
    QPushButton *B_GTPickBtn;
    QLabel *L_GlobalParams;
    QLabel *L_MinDisp;
    QLabel *L_MaxDisp;
    QLineEdit *P_MinDisp;
    QLineEdit *P_MaxDisp;
    QLineEdit *P_m_u8BlockSize;
    QLabel *L_m_u8BlockSize_half;
    QLineEdit *P_P2;
    QLabel *L_P2;
    QLineEdit *P_P1;
    QLabel *L_P1;
    QLineEdit *P_SGBMDir;
    QLabel *L_Census_2;
    QLineEdit *P_UniqRatio;
    QLabel *L_PostProcessing;
    QLabel *L_UniqRation;
    QFrame *O_line_4;
    QFrame *O_line_8;
    QLabel *I_CT_HD_SGBM;
    QLabel *I_CT_HD_Diff;
    QLabel *L_SGBM;
    QLabel *L_SGBM_2;
    QLabel *L_error_7;
    QLabel *L_error_6;
    QPushButton *B_Run;
    QPushButton *P_Update_In;
    QFrame *O_line_9;
    QFrame *O_line_10;
    QLabel *I_CT_HD_Hist;
    QLabel *L_SGBM_3;
    QLabel *L_Sources;
    QLineEdit *P_Source;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1850, 1136);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        I_LeftRaw = new QLabel(centralWidget);
        I_LeftRaw->setObjectName(QStringLiteral("I_LeftRaw"));
        I_LeftRaw->setGeometry(QRect(40, 270, 350, 220));
        I_LeftRaw->setFrameShape(QFrame::Box);
        B_LeftImgPickBtn = new QPushButton(centralWidget);
        B_LeftImgPickBtn->setObjectName(QStringLiteral("B_LeftImgPickBtn"));
        B_LeftImgPickBtn->setGeometry(QRect(71, 156, 91, 21));
        CamerList = new QListWidget(centralWidget);
        CamerList->setObjectName(QStringLiteral("CamerList"));
        CamerList->setGeometry(QRect(83, 73, 250, 81));
        B_RightImgPickBtn = new QPushButton(centralWidget);
        B_RightImgPickBtn->setObjectName(QStringLiteral("B_RightImgPickBtn"));
        B_RightImgPickBtn->setGeometry(QRect(163, 156, 81, 21));
        L_LRawImg = new QLabel(centralWidget);
        L_LRawImg->setObjectName(QStringLiteral("L_LRawImg"));
        L_LRawImg->setGeometry(QRect(144, 240, 141, 34));
        L_AvailableImg = new QLabel(centralWidget);
        L_AvailableImg->setObjectName(QStringLiteral("L_AvailableImg"));
        L_AvailableImg->setGeometry(QRect(152, 47, 121, 34));
        I_RightRaw = new QLabel(centralWidget);
        I_RightRaw->setObjectName(QStringLiteral("I_RightRaw"));
        I_RightRaw->setGeometry(QRect(40, 520, 350, 220));
        I_RightRaw->setFrameShape(QFrame::Box);
        L_RRawImg = new QLabel(centralWidget);
        L_RRawImg->setObjectName(QStringLiteral("L_RRawImg"));
        L_RRawImg->setGeometry(QRect(150, 493, 151, 34));
        I_GT = new QLabel(centralWidget);
        I_GT->setObjectName(QStringLiteral("I_GT"));
        I_GT->setGeometry(QRect(40, 770, 350, 220));
        I_GT->setFrameShape(QFrame::Box);
        L_GT = new QLabel(centralWidget);
        L_GT->setObjectName(QStringLiteral("L_GT"));
        L_GT->setGeometry(QRect(160, 740, 121, 34));
        B_GTPickBtn = new QPushButton(centralWidget);
        B_GTPickBtn->setObjectName(QStringLiteral("B_GTPickBtn"));
        B_GTPickBtn->setGeometry(QRect(245, 156, 101, 21));
        L_GlobalParams = new QLabel(centralWidget);
        L_GlobalParams->setObjectName(QStringLiteral("L_GlobalParams"));
        L_GlobalParams->setGeometry(QRect(420, 34, 131, 17));
        L_MinDisp = new QLabel(centralWidget);
        L_MinDisp->setObjectName(QStringLiteral("L_MinDisp"));
        L_MinDisp->setGeometry(QRect(580, 33, 67, 17));
        L_MaxDisp = new QLabel(centralWidget);
        L_MaxDisp->setObjectName(QStringLiteral("L_MaxDisp"));
        L_MaxDisp->setGeometry(QRect(702, 34, 67, 17));
        P_MinDisp = new QLineEdit(centralWidget);
        P_MinDisp->setObjectName(QStringLiteral("P_MinDisp"));
        P_MinDisp->setGeometry(QRect(646, 33, 41, 20));
        P_MaxDisp = new QLineEdit(centralWidget);
        P_MaxDisp->setObjectName(QStringLiteral("P_MaxDisp"));
        P_MaxDisp->setGeometry(QRect(770, 34, 41, 20));
        P_m_u8BlockSize = new QLineEdit(centralWidget);
        P_m_u8BlockSize->setObjectName(QStringLiteral("P_m_u8BlockSize"));
        P_m_u8BlockSize->setGeometry(QRect(1220, 33, 41, 20));
        L_m_u8BlockSize_half = new QLabel(centralWidget);
        L_m_u8BlockSize_half->setObjectName(QStringLiteral("L_m_u8BlockSize_half"));
        L_m_u8BlockSize_half->setGeometry(QRect(1148, 34, 81, 17));
        P_P2 = new QLineEdit(centralWidget);
        P_P2->setObjectName(QStringLiteral("P_P2"));
        P_P2->setGeometry(QRect(1060, 35, 51, 20));
        L_P2 = new QLabel(centralWidget);
        L_P2->setObjectName(QStringLiteral("L_P2"));
        L_P2->setGeometry(QRect(991, 35, 67, 17));
        P_P1 = new QLineEdit(centralWidget);
        P_P1->setObjectName(QStringLiteral("P_P1"));
        P_P1->setGeometry(QRect(928, 34, 51, 20));
        L_P1 = new QLabel(centralWidget);
        L_P1->setObjectName(QStringLiteral("L_P1"));
        L_P1->setGeometry(QRect(860, 34, 67, 17));
        P_SGBMDir = new QLineEdit(centralWidget);
        P_SGBMDir->setObjectName(QStringLiteral("P_SGBMDir"));
        P_SGBMDir->setGeometry(QRect(1410, 34, 41, 20));
        L_Census_2 = new QLabel(centralWidget);
        L_Census_2->setObjectName(QStringLiteral("L_Census_2"));
        L_Census_2->setGeometry(QRect(1290, 34, 121, 17));
        P_UniqRatio = new QLineEdit(centralWidget);
        P_UniqRatio->setObjectName(QStringLiteral("P_UniqRatio"));
        P_UniqRatio->setGeometry(QRect(1788, 36, 41, 20));
        L_PostProcessing = new QLabel(centralWidget);
        L_PostProcessing->setObjectName(QStringLiteral("L_PostProcessing"));
        L_PostProcessing->setGeometry(QRect(1531, 36, 111, 17));
        L_UniqRation = new QLabel(centralWidget);
        L_UniqRation->setObjectName(QStringLiteral("L_UniqRation"));
        L_UniqRation->setGeometry(QRect(1658, 36, 131, 20));
        O_line_4 = new QFrame(centralWidget);
        O_line_4->setObjectName(QStringLiteral("O_line_4"));
        O_line_4->setGeometry(QRect(390, 50, 1451, 20));
        O_line_4->setFrameShape(QFrame::HLine);
        O_line_4->setFrameShadow(QFrame::Sunken);
        O_line_8 = new QFrame(centralWidget);
        O_line_8->setObjectName(QStringLiteral("O_line_8"));
        O_line_8->setGeometry(QRect(560, 34, 20, 21));
        O_line_8->setFrameShape(QFrame::VLine);
        O_line_8->setFrameShadow(QFrame::Sunken);
        I_CT_HD_SGBM = new QLabel(centralWidget);
        I_CT_HD_SGBM->setObjectName(QStringLiteral("I_CT_HD_SGBM"));
        I_CT_HD_SGBM->setGeometry(QRect(830, 110, 600, 400));
        I_CT_HD_SGBM->setMouseTracking(true);
        I_CT_HD_SGBM->setFrameShape(QFrame::Box);
        I_CT_HD_Diff = new QLabel(centralWidget);
        I_CT_HD_Diff->setObjectName(QStringLiteral("I_CT_HD_Diff"));
        I_CT_HD_Diff->setGeometry(QRect(1192, 560, 600, 400));
        I_CT_HD_Diff->setFrameShape(QFrame::Box);
        L_SGBM = new QLabel(centralWidget);
        L_SGBM->setObjectName(QStringLiteral("L_SGBM"));
        L_SGBM->setGeometry(QRect(1035, 80, 191, 20));
        L_SGBM->setScaledContents(false);
        L_SGBM_2 = new QLabel(centralWidget);
        L_SGBM_2->setObjectName(QStringLiteral("L_SGBM_2"));
        L_SGBM_2->setGeometry(QRect(1250, 530, 230, 40));
        L_SGBM_2->setScaledContents(false);
        L_error_7 = new QLabel(centralWidget);
        L_error_7->setObjectName(QStringLiteral("L_error_7"));
        L_error_7->setGeometry(QRect(1540, 539, 141, 20));
        L_error_7->setScaledContents(false);
        L_error_6 = new QLabel(centralWidget);
        L_error_6->setObjectName(QStringLiteral("L_error_6"));
        L_error_6->setGeometry(QRect(1676, 540, 81, 20));
        L_error_6->setScaledContents(false);
        B_Run = new QPushButton(centralWidget);
        B_Run->setObjectName(QStringLiteral("B_Run"));
        B_Run->setGeometry(QRect(156, 188, 91, 41));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(78, 154, 6, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(117, 231, 9, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(97, 192, 7, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(39, 77, 3, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(52, 103, 4, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush7(QColor(166, 204, 130, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        B_Run->setPalette(palette);
        B_Run->setContextMenuPolicy(Qt::NoContextMenu);
        B_Run->setStyleSheet(QStringLiteral(""));
        B_Run->setAutoDefault(false);
        P_Update_In = new QPushButton(centralWidget);
        P_Update_In->setObjectName(QStringLiteral("P_Update_In"));
        P_Update_In->setGeometry(QRect(20, 100, 61, 21));
        O_line_9 = new QFrame(centralWidget);
        O_line_9->setObjectName(QStringLiteral("O_line_9"));
        O_line_9->setGeometry(QRect(1639, 34, 20, 21));
        O_line_9->setFrameShape(QFrame::VLine);
        O_line_9->setFrameShadow(QFrame::Sunken);
        O_line_10 = new QFrame(centralWidget);
        O_line_10->setObjectName(QStringLiteral("O_line_10"));
        O_line_10->setGeometry(QRect(410, 300, 20, 691));
        O_line_10->setFrameShape(QFrame::VLine);
        O_line_10->setFrameShadow(QFrame::Sunken);
        I_CT_HD_Hist = new QLabel(centralWidget);
        I_CT_HD_Hist->setObjectName(QStringLiteral("I_CT_HD_Hist"));
        I_CT_HD_Hist->setGeometry(QRect(470, 560, 600, 400));
        I_CT_HD_Hist->setFrameShape(QFrame::Box);
        L_SGBM_3 = new QLabel(centralWidget);
        L_SGBM_3->setObjectName(QStringLiteral("L_SGBM_3"));
        L_SGBM_3->setGeometry(QRect(650, 530, 241, 31));
        L_SGBM_3->setScaledContents(false);
        L_Sources = new QLabel(centralWidget);
        L_Sources->setObjectName(QStringLiteral("L_Sources"));
        L_Sources->setGeometry(QRect(10, 20, 121, 17));
        P_Source = new QLineEdit(centralWidget);
        P_Source->setObjectName(QStringLiteral("P_Source"));
        P_Source->setGeometry(QRect(140, 20, 231, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1850, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        B_Run->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        I_LeftRaw->setText(QString());
        B_LeftImgPickBtn->setText(QApplication::translate("MainWindow", "Left", Q_NULLPTR));
        B_RightImgPickBtn->setText(QApplication::translate("MainWindow", "Right", Q_NULLPTR));
        L_LRawImg->setText(QApplication::translate("MainWindow", "Left Rectified Image", Q_NULLPTR));
        L_AvailableImg->setText(QApplication::translate("MainWindow", "Available Images", Q_NULLPTR));
        I_RightRaw->setText(QString());
        L_RRawImg->setText(QApplication::translate("MainWindow", "Right Rectified Image", Q_NULLPTR));
        I_GT->setText(QString());
        L_GT->setText(QApplication::translate("MainWindow", "Ground Truth", Q_NULLPTR));
        B_GTPickBtn->setText(QApplication::translate("MainWindow", "Ground Truth", Q_NULLPTR));
        L_GlobalParams->setText(QApplication::translate("MainWindow", "Global Parameters", Q_NULLPTR));
        L_MinDisp->setText(QApplication::translate("MainWindow", "Min Disp:", Q_NULLPTR));
        L_MaxDisp->setText(QApplication::translate("MainWindow", "Max Disp:", Q_NULLPTR));
        P_MinDisp->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        P_MaxDisp->setText(QApplication::translate("MainWindow", "150", Q_NULLPTR));
        P_m_u8BlockSize->setText(QApplication::translate("MainWindow", "5", Q_NULLPTR));
        L_m_u8BlockSize_half->setText(QApplication::translate("MainWindow", "Block Size:", Q_NULLPTR));
        P_P2->setText(QApplication::translate("MainWindow", "60", Q_NULLPTR));
        L_P2->setText(QApplication::translate("MainWindow", "Penalty 2:", Q_NULLPTR));
        P_P1->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        L_P1->setText(QApplication::translate("MainWindow", "Penalty 1:", Q_NULLPTR));
        P_SGBMDir->setText(QApplication::translate("MainWindow", "3", Q_NULLPTR));
        L_Census_2->setText(QApplication::translate("MainWindow", "SGBM Directions:", Q_NULLPTR));
        P_UniqRatio->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        L_PostProcessing->setText(QApplication::translate("MainWindow", "Post-Processing", Q_NULLPTR));
        L_UniqRation->setText(QApplication::translate("MainWindow", "Uniqueness Ratio:", Q_NULLPTR));
        I_CT_HD_SGBM->setText(QString());
        I_CT_HD_Diff->setText(QString());
        L_SGBM->setText(QApplication::translate("MainWindow", "Semiglobal Block Matching", Q_NULLPTR));
        L_SGBM_2->setText(QApplication::translate("MainWindow", "Difference to Ground Truth", Q_NULLPTR));
        L_error_7->setText(QApplication::translate("MainWindow", "Average pixel error:", Q_NULLPTR));
        L_error_6->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        B_Run->setText(QApplication::translate("MainWindow", "RUN", Q_NULLPTR));
        P_Update_In->setText(QApplication::translate("MainWindow", "Update", Q_NULLPTR));
        I_CT_HD_Hist->setText(QString());
        L_SGBM_3->setText(QApplication::translate("MainWindow", "Cost-Function Ploting / Histogram", Q_NULLPTR));
        L_Sources->setText(QApplication::translate("MainWindow", "Source Directory:", Q_NULLPTR));
        P_Source->setText(QApplication::translate("MainWindow", "../Test_data/", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
