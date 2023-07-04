#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0,4);
    initOnce();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::initOnce()
{
    armorMap[0] = "B1";
    armorMap[1] = "B2";
    armorMap[2] = "B3";
    armorMap[3] = "B4";
    armorMap[4] = "B5";
    armorMap[5] = "B7";
    armorMap[6] = "R1";
    armorMap[7] = "R2";
    armorMap[8] = "R3";
    armorMap[9] = "R4";
    armorMap[10] = "R5";
    armorMap[11] = "R7";
}


void Widget::on_pballocat_clicked()
{
    check();

    carPeople = ui->lineEdit_carpeo->text().toInt();
    armorPeople = ui->lineEdit_armpeo->text().toInt();

    car56 = ui->lineEdit_56carpeo->text().toInt();
    carleague = ui->lineEdit_leaguecarpeo->text().toInt();
    carwuke = ui->lineEdit_wukecarpeo->text().toInt();
    carchuanda = ui->lineEdit_chuandacarpeo->text().toInt();

    arm56 = ui->lineEdit_56armpeo->text().toInt();
    armleague = ui->lineEdit_leaguearmpeo->text().toInt();
    armwuke = ui->lineEdit_wukearmpeo->text().toInt();
    armchuanda = ui->lineEdit_chuandaarmpeo->text().toInt();

    if((car56 + carleague + carwuke + carchuanda) != carPeople)
    {
        QMessageBox::warning(NULL,"warning","please check carPeople!");
    }

    if((arm56 + armwuke + armleague + armchuanda) != armorPeople)
    {
        QMessageBox::warning(NULL,"warning","please check armPeople!");
    }
    else {
        QMessageBox::information(NULL,"info","人数分配正确！");
    }

    //分配

    img56 = ui->lineEdit_56->text().toInt();
    imgleague = ui->lineEdit_league->text().toInt();
    imgwuke = ui->lineEdit_wuke->text().toInt();
    imgchuanda = ui->lineEdit_chuanda->text().toInt();
    qDebug()<<QString("dataset:%1:%2:%3:%4").arg(img56).arg(imgleague).arg(imgwuke).arg(imgchuanda)<<__LINE__;



}



void Widget::on_lineEdit_ratio_returnPressed()
{
   check();

    //确定车和装甲板的人数
    totalPeople = ui->lineEdit_total->text().toInt();
    carPeople = totalPeople*ui->lineEdit_ratio->text().toFloat();
    armorPeople = totalPeople*(1 - ui->lineEdit_ratio->text().toFloat());
    qDebug()<<"car:armor"<<carPeople<<":"<<armorPeople<<endl;
    ui->lineEdit_carpeo->setText(QString("%1").arg(carPeople));
    ui->lineEdit_armpeo->setText(QString("%1").arg(armorPeople));
}

void Widget::on_lineEdit_chuandadiff_returnPressed()
{
    check();

    //确定车和装甲板的人数
    totalPeople = ui->lineEdit_total->text().toInt();
    carPeople = totalPeople*ui->lineEdit_ratio->text().toFloat();
    armorPeople = totalPeople*(1 - ui->lineEdit_ratio->text().toFloat());
    qDebug()<<"car:armor"<<carPeople<<":"<<armorPeople<<endl;

    ui->lineEdit_56carpeo->setText(QString("%1").arg((int)(carPeople * diff56)));
    ui->lineEdit_leaguecarpeo->setText(QString("%1").arg((int)(carPeople *diffleague)));
    ui->lineEdit_wukecarpeo->setText(QString("%1").arg((int)(carPeople *diffwuke)));
    ui->lineEdit_chuandacarpeo->setText(QString("%1").arg((int)(carPeople *diffchuanda)));

    ui->lineEdit_56armpeo->setText(QString("%1").arg((int)(armorPeople * diff56)));
    ui->lineEdit_leaguearmpeo->setText(QString("%1").arg((int)(armorPeople *diffleague)));
    ui->lineEdit_wukearmpeo->setText(QString("%1").arg((int)(armorPeople *diffwuke)));
    ui->lineEdit_chuandaarmpeo->setText(QString("%1").arg((int)(armorPeople *diffchuanda)));


}

