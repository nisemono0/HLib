#include "gui/mainwindow.h"
#include "utils/utilfuncs.h"
#include "utils/utildefs.h"

#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QDirIterator>
#include <QMessageBox>
#include <QProgressDialog>
#include <QString>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QShortcut>
#include <QMenu>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), db("HLib_CON") {
    this->ui.setupUi(this);

    new QShortcut(QKeySequence(Qt::Key_Right), this, [=] { ui.graphicsView->setCurrentImage(SetImageOption::NextImage);});
    new QShortcut(QKeySequence(Qt::Key_Left), this, [=] { ui.graphicsView->setCurrentImage(SetImageOption::PrevImage);});
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_F), this, [=] { ui.lineEditSearch->setFocus();});

    this->ui.treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    
    this->tree_status = new QLabel(this);
    this->img_status = new QLabel(this);
    
    this->ui.graphicsView->addStatusLabel(this->img_status);
    this->img_status->setHidden(true);
    this->resetTreeStatusMessage();
    
    this->ui.statusBar->addWidget(tree_status);
    this->ui.statusBar->addPermanentWidget(img_status);

    this->pixitem = new QGraphicsPixmapItem();
    this->pixitem->setTransformationMode(Qt::SmoothTransformation);

    this->scene = new QGraphicsScene();
    this->scene->addItem(this->pixitem);

    this->ui.graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->ui.graphicsView->setScene(scene);

    this->ui.treeWidget->setSortingEnabled(true);
    this->ui.treeWidget->sortItems(0, Qt::AscendingOrder);

    this->lockWindowItems();

    connect(this->ui.actionAddFile, &QAction::triggered, this, &MainWindow::triggered_action_addFile);
    connect(this->ui.actionAddDir, &QAction::triggered, this, &MainWindow::triggered_action_addDir);
    connect(this->ui.actionExit, &QAction::triggered, this, [=] { db.closeDB(); qApp->quit();});

    connect(this->ui.actionCreateDB, &QAction::triggered, this, &MainWindow::triggered_action_createDB);
    connect(this->ui.actionLoadDB, &QAction::triggered, this, &MainWindow::triggered_action_loadDB);
    connect(this->ui.actionUnloadDB, &QAction::triggered, this, &MainWindow::triggered_action_unloadDB);

    connect(this->ui.actionThemeDarkMaroon, &QAction::triggered, this, [=] { MainWindow::triggered_action_changeTheme(MyTheme::DARK_MAROON);});
    connect(this->ui.actionThemeDarkGreen, &QAction::triggered, this, [=] { MainWindow::triggered_action_changeTheme(MyTheme::DARK_GREEN);});
    connect(this->ui.actionThemeDarkPurple, &QAction::triggered, this, [=] { MainWindow::triggered_action_changeTheme(MyTheme::DARK_PURPLE);});
    connect(this->ui.actionThemeFusion, &QAction::triggered, this, [=] { MainWindow::triggered_action_changeTheme(MyTheme::FUSION);});
    connect(this->ui.actionThemeWindows, &QAction::triggered, this, [=] { MainWindow::triggered_action_changeTheme(MyTheme::WINDOWS);});

    connect(this->ui.pushButtonSearch, &QPushButton::pressed, this, [=] { MainWindow::searchTreeItems(ui.lineEditSearch->text());});
    connect(this->ui.lineEditSearch, &QLineEdit::returnPressed, this, [=] { MainWindow::searchTreeItems(ui.lineEditSearch->text());});
    connect(this->ui.pushButtonRefresh, &QPushButton::pressed, this, [=] {ui.lineEditSearch->setText(""); MainWindow::searchTreeItems("");});

    connect(this->ui.treeWidget, &QTreeWidget::currentItemChanged, this, &MainWindow::treeItemChanged);
    connect(this->ui.treeWidget, &QTreeWidget::customContextMenuRequested, this, &MainWindow::showTreeContextMenu);
    connect(this->ui.treeWidget, &QTreeWidget::itemDoubleClicked, this, &MainWindow::treeDoubleClick);
}

