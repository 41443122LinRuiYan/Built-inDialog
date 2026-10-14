#include "dialog.h"
#include <QDebug>
#include <QtPrintSupport/qprinter.h>
#include <QtPrintSupport/qpagesetupdialog.h>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
Dialog::Dialog(QWidget *parent)//建構函數
    : QDialog(parent)
{
    QGridLayout* gridLatout = new QGridLayout;
    DisplayTextEdit = new QTextEdit(QStringLiteral("Qt的標準通用對話盒"));
    colorPushBtn = new QPushButton(QStringLiteral("顏色對話盒"));
    errorPushBtn = new QPushButton(QStringLiteral("錯誤訊息盒"));
    filePushBtn = new QPushButton(QStringLiteral("檔案對話盒"));
    fontPushBtn = new QPushButton(QStringLiteral("字體對話盒"));
    inputPushBtn = new QPushButton(QStringLiteral("輸入對話盒"));
    pagePushBtn = new QPushButton(QStringLiteral("頁面設定對話盒"));
    progressPushBtn = new QPushButton(QStringLiteral("進度設定對話盒"));
    printPushBtn =new QPushButton(QStringLiteral("列印對話盒"));
    recolorPushBtn =new QPushButton(QStringLiteral("更換文字顏色"));

    gridLatout->addWidget(colorPushBtn,0,0,1,1);
    gridLatout->addWidget(errorPushBtn,0,1,1,1);
    gridLatout->addWidget(filePushBtn,0,2,1,1);
    gridLatout->addWidget(fontPushBtn,1,0,1,1);
    gridLatout->addWidget(inputPushBtn,1,1,1,1);
    gridLatout->addWidget(pagePushBtn,1,2,1,1);
    gridLatout->addWidget(progressPushBtn,2,0,1,1);
    gridLatout->addWidget(printPushBtn,2,1,1,1);
    gridLatout->addWidget(DisplayTextEdit,3,0,3,3);
    gridLatout->addWidget(recolorPushBtn,2,2,1,1);

    setLayout(gridLatout);
    setWindowTitle(QStringLiteral("內建對話盒展示"));
    resize(400,300);

    connect(colorPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(errorPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(filePushBtn,  SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(fontPushBtn,  SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(inputPushBtn,  SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(pagePushBtn,  SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(progressPushBtn,  SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(printPushBtn,  SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(recolorPushBtn,  SIGNAL(clicked()), this, SLOT(doPushBtn()));
}


Dialog::~Dialog()
{

}
void Dialog :: doPushBtn()//槽函數
{
    QPushButton* btn =qobject_cast<QPushButton*>(sender());
    if(btn == colorPushBtn)
    {
        QPalette palette =DisplayTextEdit->palette();//調出DisplayTextEdit所屬的調色盤物件
        const QColor& color = QColorDialog::getColor(palette.color(QPalette::Base),this,"選擇顏色");

        if(color.isValid()){
            palette.setColor(QPalette::Base,color);
            DisplayTextEdit->setPalette(palette);
        }
    }
    if(btn == recolorPushBtn)
    {
        QPalette palette =DisplayTextEdit->palette();//調出DisplayTextEdit所屬的調色盤物件
        const QColor& color = QColorDialog::getColor(palette.color(QPalette::Text),this,"選擇顏色");

        if(color.isValid()){
            palette.setColor(QPalette::Text,color);
            DisplayTextEdit->setPalette(palette);
        }
    }
    if (btn == errorPushBtn)
    {
        QErrorMessage box(this);
        box.setWindowTitle(QStringLiteral("錯誤訊息盒"));
        // 只保留需要顯示的內容，或串接字串
        box.showMessage(QStringLiteral("錯誤訊息盒實例xx = ..."));
        box.exec();
    }
    if(btn == filePushBtn){
        QString fileName = QFileDialog::getOpenFileName(this, "挑選檔案", ".", "All Files (*.*);;Text Files (*.txt)");
        if (!fileName.isEmpty()) {
            DisplayTextEdit->setText(fileName);
        }
        /*Qstring fileName =QFileDialog::getSaveFileName(this,"儲存檔案",".");
        DisplayTextEdit->setText(fileName);*/
    }
    if(btn == fontPushBtn){
        bool ok;
        const QFont& font = QFontDialog::getFont(&ok,DisplayTextEdit->font(),this,QStringLiteral("字體對話盒"));
        if(ok) DisplayTextEdit->setFont(font);
    }
    if (btn == inputPushBtn)
    {
        bool ok;
        QString text = QInputDialog::getText(this, QStringLiteral("輸入對話盒"),QStringLiteral("輸入文字"),QLineEdit::Normal,QDir::home().dirName(),&ok);
        if (ok && !text.isEmpty()) DisplayTextEdit->setText(text);
    }
    if (btn == pagePushBtn)
    {
        QPrinter printer(QPrinter::HighResolution);
        QPageSetupDialog* dlg = new QPageSetupDialog(&printer, this);
        dlg->setWindowTitle(QStringLiteral("頁面設定話方塊"));
        if (dlg->exec() == QDialog::Accepted)
        {

        }
    }
    if (btn == printPushBtn)
    {
        QPrinter printer(QPrinter::HighResolution);
        QPrintDialog dialog(&printer, this);
        if (dialog.exec() != QDialog::Accepted)
            return;
    }

    if(btn == progressPushBtn){
        QProgressDialog progress("複製檔案中...","取消",0,99999,this);
        progress.setWindowTitle("進度對話盒展示");
        progress.show();
        for(int i=0;i<=99999;i++){
            progress.setValue(i);
            qApp->processEvents();
            if(progress.wasCanceled())
                break;
            qDebug() << i;
        }
        progress.setValue(99999);
    }
}