void Widget::check()
{
    if(ui->lineEdit_total->text().isEmpty()
        && ui->lineEdit_ratio->text().isEmpty())
    {
        QMessageBox::warning(NULL,"warning","please input data in totalpeople and ratio!");
        return;
    }else {
        totalPeople = ui->lineEdit_total->text().toInt();
        carPeople = totalPeople*ui->lineEdit_ratio->text().toFloat();
        armorPeople = totalPeople*(1 - ui->lineEdit_ratio->text().toFloat());

    }

    diff56 = ui->lineEdit_56diff->text().toFloat();
    diffleague = ui->lineEdit_leaguediff->text().toFloat();
    diffwuke = ui->lineEdit_wukediff->text().toFloat();
    diffchuanda = ui->lineEdit_chuandadiff->text().toFloat();

    if((int)(diff56 + diffleague + diffwuke + diffchuanda) != 1)
    {
        qDebug()<<ui->lineEdit_56diff->text().toFloat()
                                    +ui->lineEdit_leaguediff->text().toFloat()
                                    +ui->lineEdit_wukediff->text().toFloat()
                                    +ui->lineEdit_chuandadiff->text().toFloat();
        QMessageBox::warning(NULL,"warning","The total ratio is not equal to one!");
    }else {
        qDebug()<<QString("%1:%2:%3:%4:%5").arg(ui->lineEdit_56diff->text().toFloat())
                  .arg(ui->lineEdit_leaguediff->text().toFloat()).arg(ui->lineEdit_wukediff->text().toFloat()).arg(ui->lineEdit_chuandadiff->text().toFloat());
    }
}

void Widget::on_pbreadlabelpath_clicked()
{
    QString carlabelpath,armorlabelpath;

    //两个标好图片的路径
//    carlabelpath = QString("../carlabel");
//    armorlabelpath = QString("../armorlabel");
    carlabelpath = ui->lineEdit_carlabelpath->text();
    armorlabelpath = ui->lineEdit_armorlabelpath->text();

    //车的文件列表
    QDir carfolder(carlabelpath);
    QStringList carlabelfiles = carfolder.entryList(QDir::Files); // 获取文件列表

    // 遍历文件列表并插入carlabel容器
    foreach (QString file, carlabelfiles) {
        QFileInfo fileInfo(file);
        QString fileName = fileInfo.baseName(); // 获取文件名，不包含后缀
        carlabelpathSet.insert(QString(fileName).toInt());
    }

    //遍历carlabel容器的值并打印到plaintext
    for(int caritem : carlabelpathSet)
    {
        QString item = QString::number(caritem) + '\n';
        ui->plainTextEdit->appendPlainText(item);
        qDebug()<<caritem<<endl;
    }
    ui->plainTextEdit->appendPlainText(QString("carlabel总共有：%1个").arg(carlabelfiles.size()));
    qDebug()<<QString("carlabel总共有：%1个").arg(carlabelfiles.size());


    //遍历carlabel容器并插入tablewidget对应行
    for(int caritem : carlabelpathSet)
    {
        ui->tableWidget->item(caritem-1,0)->setText(QString("%1").arg(caritem));
    }


    //装甲板的文件列表
    QDir armorfolder(armorlabelpath);
    QStringList armorlabelfiles = armorfolder.entryList(QDir::Files); // 获取文件列表

    // 遍历文件列表并插入carlabel容器
    foreach (QString file, armorlabelfiles) {
        QFileInfo fileInfo(file);
        QString fileName = fileInfo.baseName(); // 获取文件名，不包含后缀
        armorlabelpathSet.insert(QString(fileName).toInt());
    }

    //遍历armorlabel容器的值并打印到plaintext
    for(int armoritem : armorlabelpathSet)
    {
        QString item = QString::number(armoritem) + '\n';
        ui->plainTextEdit->appendPlainText(item);
        qDebug()<<armoritem<<endl;
    }
    ui->plainTextEdit->appendPlainText(QString("armorlabel总共有：%1个").arg(armorlabelfiles.size()));
    qDebug()<<QString("armorlabel总共有：%1个").arg(armorlabelfiles.size());

    //遍历armorlabel容器并插入tablewidget对应行
    for(int armoritem : armorlabelpathSet)
    {
        ui->tableWidget->item(armoritem-1,1)->setText(QString("%1").arg(armoritem));
    }


    //检查空行
    on_pbcheckarmor_clicked();

}