MainWindow::~MainWindow() {
    delete this->pixitem;
    delete this->scene;
    delete this->tree_status;
    delete this->img_status;
}

void MainWindow::triggered_action_changeTheme(const MyTheme::MyTheme theme) {
    QFile theme_file;
    QString theme_style;
    switch (theme) {
        case MyTheme::DARK_MAROON:
            theme_file.setFileName(":DarkMaroon.qss");
            break;
        case MyTheme::DARK_GREEN:
            theme_file.setFileName(":DarkGreen.qss");
            break;
        case MyTheme::DARK_PURPLE:
            theme_file.setFileName(":DarkPurple.qss");
            break;
        case MyTheme::FUSION:
            theme_style = "Fusion";
            break;
        case MyTheme::WINDOWS:
            theme_style = "Windows";
            break;
    };

    if (theme_file.exists()) {
        theme_file.open(QFile::ReadOnly);
        if (theme_file.isOpen()) {
            qApp->style()->unpolish(qApp);
            qApp->setStyle("Fusion");
            qApp->setStyleSheet(QString::fromLatin1(theme_file.readAll()));
            qApp->style()->polish(qApp);
            theme_file.close();
        }
    } else {
        qApp->style()->unpolish(qApp);
        qApp->setStyleSheet("");
        qApp->setStyle(theme_style);
        qApp->style()->polish(qApp);
    }
}

void MainWindow::triggered_action_addFile() {
    QString file_path = QFileDialog::getOpenFileName(this, "Open zip archive", QDir::homePath(), { "Zip files (*.zip)" });
    if (Utils::isNullOrEmpty(file_path)) {
        return;
    }

    if (QFile::exists(file_path)) {
        QJsonObject json_obj = Utils::getJsonFromZip(file_path, "info.json");
        QMap json_map = Utils::getMapFromJson(json_obj);

        if (!json_map.isEmpty()) {
            QStringList hash_list = this->db.selectAllHashes();
            if (!hash_list.contains(json_map["file_hash"])) {
                if (this->db.insert(json_map)) {
                    this->populateTree();
                    QMessageBox::information(this, "Info", "Added to database");
                } else {
                    QMessageBox::warning(this, "Warning", "Couldn't add to database");
                }
            }
        }
    }
}

void MainWindow::triggered_action_addDir() {
    QString dir_path = QFileDialog::getExistingDirectory(this, "Open directory", QDir::homePath(), QFileDialog::ShowDirsOnly);
    
    if (Utils::isNullOrEmpty(dir_path)) {
        return;
    }

    if (Utils::isDirEmpty(dir_path)) {
        QMessageBox::information(this, "Info", "Directory is empty");
        return;
    }

    QStringList zip_files = Utils::getZipFilesList(dir_path);

    if (zip_files.isEmpty()) {
        QMessageBox::information(this, "Info", "No zip files found");
        return;
    }

    QList<QMap<QString, QString>> data_list;
    QStringList db_hashes = this->db.selectAllHashes();
    
    QProgressDialog progress("Adding files to DB", nullptr, 0, zip_files.length(), this);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    for (int i = 0; i < zip_files.length(); i++) {
        QJsonObject json_obj = Utils::getJsonFromZip(zip_files[i], "info.json");
        QMap json_map = Utils::getMapFromJson(json_obj);

        if (!json_map.isEmpty()) {
            if (!db_hashes.contains(json_map["file_hash"])) {
                data_list.append(json_map);
            }
        }

        progress.setValue(i);
        progress.setLabelText(QString("Working on files: [%1/%2]").arg(QString::number(i + 1), QString::number(zip_files.length())));
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }
    if (this->db.insert(data_list)) {
        this->populateTree();
        progress.hide();
        QMessageBox::information(this, "Info", "Added to database");
    } else {
        QMessageBox::warning(this, "Warning", "Couldn't add to database");
    }
}

