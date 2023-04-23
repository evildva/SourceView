#include "dirtree.h"

TreeMenu::TreeMenu(QWidget *parent):QTreeWidget(parent){
    this->setObjectName("TreeMenu");
    this->verticalScrollBar()->setObjectName("TreeMenuVerticl");
    this->horizontalScrollBar()->setObjectName("TreeMenuHorizontal");

    this->setColumnCount(1);
    this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    this->setAutoScroll(true);
    this->header()->setVisible(false);   //隐藏横向表头

    this->setFrameStyle(QFrame::Sunken);
    this->setAnimated(true); //展开折叠动画

    connect(this,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(itemPressedSlot(QTreeWidgetItem*,int)));
    connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(DoubleClickpath(QTreeWidgetItem*,int)));
    connect(this,SIGNAL(collapseItemSignal(const QTreeWidgetItem*)),this,SLOT(collapseItem(const QTreeWidgetItem*)));
}

// 创建文件树的根
void TreeMenu::CreateTopItem(QString path){
    QDir *rootdir = new QDir(path);
    root = new QTreeWidgetItem();
    this->addTopLevelItem(root);
    root->setText(0,rootdir->dirName());
    FindFile(rootdir,root);
    QApplication::processEvents(); //防止界面假死
    root->setExpanded(true);
}
// 创建文件树
void TreeMenu::FindFile(QDir *path,QTreeWidgetItem *parent){
    QApplication::processEvents(); //防止界面假死
    QStringList AllDirName = path->entryList();  //返回所有文件名
    QString PathContent = path->absolutePath();
    for(int i=2;i<AllDirName.size();i++)
    {
        QFileInfo *FileInfo = new QFileInfo(PathContent+"/"+AllDirName[i]);
        if(FileInfo->isFile())
        {
            QTreeWidgetItem *child = new QTreeWidgetItem(parent); //创建对象并添加所属关系
            child->setIcon(0,QIcon(":/new/prefix1/file.png")); //设置Item的图标，也可以通过QSS设置。
            child->setText(0,AllDirName[i]); //设置Item的名字及所扫描到的文件名。
            child->setToolTip(0,PathContent+"/"+AllDirName[i]);
        }
        else if(FileInfo->isDir())
        {
            QDir *NextDir = new QDir(PathContent+"/"+AllDirName[i]); //返回包含文件名的绝对路径。
            QTreeWidgetItem *child = new QTreeWidgetItem(parent);  //创建对象并添加所属关系。
            child->setIcon(0,QIcon(":/new/prefix1/dir.png")); //设置Item的图标，也可以通过QSS设置。
            child->setText(0,AllDirName[i]);  //设置Item的名字及所扫描到的文件名。
            child->setToolTip(0,PathContent+"/"+AllDirName[i]); //鼠标移动到Item上所显示的内容，这里为绝对路径。
            FindFile(NextDir,child);
        }
    }
}
// 双击槽函数检测是文件还是目录
void TreeMenu::DoubleClickpath(QTreeWidgetItem *item, int /*column*/){
    QString absolute_Path = item->toolTip(0);
    QFileInfo *FileInfo = new QFileInfo(absolute_Path);
    this->resizeColumnToContents(0);

    if(FileInfo->isFile())
    {
        // 发送信号量打开文件
        emit showTextSignal(absolute_Path,FileInfo->baseName(),item);
    }
    else{
        // 由于不是文件所以除了执行展开或折叠文件外不再需要执行其他操作，因此此处不需要执行别的操作。
    }
}
// 鼠标右键单击文件或文件夹时所执行的操作
void TreeMenu::itemPressedSlot(QTreeWidgetItem * pressedItem, int column){
    this->resizeColumnToContents(0);
    nowItem = pressedItem;
    nowCol = column;
    if(qApp->mouseButtons() == Qt::LeftButton)   //判断是否为右键
    {
        QString absolute_Path = pressedItem->toolTip(0);
        QFileInfo *FileInfo = new QFileInfo(absolute_Path);
        if(FileInfo->isFile()){
            qDebug()<<absolute_Path;
        }
    }
}
// 文件夹折叠的实现主要为顶部按钮提供方法，顶部按钮的实现下次再讲
void TreeMenu::buttonCollapseItem(){
    QTreeWidgetItem *t = this->currentItem();
    if(t==0)
        return;
    if(t->childCount()==0){
        QTreeWidgetItem *p = t->parent();
        if(p==0){
            return;
        }
        else{
            emit collapseItemSignal(p); //折叠文件夹
        }
    }
    else{
        emit collapseItemSignal(t);
    }
}
