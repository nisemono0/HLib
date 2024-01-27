#include "gui/mainwindow.h"
#include "utils/utilfuncs.h"
#include "utils/logging.h"
#include "utils/utildefs.h"

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
#include <QFileInfo>
#include <QLocale>
#include <QActionGroup>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->ui.setupUi(this);

    this->db = new SQLiteDB("HLib_CON");
    
    this->action_scale_slider = new QWidgetAction(this->ui.menuSettings);
    this->scale_slider = new QSlider(this->ui.menuSettings);
    this->scale_slider->setFixedHeight(25);
    this->scale_slider->setOrientation(Qt::Horizontal);
    this->scale_slider->setTickPosition(QSlider::NoTicks);
    this->scale_slider->setMaximum(10);
    this->scale_slider->setMinimum(0);
    this->scale_slider->setSingleStep(0);
    this->scale_slider->setPageStep(0);
    this->scale_slider->setValue(0);
    this->action_scale_slider->setDefaultWidget(this->scale_slider);
    this->ui.menuSettings->insertAction(this->ui.menuSettingsView->menuAction(), this->action_scale_slider);
    this->ui.menuSettings->insertSeparator(this->ui.menuSettingsView->menuAction());

    this->settings_view_group = new QActionGroup(this->ui.menuSettingsView);
    this->settings_view_group->addAction(this->ui.actionFitInView);
    this->settings_view_group->addAction(this->ui.actionFitToWidth);
    this->settings_view_group->addAction(this->ui.actionFreeView);
    this->settings_view_group->setExclusive(true);

    this->action_zoom_slider = new QWidgetAction(this->ui.menuSettingsView);
    this->zoom_slider = new QSlider(this->ui.menuSettingsView);
    this->zoom_slider->setFixedHeight(25);
    this->zoom_slider->setOrientation(Qt::Horizontal);
    this->zoom_slider->setTickPosition(QSlider::NoTicks);
    this->zoom_slider->setMaximum(10);
    this->zoom_slider->setMinimum(1);
    this->zoom_slider->setSingleStep(0);
    this->zoom_slider->setPageStep(0);
    this->zoom_slider->setValue(1);
    this->action_zoom_slider->setDefaultWidget(this->zoom_slider);
    this->ui.menuSettingsView->addAction(this->action_zoom_slider);

    this->loaded_archives_num = 0;
    this->filtered_archives_num = 0;

    this->search_timer = new QTimer(this);
    this->old_search = this->ui.lineEditSearch->text();
    this->select_first_result = false;

    new QShortcut(QKeySequence(Qt::Key_Right), this, [=] { ui.graphicsView->setCurrentImage(SetImage::NextImage);});
    new QShortcut(QKeySequence(Qt::Key_Left), this, [=] { ui.graphicsView->setCurrentImage(SetImage::PrevImage);});
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
    connect(this->ui.actionExit, &QAction::triggered, this, [=] { db->closeDB(); qApp->quit();});

    connect(this->ui.actionCreateDB, &QAction::triggered, this, &MainWindow::triggered_action_createDB);
    connect(this->ui.actionLoadDB, &QAction::triggered, this, &MainWindow::triggered_action_loadDB);
    connect(this->ui.actionUnloadDB, &QAction::triggered, this, &MainWindow::triggered_action_unloadDB);
    connect(this->ui.actionCleanDB, &QAction::triggered, this, &MainWindow::triggered_action_cleanDB);
    connect(this->ui.actionCleanHashes, &QAction::triggered, this, &MainWindow::triggered_action_cleanHashes);
    connect(this->ui.actionCleanPaths, &QAction::triggered, this, &MainWindow::triggered_action_cleanPaths);
    connect(this->ui.actionCheckDB, &QAction::triggered, this, &MainWindow::triggered_action_checkDB);
    connect(this->ui.actionCheckPaths, &QAction::triggered, this, &MainWindow::triggered_action_checkPaths);

    connect(this->ui.actionScaleImage, &QAction::toggled, this, &MainWindow::triggered_action_scaleimage);
    connect(this->scale_slider, &QSlider::sliderMoved, this, &MainWindow::triggered_action_scalechanged);
    connect(this->settings_view_group, &QActionGroup::triggered, this, &MainWindow::triggered_action_viewfit);
    connect(this->zoom_slider, &QSlider::sliderMoved, this, &MainWindow::triggered_action_zoomchanged);

    connect(this->ui.actionSearchWhileTyping, &QAction::toggled, this, &MainWindow::triggered_action_search_typing);
    connect(this->search_timer, &QTimer::timeout, this, &MainWindow::triggered_search_timer);
    connect(this->ui.actionSelectFirstAfterSearch, &QAction::toggled, this, &MainWindow::triggered_action_select_first_result);

    connect(this->ui.actionShowLogs, &QAction::triggered, this, &MainWindow::triggered_action_showlogs);

    connect(this->ui.actionThemeDarkMaroon, &QAction::triggered, this, [=] { MainWindow::triggered_action_changeTheme(MyTheme::DARK_MAROON);});
    connect(this->ui.actionThemeDarkGreen, &QAction::triggered, this, [=] { MainWindow::triggered_action_changeTheme(MyTheme::DARK_GREEN);});
    connect(this->ui.actionThemeDarkPurple, &QAction::triggered, this, [=] { MainWindow::triggered_action_changeTheme(MyTheme::DARK_PURPLE);});
    connect(this->ui.actionThemeFusion, &QAction::triggered, this, [=] { MainWindow::triggered_action_changeTheme(MyTheme::FUSION);});
    connect(this->ui.actionThemeWindows, &QAction::triggered, this, [=] { MainWindow::triggered_action_changeTheme(MyTheme::WINDOWS);});

    connect(this->ui.pushButtonSearch, &QPushButton::pressed, this, [=] { MainWindow::searchTreeItems(ui.lineEditSearch->text());});
    connect(this->ui.lineEditSearch, &QLineEdit::returnPressed, this, [=] { MainWindow::searchTreeItems(ui.lineEditSearch->text());});
    connect(this->ui.pushButtonRandom, &QPushButton::pressed, this, &MainWindow::randomButtonClicked);
    connect(this->ui.pushButtonRefresh, &QPushButton::pressed, this, &MainWindow::refreshButtonClicked);

    connect(this->ui.treeWidget, &QTreeWidget::currentItemChanged, this, &MainWindow::treeItemChanged);
    connect(this->ui.treeWidget, &QTreeWidget::customContextMenuRequested, this, &MainWindow::showTreeContextMenu);
    connect(this->ui.treeWidget, &QTreeWidget::itemDoubleClicked, this, &MainWindow::treeDoubleClick);
}