void MainWindow::triggered_action_createDB() {
    QString db_file = QFileDialog::getSaveFileName(this, "Open DB", QDir::homePath(), { "SQLite database (*.sqlite *.sqlite3 *db *db3) ;; All files (*)" });

    if (Utils::isNullOrEmpty(db_file)) {
        return;
    }
    
    if (Utils::createDB(db_file, "HLib_CON_CREATE_DB")) {
        QMessageBox::information(this, "Info", "Database created, you can load it now");
    } else {
        QMessageBox::warning(this, "Warning", "Couldn't create database");
    }
}

void MainWindow::triggered_action_loadDB() {
    QString db_file = QFileDialog::getOpenFileName(this, "Open DB", QDir::homePath(), { "SQLite database (*.sqlite *.sqlite3 *db *db3) ;; All files (*)" });

    if (Utils::isNullOrEmpty(db_file)) {
        return;
    }

    this->clearView();
    this->ui.lineEditSearch->setText("");
    
    this->db.setDBPath(db_file);
    if (this->db.openDB()) {
        this->unlockWindowItems();
        this->populateTree();
        QMessageBox::information(this, "Info", "Database loaded");
    } else {
        QMessageBox::warning(this, "Warning", "Couldn't load database");
    }
}

void MainWindow::triggered_action_unloadDB() {
    this->db.closeDB();
    this->clearTree();
    this->clearView();
    this->ui.lineEditSearch->setText("");
    this->resetTreeStatusMessage();
    this->lockWindowItems();
    QMessageBox::information(this, "Info", "Database unloaded");
}

void MainWindow::lockWindowItems() {
    this->ui.actionAddFile->setEnabled(false);
    this->ui.actionAddDir->setEnabled(false);
    this->ui.actionLoadDB->setEnabled(true);
    this->ui.actionUnloadDB->setEnabled(false);
    this->ui.lineEditSearch->setEnabled(false);
    this->ui.pushButtonSearch->setEnabled(false);
    this->ui.pushButtonRefresh->setEnabled(false);
}

void MainWindow::unlockWindowItems() {
    this->ui.actionAddFile->setEnabled(true);
    this->ui.actionAddDir->setEnabled(true);
    this->ui.actionLoadDB->setEnabled(false);
    this->ui.actionUnloadDB->setEnabled(true);
    this->ui.lineEditSearch->setEnabled(true);
    this->ui.pushButtonSearch->setEnabled(true);
    this->ui.pushButtonRefresh->setEnabled(true);
}

void MainWindow::clearTree() {
    this->ui.treeWidget->clear();
}

void MainWindow::clearView() {
    this->ui.graphicsView->clearImageView();
    this->pixitem->setPixmap(QPixmap());
}

void MainWindow::resetTreeStatusMessage() {
    this->tree_status->setText("No database loaded");
}

void MainWindow::setTreeStatusMessage() {
    this->tree_status->setText(QString("Loaded: [%1] archives").arg(QString::number(this->ui.treeWidget->topLevelItemCount())));
}

void MainWindow::setTreeStatusMessage(const QString message) {
    this->tree_status->setText(message);
}

void MainWindow::populateTree() {
    QList<QMap<QString, QVariant>> list_variants = this->db.select();
    if (list_variants.isEmpty()) {
        this->setTreeStatusMessage("Empty database");
        return;
    }

    this->clearTree();
    QList<QTreeWidgetItem *> root_items;
    for (auto it : list_variants) {
        QTreeWidgetItem *root = new QTreeWidgetItem();
        root->setText(0, it["title"].toString());
        root->setData(0, MyDataRoles::Title, it["title"].toString());
        root->setData(0, MyDataRoles::FilePath, it["file_path"].toString());
        root->setData(0, MyDataRoles::FileHash, it["file_hash"].toString());
        root->setData(0, MyDataRoles::Tags, it["tags"].toString());
        root_items.append(root);
    }
    this->ui.treeWidget->addTopLevelItems(root_items);
    
    this->setTreeStatusMessage();
}