void Widget::on_pbcheckarmor_clicked()
{
    // 首次清空
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->plainTextEdit->clear();

    QString txtfolderPath = ui->lineEdit_armorlabelpath->text();
    ui->tableWidget->setColumnCount(15);  // 设置列数为15

    // 获取指定文件夹内的txt文件列表
    QDir directory(txtfolderPath);
    QStringList filters;
    filters << "*.txt";  // 仅筛选txt文件
    directory.setNameFilters(filters);
    QFileInfoList fileList = directory.entryInfoList();

    // 遍历txt文件列表
    foreach (QFileInfo fileInfo, fileList) {
        QString fileName = fileInfo.baseName();
        // 判断文件名是否为纯数字
        bool isNumeric = false;
        fileName.toInt(&isNumeric);
        if (!isNumeric) {
            continue;  // 跳过非纯数字文件名的文件
        }

        // 打开txt文件并读取数据
        QFile file(fileInfo.filePath());
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            int rowCount = 0;  // 统计行数
            while (!in.atEnd())
            {
                QString line = in.readLine();
                QStringList values = line.split(" ");
                // 创建新行并填充数据
                ui->tableWidget->insertRow(rowCount);
                for (int i = 0; i < values.size(); ++i) {
                    QTableWidgetItem *item = new QTableWidgetItem(values[i]);
                    ui->tableWidget->setItem(rowCount, i+1, item);  //classes + 点的坐标
                    if(i>=5)
                    {
                        QTableWidgetItem* itemdirty = ui->tableWidget->item(rowCount, i+1);
                        if (itemdirty && !itemdirty->text().isEmpty()) {
                            itemdirty->setForeground(Qt::red);
                        }
                        QString plainText = ui->plainTextEdit->toPlainText();
                        QStringList existingData = plainText.split("\n");

                        if (!existingData.contains(fileInfo.baseName())) {
                            ui->plainTextEdit->appendPlainText(fileInfo.baseName());
                        }
                    }
                }

                QTableWidgetItem *fileName = new QTableWidgetItem(fileInfo.baseName());
                ui->tableWidget->setItem(rowCount, 0, fileName);    //filename
                rowCount++;
            }

            file.close();
        }
    }

    int elementCount = ui->plainTextEdit->document()->blockCount();
    ui->plainTextEdit->appendPlainText(QString("\n-------------\n"));
    if(elementCount - 1 != 0){
        ui->plainTextEdit->appendPlainText(QString("mouse shit all: %1").arg(elementCount-1));
    }
    else {
        ui->plainTextEdit->appendPlainText(QString("congratulation, all file format is well !"));
    }
    ui->plainTextEdit->appendPlainText(QString("\n-------------\n"));

    // 遍历表格的每一行，统计第一列元素的个数
    QMap<int, int> elementCountMap;
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem *item = ui->tableWidget->item(row, 1);
        if (item) {
            int element = item->text().toInt();
            elementCountMap[element]++;
        }
    }

    // 输出每个元素的个数
    QMapIterator<int, int> it(elementCountMap);
    QList<int> armorClassCount;
    int totalLabels = 0;
    while (it.hasNext()) {
        it.next();
        int key = it.key();
        int value = it.value();
        armorClassCount << value;
        ui->plainTextEdit->appendPlainText(QString("%1 :%2").arg(armorMap[key]).arg(value));
        totalLabels += value;
    }
    ui->plainTextEdit->appendPlainText(QString("\n-------------\n"));
    ui->plainTextEdit->appendPlainText(QString(" Total number of labels: %1").arg(totalLabels));


    window.setWindowTitle("Armor Bar Chart");
    window.resize(1200, 1000);

    // 创建柱状图
    QChart *chart = new QChart();

    // 创建柱状图数据系列
    QBarSeries *series = new QBarSeries();

    // 创建柱状图数据
    QBarSet *data = new QBarSet("Data");
    for(int i = 0; i < armorClassCount.size(); ++i)
    {
        int value = armorClassCount[i];
        *data << value;
    }

    // 将数据添加到系列中
    series->append(data);

    // 设置柱子顶部标签显示
    series->setLabelsVisible(true);

    // 将系列添加到柱状图中
    chart->addSeries(series);

    // 创建X轴和Y轴
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QStringList armorList = (QStringList() << "B1" << "B2" << "B3" << "B4" << "B5" << "B7"
                                            << "R1" << "R2" << "R3" << "R4" << "R5" << "R7");
    axisX->append(armorList);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // 创建图表视图并设置柱状图
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 创建布局，并将图表视图添加到布局中
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);

    // 将布局设置为窗口的主布局
    window.setLayout(layout);

    // 显示窗口
    window.show();


}