MainWindow::~MainWindow() {
    this->db->closeDB();
    delete this->db;
    delete this->pixitem;
    delete this->scene;
    delete this->tree_status;
    delete this->img_status;
    delete this->scale_slider;
    delete this->action_scale_slider;
    delete this->settings_view_group;
    delete this->zoom_slider;
    delete this->action_zoom_slider;
    delete this->search_timer;
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
        QStringList db_filepaths = this->db->selectAllFilepaths();
        if (!db_filepaths.contains(file_path, Qt::CaseInsensitive)) {
            QJsonObject json_obj = Utils::getJsonFromZip(file_path, "info.json");
            QMap json_map = Utils::getMapFromJson(json_obj);
            if (!json_map.isEmpty()) {
                if (this->db->insert(json_map)) {
                    this->populateTree();
                    QMessageBox::information(this, "Info", QString("Added %1 to database").arg(json_map["title"]));
                } else {
                    QMessageBox::warning(this, "Warning", "Couldn't add to database");
                }
            } else {
                QMessageBox::warning(this, "Warning", "No json found in archive");
            }
        } else {
            QMessageBox::information(this, "Info", "Archive already in database");
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
    QStringList db_filepaths = this->db->selectAllFilepaths();
    int total_toadd = 0;
    
    QProgressDialog progress("Adding files to DB", nullptr, 0, zip_files.length() - 1, this);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    for (int i = 0; i < zip_files.length(); i++) {
        if (!db_filepaths.contains(zip_files[i], Qt::CaseInsensitive)) {
            QJsonObject json_obj = Utils::getJsonFromZip(zip_files[i], "info.json");
            QMap json_map = Utils::getMapFromJson(json_obj);
            if (!json_map.isEmpty()) {
                data_list.append(json_map);
                Logging::logMessage(QString("[To add]: %1").arg(json_map["title"]));
                total_toadd++;
            } else {
                Logging::logMessage(QString("[No json]: %1").arg(zip_files[i]));
            }
        }

        progress.setValue(i);
        progress.setLabelText(QString("Working on files: [%1/%2]").arg(QString::number(i + 1), QString::number(zip_files.length())));
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }
    progress.hide();
    if (this->db->insert(data_list)) {
        this->populateTree();
        QMessageBox::information(this, "Info", QString("Added %1 archives to database").arg(QString::number(total_toadd)));
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
    
    this->db->setDBPath(db_file);
    if (this->db->openDB()) {
        this->unlockWindowItems();
        this->populateTree();
        QMessageBox::information(this, "Info", "Database loaded");
    } else {
        QMessageBox::warning(this, "Warning", "Couldn't load database");
    }
}

void MainWindow::triggered_action_unloadDB() {
    this->db->closeDB();
    this->clearTree();
    this->clearView();
    this->ui.lineEditSearch->setText("");
    this->resetTreeStatusMessage();
    this->lockWindowItems();
    this->loaded_archives_num = 0;
    this->filtered_archives_num = 0;
    QMessageBox::information(this, "Info", "Database unloaded");
}

void MainWindow::triggered_action_cleanDB() {
    QMessageBox::StandardButton ask_cleandb = QMessageBox::question(this, "Clean DB", QString("Are you sure you want to clean DB ?"), QMessageBox::Yes | QMessageBox::No);
    if (ask_cleandb == QMessageBox::No) {
        return;
    }
    
    QList<QMap<QString, QVariant>> db_select = this->db->selectAll();

    QMap<QString, QStringList> path_hash_map;

    for (auto it : db_select) {
        path_hash_map[it["file_path"].toString()].append(it["file_hash"].toString());
    }

    QStringList removable_hashes = Utils::getCleanDBEntries(path_hash_map);

    if (this->db->removeFromDB(removable_hashes)) {
        this->populateTree();
        QMessageBox::information(this, "Info", QString("Cleaned %1 entries from DB").arg(QString::number(removable_hashes.length())));
    } else {
        QMessageBox::warning(this, "Warning", "Couldn't clean DB");
    }
}

void MainWindow::triggered_action_cleanHashes() {
    QMessageBox::StandardButton ask_cleanhashes = QMessageBox::question(this, "Clean hashes", QString("Are you sure you want to clean hashes ?"), QMessageBox::Yes | QMessageBox::No);
    if (ask_cleanhashes == QMessageBox::No) {
        return;
    }

    QStringList hashes = this->db->selectAllHashes();
    QStringList removable_hashes = Utils::getCleanDBHashes(hashes);
    if (this->db->removeFromDB(removable_hashes)) {
        this->populateTree();
        QMessageBox::information(this, "Info", QString("Removed %1 duplicate hashes from DB").arg(QString::number(removable_hashes.length())));
    } else {
        QMessageBox::warning(this, "Warning", "Couldn't clean DB");
    }
}

void MainWindow::triggered_action_cleanPaths() {
    QMessageBox::StandardButton ask_cleanpaths = QMessageBox::question(this, "Clean paths", QString("Are you sure you want to clean paths ?"), QMessageBox::Yes | QMessageBox::No);
    if (ask_cleanpaths == QMessageBox::No) {
        return;
    }

    QList<QMap<QString, QVariant>> db_select = this->db->selectAll();

    QMap<QString, QStringList> path_hash_map;

    for (auto it : db_select) {
        path_hash_map[it["file_path"].toString()].append(it["file_hash"].toString());
    }

    QStringList removable_paths = Utils::getCleanDBPaths(path_hash_map);

    if (this->db->removeFromDB(removable_paths)) {
        this->populateTree();
        QMessageBox::information(this, "Info", QString("Removed %1 duplicate filepaths from DB").arg(QString::number(removable_paths.length())));
    } else {
        QMessageBox::warning(this, "Warning", "Couldn't clean DB");
    }
}

void MainWindow::triggered_action_checkDB() {
    QMessageBox::StandardButton ask_checkdb = QMessageBox::question(this, "Check DB", QString("Are you sure you want to check DB ?"), QMessageBox::Yes | QMessageBox::No);
    if (ask_checkdb == QMessageBox::No) {
        return;
    }
    
    QList<QMap<QString, QVariant>> db_select = this->db->selectAll();
    QMap<QString, QStringList> hash_path_map;

    QProgressDialog progress("Checking DB", nullptr, 0, db_select.length() - 1, this);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    for (int i = 0; i < db_select.length(); i++) {
        QString db_hash = db_select[i]["file_hash"].toString();
        QString disk_hash = Utils::getSHA1Hash(db_select[i]["file_path"].toString());
        if (disk_hash.isEmpty()) {
            Logging::logMessage(QString("[Not found]: %1").arg(db_select[i]["file_path"].toString()));
        } else {
            if (QString::compare(db_hash, disk_hash, Qt::CaseInsensitive) != 0) {
                Logging::logMessage(QString("[Hash mismatch]: %1").arg(db_select[i]["file_path"].toString()));
            }
        }
        progress.setValue(i);
        progress.setLabelText(QString("Working on files: [%1/%2]").arg(QString::number(i + 1), QString::number(db_select.length())));
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }
    progress.hide();
    QMessageBox::information(this, "Info", "Finished, check logs for more info");
}

void MainWindow::triggered_action_checkPaths() {
    QMessageBox::StandardButton ask_checkpaths = QMessageBox::question(this, "Check DB paths", QString("Are you sure you want to check DB paths ?"), QMessageBox::Yes | QMessageBox::No);
    if (ask_checkpaths == QMessageBox::No) {
        return;
    }

    QStringList db_paths = this->db->selectAllFilepaths();

    QProgressDialog progress("Checking DB paths", nullptr, 0, db_paths.length() - 1, this);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    for (int i = 0; i < db_paths.length(); i++) {
        if (!Utils::fileExists(db_paths[i])) {
            Logging::logMessage(QString("[Not found]: %1").arg(db_paths[i]));
        }
        progress.setValue(i);
        progress.setLabelText(QString("Working on files: [%1/%2]").arg(QString::number(i + 1), QString::number(db_paths.length())));
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }
    progress.hide();
    QMessageBox::information(this, "Info", "Finished, check logs for more info");
}

void MainWindow::triggered_action_scaleimage(bool checked) {
    this->ui.graphicsView->toggleScaleImage(checked);
}

void MainWindow::triggered_action_search_typing(bool checked) {
    if (checked) {
        this->search_timer->start(500);
    } else {
        this->search_timer->stop();
    }
}

void MainWindow::triggered_action_select_first_result(bool checked) {
    this->select_first_result = checked;
}

void MainWindow::triggered_search_timer() {
    QString new_search = this->ui.lineEditSearch->text();
    if (this->old_search != new_search) {
        this->searchTreeItems(new_search);
        this->old_search = new_search;
    }
}

void MainWindow::triggered_action_scalechanged(int value) {
    this->ui.graphicsView->setScaleValue(value);
}

void MainWindow::triggered_action_viewfit(QAction *action) {
    if (action == this->ui.actionFitInView) {
        this->ui.graphicsView->setViewFit(ImageOption::FitInView);
    } else if (action == this->ui.actionFitToWidth) {
        this->ui.graphicsView->setViewFit(ImageOption::FitToWidth);
    } else if (action == this->ui.actionFreeView) {
        this->ui.graphicsView->setViewFit(ImageOption::FreeView);
    }
}

void MainWindow::triggered_action_zoomchanged(int value) {
    this->ui.graphicsView->setZoomValue(value);
}

void MainWindow::triggered_action_showlogs() {
    Logging::showLoggingWindow();
}

void MainWindow::lockWindowItems() {
    this->ui.actionAddFile->setEnabled(false);
    this->ui.actionAddDir->setEnabled(false);
    this->ui.actionLoadDB->setEnabled(true);
    this->ui.actionUnloadDB->setEnabled(false);
    this->ui.actionCleanDB->setEnabled(false);
    this->ui.actionCleanHashes->setEnabled(false);
    this->ui.actionCleanPaths->setEnabled(false);
    this->ui.actionCheckDB->setEnabled(false);
    this->ui.actionCheckPaths->setEnabled(false);
    this->ui.lineEditSearch->setEnabled(false);
    this->ui.pushButtonSearch->setEnabled(false);
    this->ui.pushButtonRandom->setEnabled(false);
    this->ui.pushButtonRefresh->setEnabled(false);
}

void MainWindow::unlockWindowItems() {
    this->ui.actionAddFile->setEnabled(true);
    this->ui.actionAddDir->setEnabled(true);
    this->ui.actionLoadDB->setEnabled(false);
    this->ui.actionUnloadDB->setEnabled(true);
    this->ui.actionCleanDB->setEnabled(true);
    this->ui.actionCleanHashes->setEnabled(true);
    this->ui.actionCleanPaths->setEnabled(true);
    this->ui.actionCheckDB->setEnabled(true);
    this->ui.actionCheckPaths->setEnabled(true);
    this->ui.lineEditSearch->setEnabled(true);
    this->ui.pushButtonSearch->setEnabled(true);
    this->ui.pushButtonRandom->setEnabled(true);
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
    this->tree_status->setText(QString("Showing: [%1/%2]").arg(QString::number(this->filtered_archives_num), QString::number(this->loaded_archives_num)));
}

void MainWindow::setTreeStatusMessage(const QString file_path) {
    QFileInfo file(file_path);
    QLocale locale;
    QString file_size = "File not found";
    if (file.exists()) {
        file_size = locale.formattedDataSize(file.size(), 1, QLocale::DataSizeIecFormat);
    }
    this->tree_status->setText(QString("Showing: [%1/%2] | Filesize: [%3]").arg(QString::number(this->filtered_archives_num), QString::number(this->loaded_archives_num), file_size));
}

void MainWindow::populateTree() {
    QList<QMap<QString, QVariant>> list_variants = this->db->selectAll();

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
    this->loaded_archives_num = this->filtered_archives_num = this->ui.treeWidget->topLevelItemCount();
    this->setTreeStatusMessage();
}

QTreeWidgetItem *MainWindow::getFirstVisibleItem() {
    QTreeWidgetItemIterator tree_it(this->ui.treeWidget);
    while (*tree_it) {
        if (!(*tree_it)->isHidden()) {
            return (*tree_it);
        }
        tree_it++;
    }
    return nullptr;
}

bool MainWindow::removeTreeItem(QTreeWidgetItem *item) {
    int index = this->ui.treeWidget->indexOfTopLevelItem(item);
    if (index != -1) {
        if (this->ui.treeWidget->takeTopLevelItem(index) != nullptr) {
            return true;
        }
    }
    return false;
}

void MainWindow::searchTreeItems(const QString search_str) {
    QStringList hash_list = this->db->selectTags("*" + search_str + "*");
    this->filtered_archives_num = 0;

    QTreeWidgetItemIterator tree_it(this->ui.treeWidget);
    while (*tree_it) {
        if (Utils::isNullOrEmpty(search_str)) {
            (*tree_it)->setHidden(false);
        } else {
            QString tree_item_hash = (*tree_it)->data(0, MyDataRoles::FileHash).toString();
            if (hash_list.contains(tree_item_hash, Qt::CaseSensitive)) {
                (*tree_it)->setHidden(false);
                this->filtered_archives_num++;
            } else {
                (*tree_it)->setHidden(true);
            }
        }
        tree_it++;
    }

    if (this->select_first_result) {
        this->ui.treeWidget->setCurrentItem(this->getFirstVisibleItem());
    }
}

void MainWindow::loadAllImages(const QString item_path, const QString title) {
    QByteArrayList images_list = Utils::getImagesFromZip(item_path, this);
    
    if (images_list.isEmpty()) {
        return;
    }

    QPixmap img;
    if (img.loadFromData(images_list[0])) {
        this->pixitem->setPixmap(img);
        this->pixitem->setData(MyDataRoles::FilePath, QVariant::fromValue(item_path));
        this->pixitem->setData(MyDataRoles::Title, QVariant::fromValue(title));
        this->ui.graphicsView->loadImages(images_list);
    }
}

void MainWindow::loadFIrstImage(const QString file_path, const QString title) {
    QByteArray zip_image = Utils::getFirstImageFromZip(file_path);
    
    if (Utils::isNullOrEmpty(zip_image)) {
        return;
    }

    QPixmap img;
    if (img.loadFromData(zip_image)) {
        this->pixitem->setPixmap(img);
        this->pixitem->setData(MyDataRoles::FilePath, QVariant::fromValue(file_path));
        this->pixitem->setData(MyDataRoles::Title, QVariant::fromValue(title));
        this->ui.graphicsView->loadImages(zip_image);
    }
}

void MainWindow::treeItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous) {
    // (void)previous;
    // Q_UNUSED(previous);
    
    if (current == nullptr) {
        if (previous == nullptr) {
            this->setTreeStatusMessage();
            return;
        }
        QString item_path = previous->data(0, MyDataRoles::FilePath).toString();
        this->setTreeStatusMessage(item_path);
        return;
    }

    this->clearView();
    
    QString item_path = current->data(0, MyDataRoles::FilePath).toString();
    QString title = current->data(0, MyDataRoles::Title).toString();
    this->setTreeStatusMessage(item_path);
    this->loadFIrstImage(item_path, title);
}

void MainWindow::showTreeContextMenu(const QPoint &pos) {
    QModelIndex index = this->ui.treeWidget->indexAt(pos);
    if (!index.isValid())
        return;
    
    QTreeWidgetItem *item = this->ui.treeWidget->itemAt(pos);
    QString title = item->data(0, MyDataRoles::Title).toString();
    QString item_filehash = item->data(0, MyDataRoles::FileHash).toString();
    QString item_filepath = item->data(0, MyDataRoles::FilePath).toString();
    QString item_filename = item->text(0);
    QString item_tags = item->data(0, MyDataRoles::Tags).toString();

    QMenu menu(this);
    QAction *load_all_images = new QAction("Load all images", &menu);
    QAction *show_zip_info = new QAction("Show zip info", &menu);
    QAction *copy_title = new QAction("Copy title", &menu);
    QAction *copy_filepath = new QAction("Copy path", &menu);
    QAction *copy_tags = new QAction("Copy tags", &menu);
    QAction *copy_hash = new QAction("Copy hash", &menu);
    QAction *check_hash = new QAction("Check hash", &menu);
    QAction *remove_db = new QAction("Remove from DB", &menu);
    menu.addAction(load_all_images);
    menu.addSeparator();
    menu.addAction(show_zip_info);
    menu.addSeparator();
    menu.addAction(copy_title);
    menu.addAction(copy_filepath);
    menu.addAction(copy_tags);
    menu.addAction(copy_hash);
    menu.addSeparator();
    menu.addAction(check_hash);
    menu.addSeparator();
    menu.addAction(remove_db);
    QAction *clicked_action = menu.exec(this->ui.treeWidget->viewport()->mapToGlobal(pos));

    if (!clicked_action) {
        return;
    }

    if (clicked_action == load_all_images) {
        this->loadAllImages(item_filepath, title);
    } else if (clicked_action == show_zip_info) {
        QString info = Utils::getArchiveInfo(item_filepath, "info.json");
        QMessageBox::information(this, "Zip archive info", info);
    } else if (clicked_action == copy_title) {
        QApplication::clipboard()->clear();
        QApplication::clipboard()->setText(item_filename, QClipboard::Clipboard);
    } else if (clicked_action == copy_filepath) {
        QApplication::clipboard()->clear();
        QApplication::clipboard()->setText(item_filepath, QClipboard::Clipboard);
    } else if (clicked_action == copy_tags) {
        QApplication::clipboard()->clear();
        QApplication::clipboard()->setText(item_tags, QClipboard::Clipboard);
    } else if (clicked_action == copy_hash) {
        QApplication::clipboard()->clear();
        QApplication::clipboard()->setText(item_filehash, QClipboard::Clipboard);
    } else if (clicked_action == check_hash) {
        QString disk_hash = Utils::getSHA1Hash(item_filepath);
        if (QString::compare(item_filehash, disk_hash, Qt::CaseInsensitive) == 0) {
            QMessageBox::information(this, "Info", "Hashes are the same");
        } else {
            QMessageBox::information(this, "Info", "Hashes don't match");
        }
    } else if (clicked_action == remove_db) {
        QMessageBox::StandardButton remove_reply = QMessageBox::question(this, "Remove from DB", QString("Remove %1 from DB").arg(title), QMessageBox::Yes | QMessageBox::No);
        if (remove_reply == QMessageBox::Yes) {
            if (this->db->removeFromDB(item_filehash)) {
                if (this->removeTreeItem(item)) {
                    QMessageBox::information(this, "Info", QString("Removed %1 from DB").arg(title));
                } else {
                    QMessageBox::warning(this, "Warning", "Couldn't remove item from tree");
                }
            } else {
                QMessageBox::warning(this, "Warning", "Couldn't remove from DB");
            }
        }
    }
}

void MainWindow::treeDoubleClick(QTreeWidgetItem *item, int column) {
    if (item == nullptr) {
        return;
    }
    
    QString item_filepath = item->data(column, MyDataRoles::FilePath).toString();
    QString title = item->data(0, MyDataRoles::Title).toString();
    
    this->loadAllImages(item_filepath, title);
}

void MainWindow::randomButtonClicked() {
    QList<QTreeWidgetItem *> visible_items;

    QTreeWidgetItemIterator tree_it(this->ui.treeWidget);
    while (*tree_it) {
        if (!(*tree_it)->isHidden()) {
            visible_items.append(*tree_it);
        }
        tree_it++;
    }

    if (visible_items.length() > 0) {
        this->ui.treeWidget->setCurrentItem(visible_items[QRandomGenerator::global()->bounded(0, visible_items.length())]);
    }
}

void MainWindow::refreshButtonClicked() {
    QTreeWidgetItemIterator tree_it(this->ui.treeWidget);
    while (*tree_it) {
        (*tree_it)->setHidden(false);
        tree_it++;
    }
    
    this->ui.lineEditSearch->setText("");
    
    if (this->ui.treeWidget->topLevelItemCount() > 0) {
        this->filtered_archives_num = this->loaded_archives_num;
        if (this->select_first_result) {
            this->ui.treeWidget->setCurrentItem(this->ui.treeWidget->topLevelItem(0));
        }
    }
}
