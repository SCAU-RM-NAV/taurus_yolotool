#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QDebug>
#include<QMessageBox>
#include<QString>
#include <QDir>
#include <QStringList>
#include<set>
#include <QColor>
#include<QList>
#include<QDateTime>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pballocat_clicked();

    void on_lineEdit_ratio_returnPressed();

    void on_lineEdit_chuandadiff_returnPressed();

    void check();

    void on_pbreadlabelpath_clicked();

    void on_pbcheckarmor_clicked();

    void on_pbExecute_clicked();

    void on_pbClean_clicked();

    void on_pbCheckNull_clicked();

    void on_pb_retainDele_clicked();

    void on_pb_DeleExcessFile_clicked();

    void on_pb_startrenamesort_clicked();

private:
    void initOnce();
    void renumberFiles(const QString& folderPath, int startNumber, const QString& fileType);
    bool isNumeric(const QString& str);
    bool isFolderExists(const QString& folderPath);

    struct CustomCompare {
        bool operator()(const QString& lhs, const QString& rhs) const {
            int lhsNum = lhs.toInt();
            int rhsNum = rhs.toInt();
            return lhsNum < rhsNum;
        }
    };


private:
    Ui::Widget *ui;

    int totalPeople,carPeople,armorPeople;
    float diff56,diffleague,diffwuke,diffchuanda;
    int car56,carleague,carwuke,carchuanda,arm56,armleague,armwuke,armchuanda;
    int img56,imgleague,imgwuke,imgchuanda;

    std::set<int> carlabelpathSet,armorlabelpathSet;

    QStringList armorList = (QStringList() << "B1" << "B2" << "B3" << "B4" << "B5" << "B7"
                             << "R1" << "R2" << "R3" << "R4" << "R5" << "R7");

    QMap<int, QString> armorMap;
    QWidget window;

};
#endif // WIDGET_H