void Widget::on_pbExecute_clicked()
{
    std::set<QString>reserveSet;
    QString reservePath = ui->lePath->text();
    QString reserveClass = ui->leClass->text();
    QStringList filterList = ui->leClass->text().split(",");

    QDir reservefolder(reservePath);
    QStringList reservefiles = reservefolder.entryList(QDir::Files); // 获取文件列表

    // 遍历文件列表并插入reservefiles容器
    foreach (QString file, reservefiles)
    {
        QFileInfo fileInfo(file);
        bool isNum;
        fileInfo.baseName().toInt(&isNum);
        if(isNum && fileInfo.suffix() == "txt")
        {
            reserveSet.insert(QString(fileInfo.fileName()));
        }
        else {
            qDebug()<<QString("%1 is no number").arg(fileInfo.fileName());
        }

    }

    foreach(QString itemname,reserveSet)
    {
        QString filename = QString("%1/%2").arg(ui->lePath->text()).arg(itemname);
        if(!QFile(filename).exists())
        {
            qDebug()<<QString("%1 file don't exist").arg(filename);
            QMessageBox::warning(NULL,"warning",QString("%1 don't exist").arg(filename));
        }

        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file" << filename;
            QMessageBox::warning(NULL,"warning",QString("Failed to open file"));
            return;
        }

        QStringList lines; // 存储文件每一行的内容
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList words = line.split(" ");
            QString firstWord = words.first();
            int lineNum = firstWord.toInt();
            if(lineNum == filterList.at(0).toInt() || lineNum == filterList.at(1).toInt() || lineNum == filterList.at(2).toInt())
            {
                lines.append(line);
            }
        }
        file.close();
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            qDebug() << "Failed to open file: " << file.errorString();
            return;
        }
        QTextStream out(&file);
        for (const QString& line : lines) {
            out << line << endl;
        }
        file.close();
    }



    qDebug()<<QString("reserveSet total item is: %1").arg(reserveSet.size());
    QMessageBox::information(NULL,"info","complete!");
}

void Widget::on_pbClean_clicked()
{
    // 获取程序开始执行的时间
    QDateTime startTime = QDateTime::currentDateTime();

    std::set<QString>sourceFileSet;
    QString cleanPath =ui->lineEdit_cleanPath->text();
    QString cleanType = ui->lineEdit_cleantype->text();
    QString targetType = ui->lineEdit_targetcleantype->text();
    QStringList cleanTypeList = cleanType.split(",");

    QDir sourcefolder(cleanPath);
    QStringList allfiles = sourcefolder.entryList(QDir::Files);

    QStringList sourcefiles;
    //指定一定范围
    if(!ui->lineEdit_txtrange->text().isEmpty())
    {
        QString range = ui->lineEdit_txtrange->text();
        QStringList rangeList = range.split("-");
        int startNumber = rangeList[0].toInt();
        int endNumber = rangeList[1].toInt();
        foreach (const QString& fileName, allfiles) {
            QString baseName = QFileInfo(fileName).baseName();
            bool ok;
            int fileNumber = baseName.toInt(&ok);
            if (ok && fileNumber >= startNumber && fileNumber <= endNumber) {
                sourcefiles.append(fileName);
            }
        }
    }else {
        sourcefiles = allfiles;
    }
    qDebug()<<allfiles<<__LINE__<<endl;
    qDebug()<<sourcefiles<<__LINE__<<endl;

    foreach(QString file,sourcefiles)
    {
        QFileInfo fileInfo(file);
        bool isNum;
        fileInfo.baseName().toInt(&isNum);
        if(isNum && fileInfo.suffix() == "txt")
        {
            sourceFileSet.insert(QString(fileInfo.fileName()));
        }
        else {
            qDebug()<<QString("%1 is no number").arg(fileInfo.fileName());
            QMessageBox::warning(NULL,"warning",QString("%1 is no number").arg(fileInfo.fileName()));
        }
    }

    foreach(QString itemname,sourceFileSet)
    {
        QString filename = QString("%1/%2").arg(cleanPath).arg(itemname);
        if(!QFile(filename).exists())
        {
            qDebug()<<QString("%1 file don't exist").arg(filename);
            QMessageBox::warning(NULL,"warning",QString("%1 don't exist").arg(filename));
        }

        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file" << filename;
            QMessageBox::warning(NULL,"warning",QString("Failed to open file"));
            return;
        }

        QStringList lines; // 存储文件每一行的内容
        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList dataList = line.split(" ");

            if(cleanTypeList.contains(dataList[0])/*dataList[0] == cleanTypeList[0] || dataList[0] == cleanTypeList[1]*/)
            {
                dataList[0] = targetType;
            }
            line = dataList.join(" ");
            lines.append(line);
        }

        file.close();
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            qDebug() << "Failed to open file: " << file.errorString();
            return;
        }
        QTextStream out(&file);
        for (const QString& line : lines) {
            out << line << endl;
        }
        file.close();
    }

    // 获取程序执行结束的时间
      QDateTime endTime = QDateTime::currentDateTime();
      // 计算程序执行时间，单位为毫秒
      qint64 elapsedTime = startTime.msecsTo(endTime);


    qDebug()<<QString("sourceFileSet total item is: %1").arg(sourceFileSet.size());
    QMessageBox::information(NULL,"info",QString("complete! time-consuming %1ms").arg(elapsedTime));
}