void MainWindow::searchTreeItems(const QString search_str) {    
    QStringList hash_list = this->db.select(search_str);
    
    QTreeWidgetItemIterator tree_it(this->ui.treeWidget);
    while (*tree_it) {
        if (Utils::isNullOrEmpty(search_str)) {
            (*tree_it)->setHidden(false);
        } else {
            QString tree_item_hash = (*tree_it)->data(0, MyDataRoles::FileHash).toString();
            if (hash_list.contains(tree_item_hash, Qt::CaseSensitive)) {
                (*tree_it)->setHidden(false);
            } else {
                (*tree_it)->setHidden(true);
            }
        }
        tree_it++;
    }
}

void MainWindow::loadAllImages(const QString item_path) {
    QByteArrayList images_list = Utils::getImagesFromZip(item_path, this);
    
    if (images_list.isEmpty()) {
        return;
    }

    QPixmap img;
    if (img.loadFromData(images_list[0])) {
        this->pixitem->setPixmap(img);
        this->pixitem->setData(MyDataRoles::FilePath, QVariant::fromValue(item_path));
        this->ui.graphicsView->loadImages(images_list);
    }
}

void MainWindow::loadFIrstImage(const QString file_path) {
    QByteArray zip_image = Utils::getFirstImageFromZip(file_path);
    
    if (Utils::isNullOrEmpty(zip_image)) {
        return;
    }

    QPixmap img;
    if (img.loadFromData(zip_image)) {
        this->pixitem->setPixmap(img);
        this->pixitem->setData(MyDataRoles::FilePath, QVariant::fromValue(file_path));
        this->ui.graphicsView->loadImages(zip_image);
    }
}

void MainWindow::treeItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous) {
    this->clearView();
    
    if (current == nullptr) {
        return;
    }
    
    QString item_path = current->data(0, MyDataRoles::FilePath).toString();
    this->loadFIrstImage(item_path);
}

void MainWindow::showTreeContextMenu(const QPoint &pos) {
    QModelIndex index = this->ui.treeWidget->indexAt(pos);
    if (!index.isValid())
        return;
    
    QTreeWidgetItem *item = this->ui.treeWidget->itemAt(pos);    
    QString item_filepath = item->data(0, MyDataRoles::FilePath).toString();
    QString item_filename = item->text(0);
    QString item_tags = item->data(0, MyDataRoles::Tags).toString();

    QMenu menu(this);
    QAction *load_all_images = new QAction("Load all images", &menu);
    QAction *copy_title = new QAction("Copy title", &menu);
    QAction *copy_filepath = new QAction("Copy path", &menu);
    QAction *copy_tags = new QAction("Copy tags", &menu);
    menu.addAction(load_all_images);
    menu.addAction(copy_title);
    menu.addAction(copy_filepath);
    menu.addAction(copy_tags);
    QAction *clicked_action = menu.exec(this->ui.treeWidget->viewport()->mapToGlobal(pos));

    if (!clicked_action) {
        return;
    }

    if (clicked_action == load_all_images) {
        this->loadAllImages(item_filepath);        
    }
    else if (clicked_action == copy_title) {
        QApplication::clipboard()->clear();
        QApplication::clipboard()->setText(item_filename, QClipboard::Clipboard);
    } else if (clicked_action == copy_filepath) {
        QApplication::clipboard()->clear();
        QApplication::clipboard()->setText(item_filepath, QClipboard::Clipboard);
    } else if (clicked_action == copy_tags) {
        QApplication::clipboard()->clear();
        QApplication::clipboard()->setText(item_tags, QClipboard::Clipboard);
    }
}

void MainWindow::treeDoubleClick(QTreeWidgetItem *item, int column) {
    if (item == nullptr) {
        return;
    }
    
    QString item_filepath = item->data(column, MyDataRoles::FilePath).toString();
    this->loadAllImages(item_filepath);
}