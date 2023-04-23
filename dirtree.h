#ifndef DIRTREE_H
#define DIRTREE_H
#include <QDir>
#include <QMenu>
#include <QLabel>
#include <QDebug>
#include <QDialog>
#include <QProcess>
#include <QComboBox>
#include <QTreeWidget>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QHeaderView>
#include <QApplication>

// 显示文件树的窗体
class TreeMenu : public QTreeWidget{
    Q_OBJECT
public:
    TreeMenu(QWidget *parent = 0);
    void CreateTopItem(QString path);
    void FindFile(QDir *path,QTreeWidgetItem *parent);
    void buttonCollapseItem();
private:
    QTreeWidgetItem *root; //树的根
    QMenu *dirMenu;  //文件夹菜单栏
    QMenu *fileMenu;  //文件菜单栏
    QTreeWidgetItem *nowItem; //当前光标所在Item
    int nowCol; //当前所在列

signals:
    void showTextSignal(QString path,QString name,QTreeWidgetItem *item);
    void collapseItemSignal(const QTreeWidgetItem *item);
    void renameSignal();
private slots:
    void DoubleClickpath(QTreeWidgetItem *item, int column);
    void itemPressedSlot(QTreeWidgetItem * pressedItem, int column);
};

#endif // DIRTREE_H