void Widget::on_pbCheckNull_clicked()
{
    std::set<QString>txtFileSet;
    std::set<QString>emptyTXTSet;
    std::set<QString>emptyIMGSet;
    QString checkNullTxtPath = ui->lineEdit_checkNull_TXTPath->text();
    QString checkNullIMGPath = ui->lineEdit_checkNull_IMGPath->text();

    QDir txtFolderDir(checkNullTxtPath);
    QStringList txtList = txtFolderDir.entryList(QDir::Files);

    if(checkNullTxtPath.isEmpty() || checkNullIMGPath.isEmpty())
    {
        QMessageBox::warning(NULL,"warning","please input txt and img path!");
        return;
    }

    //把所有 数字.txt 存入容器
    foreach(QString file , txtList)
    {
        QFileInfo fileInfo(file);
        bool isNum;
        fileInfo.baseName().toInt(&isNum);
        if(isNum && fileInfo.suffix() == "txt")
        {
            txtFileSet.insert(QString(fileInfo.fileName()));
        }
        else {
            qDebug()<<QString("%1 filename is no number").arg(fileInfo.fileName());
            QMessageBox::warning(NULL,"warning",QString("%1 filename is no number").arg(fileInfo.fileName()));
        }
    }

    //检查每个txt内容是否为空
    foreach(QString itemname, txtFileSet)
    {
        QString filename = QString("%1/%2").arg(checkNullTxtPath).arg(itemname);
        if(!QFile(filename).exists())
        {
            qDebug()<<QString("%1 file don't exist").arg(filename);
            QMessageBox::warning(NULL,"warning",QString("%1 don't exist").arg(filename));
        }

        QFile file(filename);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString content = QString::fromUtf8(file.readAll());
            file.close();
            if(content.trimmed().isEmpty()) // 检查内容是否为空（去除首尾空白字符）
            {
                emptyTXTSet.insert(itemname);
                QFileInfo fileInfo(filename);
                qDebug()<<QString("%1/%2.jpg").arg(checkNullIMGPath).arg(fileInfo.baseName());
                QFile::remove(filename); //删除TXT
                QFile::remove(QString("%1/%2.jpg").arg(checkNullIMGPath).arg(fileInfo.baseName())); //删除IMG
            }
        } else {
            QMessageBox::warning(NULL,"warning",QString("cannot open %1 file").arg(filename)); // 文件打开失败
        }
    }



    QString emptyTXTString;
    foreach(QString itemname, emptyTXTSet)
    {
        qDebug()<<"empty txt is"<<itemname<<endl;
        emptyTXTString.append(itemname);
        emptyTXTString.append('\n');
    }

    if(emptyTXTSet.empty())
        QMessageBox::information(NULL,QString("info"),QString("congratulation! Folder don't have empty files!"));
    else
        QMessageBox::information(NULL,QString("info"),QString("finish!\n empty TXT is \n%1").arg(emptyTXTString));
}

