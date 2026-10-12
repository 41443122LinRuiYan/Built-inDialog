#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])//程式紀錄點
{
    QApplication a(argc, argv);//建立視窗環境
    Dialog w;   //我們宣告的類別之物件實體(w)
    //w.setWindowTitle("我們的對話盒");
    w.show(); //將物件顯示於桌面
    return QApplication::exec(); //進入視窗訊息迴圈
}