void Widget::on_pb_retainDele_clicked()
{
    std::set<QString>txtFileSet;
    std::set<QString>surplusSet;
    QString retainTXTPath = ui->lineEdit_retainTXTPath->text();
    QString retainClass = ui->lineEdit_ratainClass->text();

    QStringList retainClassList = retainClass.split(",");

    QDir retainfolder(retainTXTPath);
    QStringList retainTXTList = retainfolder.entryList(QDir::Files);

    foreach(QString file,retainTXTList)
    {
        QFileInfo fileInfo(file);
        bool isNum;
        fileInfo.baseName().toInt(&isNum);
        if(isNum && fileInfo.suffix() == "txt")
        {
            txtFileSet.insert(QString(fileInfo.fileName()));
        }
        else {
            qDebug()<<QString("%1 is no number").arg(fileInfo.fileName());
            QMessageBox::warning(NULL,"warning",QString("%1 is no number").arg(fileInfo.fileName()));
        }
    }

    foreach(QString itemname, txtFileSet)
    {
        QString filename = QString("%1/%2").arg(retainTXTPath).arg(itemname);
        if(!QFile(filename).exists())
        {
            qDebug()<<QString("%1 file don't exist").arg(filename);
            QMessageBox::warning(NULL,"warning",QString("%1 don't exist").arg(filename));
        }

        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file" << filename;
            QMessageBox::warning(NULL,"warning",QString("Failed to open file"));
            return;
        }

        QStringList lines; // 存储文件每一行的内容
        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList dataList = line.split(" ");
            if(retainClassList.contains(dataList[0]))
            {
                lines.append(line);
            }else {
                surplusSet.insert(itemname);
            }
        }
        file.close();
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            qDebug() << "Failed to open file: " << file.errorString();
            return;
        }
        QTextStream out(&file);
        for (const QString& line : lines) {
            out << line << endl;
        }
        file.close();
    }


    QString surplusString;
    foreach(QString itemname, surplusSet)
    {
        qDebug()<<"empty txt is"<<itemname<<endl;
        surplusString.append(itemname);
        surplusString.append('\n');
    }

    if(surplusSet.empty())
        QMessageBox::information(NULL,QString("info"),QString("congratulation! Folder TXT don't have surplus class!"));
    else
        QMessageBox::information(NULL,QString("info"),QString("finish!\n surplus class TXT is \n%1").arg(surplusString));

}

void Widget::on_pb_DeleExcessFile_clicked()
{
    std::set<QString>txtBaseNameSet,imgBaseNameSet;
    std::set<QString> differenceTXT,differenceIMG;
    QString excessTXTPath = ui->lineEdit_excessTXTPath->text();
    QString excessIMGPath = ui->lineEdit_excessIMGPath->text();

    if(excessTXTPath.isEmpty() || excessIMGPath.isEmpty())
    {
        QMessageBox::warning(NULL,"warning","please input txt and img path!");
        return;
    }

    QDir excessTXTDir(excessTXTPath);
    QStringList excessTXTList = excessTXTDir.entryList(QDir::Files);
    QDir excessIMGDir(excessIMGPath);
    QStringList excessIMGList = excessIMGDir.entryList(QDir::Files);

    QStringList diffTXTList,diffIMGList;

    foreach(QString txt, excessTXTList)
    {
        QFileInfo txtfile(txt);
        txtBaseNameSet.insert(txtfile.baseName());
    }

    foreach(QString img,excessIMGList)
    {
        QFileInfo imgFile(img);
        imgBaseNameSet.insert(imgFile.baseName());
    }

    foreach(QString str,txtBaseNameSet)
    {
        qDebug()<<"txtbasename:"<<str;
    }


    foreach(QString str,imgBaseNameSet)
    {
        qDebug()<<"imgbasename:"<<str;
    }

    // 查找 txt 中多余的项，并存储在 differenceTXT 中
    std::set_difference(txtBaseNameSet.begin(), txtBaseNameSet.end(), imgBaseNameSet.begin(), imgBaseNameSet.end(), std::inserter(differenceTXT, differenceTXT.begin()),CustomCompare());

    if (differenceTXT.empty()) {
        qDebug() << "differenceTXT Sets are equal." << endl;
    } else {
        qDebug() << "Sets are not equal. Extra items in differenceTXT:" << endl;
        for (const auto& item : differenceTXT) {
            qDebug() << item << endl;
            QFile::remove(QString("%1/%2.txt").arg(excessTXTPath).arg(item));
        }
    }

    // 查找 img 中多余的项，并存储在 differenceIMG 中
    std::set_difference(imgBaseNameSet.begin(), imgBaseNameSet.end(), txtBaseNameSet.begin(), txtBaseNameSet.end(), std::inserter(differenceIMG, differenceIMG.begin()),CustomCompare());

    if (differenceIMG.empty()) {
        qDebug() << "differenceTXT Sets are equal." << endl;
    } else {
        qDebug() << "Sets are not equal. Extra items in differenceTXT:" << endl;
        for (const auto& item : differenceIMG) {
            qDebug() << item << endl;
            QFile::remove(QString("%1/%2.jpg").arg(excessIMGPath).arg(item));
            QFile::remove(QString("%1/%2.png").arg(excessIMGPath).arg(item));
        }
    }
    QMessageBox::information(NULL,"info","complete!");
}

bool Widget::isNumeric(const QString& str)
{
    QRegularExpression regex("^[0-9]+$");
    QRegularExpressionMatch match = regex.match(str);
    return match.hasMatch();
}

bool Widget::isFolderExists(const QString &folderPath)
{
    QDir folderDir(folderPath);
    return folderDir.exists();
}

void Widget::renumberFiles(const QString& folderPath, int startNumber, const QString& fileType)
{
    QDir folderDir(folderPath);
    QStringList fileNames = folderDir.entryList(QDir::Files | QDir::NoDotAndDotDot);

    int currentNumber = startNumber;

    foreach (const QString& fileName, fileNames) {
        QString currentFilePath = folderDir.filePath(fileName);

        // 检查文件名是否是数字
        if (!isNumeric(fileName.left(fileName.lastIndexOf('.')))) {
            qDebug() << "Skipping file" << currentFilePath << "- Invalid numeric file name";
            continue;
        }

        // 检查文件类型
        QString fileExtension = QFileInfo(fileName).suffix();
        if (fileExtension.toLower() != fileType) {
            qDebug() << "Skipping file" << currentFilePath << "- Invalid file type";
            continue;
        }

        // 构建新的文件名
        QString newFileName = QString("%1.%2").arg(currentNumber, 6, 10, QChar('0')).arg(fileExtension);

        // 构建新的文件路径
        QString newFilePath = folderDir.filePath(newFileName);

        // 重命名文件
        if (QFile::rename(currentFilePath, newFilePath)) {
            qDebug() << "Renamed file" << currentFilePath << "to" << newFilePath;
        } else {
            qDebug() << "Failed to rename file" << currentFilePath;
        }

        ++currentNumber;
    }
}

void Widget::on_pb_startrenamesort_clicked()
{
    int startNum = ui->lineEdit_sort_startnum->text().toInt();
    QString sortTXTPath = ui->lineEdit_sort_txtpath->text();
    QString sortIMGPath = ui->lineEdit_sort_imgpath->text();

    if(ui->lineEdit_sort_startnum->text().isEmpty())
    {
        QMessageBox::warning(NULL,"warning","please input startNum!");
        return;
    }

    if(!sortTXTPath.isEmpty() && isFolderExists(sortTXTPath))
    {
        renumberFiles(sortTXTPath, startNum, "txt");
        QMessageBox::information(NULL,"info","TXT sort finish!");
    }else {
        QMessageBox::warning(NULL,"info","please input correct TXT Path!");
    }

    if(!sortIMGPath.isEmpty() && isFolderExists(sortIMGPath))
    {
        renumberFiles(sortIMGPath, startNum, "jpg");
        QMessageBox::information(NULL,"info","IMG sort finish!");
    }else {
        QMessageBox::warning(NULL,"info","please input correct IMG Path!");
    }
}


