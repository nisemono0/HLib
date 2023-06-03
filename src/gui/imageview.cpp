#include "gui/imageview.h"
#include "utils/utilfuncs.h"

#include <QGraphicsItem>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QToolTip>
#include <QCursor>
#include <QScrollBar>
#include <QInputDialog>
#include <QMessageBox>

ImageView::ImageView(QWidget *parent) : QGraphicsView(parent) {
    this->current_image = -1;
    this->total_images = -1;
    this->has_images = false;
    this->image_item = nullptr;
    this->scale_images = true;
    this->scale_value = 1.0;
    this->zoom_value = 1.1;
    this->is_loaded_images = false;
    this->current_pixmap = QPixmap();
    this->current_image_size = QSize();
    this->image_fit_option = ImageOption::FitInView;
    this->cursor_next = QCursor(QPixmap(":mouse/mouse-image-next"), -1, -1);
    this->cursor_prev = QCursor(QPixmap(":mouse/mouse-image-prev"), -1, -1);
}

void ImageView::loadImages(QByteArrayList images) {
    this->images.clear();
    this->images = images;
    this->has_images = true;
    this->current_image = 0;
    this->total_images = images.count();
    this->image_item = (QGraphicsPixmapItem *)this->scene()->items().at(0);
    this->current_pixmap.loadFromData(this->images[this->current_image]);
    this->current_image_size = this->current_pixmap.size();
    this->is_loaded_images = true;
    this->scaleAndFit();
    this->centerOn(0, 0);
    this->setMouseTracking(true);
    this->showStatus();
}

void ImageView::loadImages(QByteArray image) {
    this->images = { image };
    this->has_images = true;
    this->current_image = 0;
    this->total_images = images.count();
    this->image_item = (QGraphicsPixmapItem *)this->scene()->items().at(0);
    this->current_pixmap = this->image_item->pixmap();
    this->current_image_size = this->current_pixmap.size();
    this->scaleAndFit();
    this->centerOn(0, 0);
    this->setMouseTracking(true);
    this->showStatus();
}

void ImageView::addStatusLabel(QLabel *img_status) {
    this->img_status = img_status;
}

QImage ImageView::getCurrentImage() {
    if (this->has_images) {
        QImage image;
        image.loadFromData(this->images[this->current_image]);
        return image;
    }
    return QImage();
}

void ImageView::setCurrentImage(const SetImage::SetImage option) {
    if (option == SetImage::NextImage && (0 <= this->current_image + 1 && this->current_image + 1 < this->total_images)) {
        this->current_image++;
    } else if (option == SetImage::PrevImage && (0 <= this->current_image - 1 && this->current_image - 1 < this->total_images)) {
        this->current_image--;
    }

    if (this->has_images && (0 <= current_image && current_image < this->total_images)) {
        this->current_pixmap.loadFromData(this->images[this->current_image]);
        this->current_image_size = this->current_pixmap.size();
        this->scaleAndFit();
        this->showStatus();
        this->centerOn(0, 0);
    }
}

void ImageView::setCurrentImage(const int image_number) {
    if (this->has_images) {
        if (image_number <= 0) {
            this->current_image = 0;
        } else if (image_number < this->total_images) {
            this->current_image = image_number;
        }
        this->current_pixmap.loadFromData(this->images[this->current_image]);
        this->current_image_size = this->current_pixmap.size();
        this->scaleAndFit();
        this->showStatus();
        this->centerOn(0, 0);
    }
}

void ImageView::showStatus() {
    this->img_status->setHidden(false);
    this->img_status->setText(QString("Image: [%1/%2] (%3x%4)").arg(
        QString::number(this->current_image + 1), QString::number(this->total_images),
        QString::number(this->current_image_size.width()), QString::number(this->current_image_size.height())
    ));
}

void ImageView::hideStatus() {
    this->img_status->hide();
}

void ImageView::fitImage() {
    if (this->has_images) {
        this->setSceneRect(this->image_item->boundingRect());
        if (this->image_fit_option == ImageOption::FitInView) {
            this->fitInView(this->image_item->boundingRect(), Qt::KeepAspectRatio);
        } else if (this->image_fit_option == ImageOption::FitToWidth) {
            int scroll_x = this->horizontalScrollBar()->value();
            int scroll_y = this->verticalScrollBar()->value();
            this->fitInView(this->scene()->itemsBoundingRect(), Qt::KeepAspectRatioByExpanding);
            if (this->sceneRect().width() >= this->mapToScene(this->viewport()->rect()).boundingRect().width()) {
                this->fitInView(this->image_item->boundingRect(), Qt::KeepAspectRatio);
            }
            this->horizontalScrollBar()->setValue(scroll_x);
            this->verticalScrollBar()->setValue(scroll_y);
        }
    }
}

void ImageView::scaleDisplayImage() {
    if (this->has_images) {
        if (this->scale_images) {
            this->image_item->setPixmap(this->current_pixmap.scaled(QWidget::window()->size() * this->scale_value, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            this->image_item->setPixmap(this->current_pixmap);
        }
    }
}

void ImageView::scaleAndFit() {
    this->scaleDisplayImage();
    this->fitImage();
}

void ImageView::toggleScaleImage(bool checked) {
    this->scale_images = checked;
    this->scaleAndFit();
}

void ImageView::setScaleValue(int value) {
    this->scale_value = 1.0 + (value / 10.0);
    QToolTip::showText(QCursor::pos(), QString("Scale: %1").arg(this->scale_value), nullptr);
    this->scaleAndFit();
}

void ImageView::setZoomValue(int value) {
    this->zoom_value = 1.0 + (value / 10.0);
    QToolTip::showText(QCursor::pos(), QString("Zoom: %1").arg(this->zoom_value), nullptr);
}

void ImageView::setViewFit(const ImageOption::ImageOption option) {
    this->image_fit_option = option;
    this->scaleAndFit();
}

void ImageView::clearImageView() {
    this->images = QByteArrayList();
    this->current_image = -1;
    this->total_images = -1;
    this->has_images = false;
    this->is_loaded_images = false;
    this->current_pixmap = QPixmap();
    this->setCursor(Qt::ArrowCursor);
    this->setMouseTracking(false);
    this->hideStatus();
}

void ImageView::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    this->scaleAndFit();
}

void ImageView::mousePressEvent(QMouseEvent *event) {
    if (this->has_images && (this->image_fit_option == ImageOption::FitToWidth || this->image_fit_option == ImageOption::FreeView)) {
        if (event->button() == Qt::MiddleButton) {
            this->setDragMode(QGraphicsView::ScrollHandDrag);
            QMouseEvent fake(event->type(), event->pos(), Qt::LeftButton, Qt::LeftButton, event->modifiers());
            QGraphicsView::mousePressEvent(&fake);
        } else {
            QGraphicsView::mousePressEvent(event);
        }
    }
}

void ImageView::mouseReleaseEvent(QMouseEvent *event) {
    this->setDragMode(QGraphicsView::NoDrag);
    QGraphicsView::mouseReleaseEvent(event);
    if (this->has_images && this->total_images > 1) {
        if (event->button() == Qt::LeftButton) {
            int mouse_x = event->localPos().x();
            int half_point = this->size().width() / 2;
            if (mouse_x > half_point) {
                this->setCurrentImage(SetImage::NextImage);
            } else {
                this->setCurrentImage(SetImage::PrevImage);
            }
        }
    }
}

void ImageView::mouseMoveEvent(QMouseEvent *event) {
    QGraphicsView::mouseMoveEvent(event);
    if (this->has_images && this->total_images > 1) {
        int mouse_x = event->localPos().x();
        int half_point = this->size().width() / 2;
        if (mouse_x > half_point) {
            this->setCursor(this->cursor_next);
        } else {
            this->setCursor(this->cursor_prev);
        }
    } else {
        this->setCursor(Qt::ArrowCursor);
    }
}

void ImageView::mouseDoubleClickEvent(QMouseEvent *event) {
    QGraphicsView::mouseDoubleClickEvent(event);
    if (this->has_images && !this->is_loaded_images && event->button() == Qt::LeftButton) {
        QString file_path = this->image_item->data(MyDataRoles::FilePath).toString();

        QByteArrayList images_list = Utils::getImagesFromZip(file_path, this);
        if (images_list.isEmpty()) {
            return;
        }
        this->image_item->setData(MyDataRoles::FilePath, QVariant::fromValue(file_path));
        this->loadImages(images_list);
    }
}

void ImageView::contextMenuEvent(QContextMenuEvent *event) {
    QGraphicsView::contextMenuEvent(event);
    if (this->has_images) {
        QMenu menu(this);
        QString file_path = this->image_item->data(MyDataRoles::FilePath).toString();
        QString title = this->image_item->data(MyDataRoles::Title).toString();

        QAction *load_all_images = new QAction("Load all images", &menu);
        QAction *show_zip_info = new QAction("Show zip info", &menu);
        QAction *copy_current_image = new QAction("Copy image", &menu);
        QAction *copy_title = new QAction("Copy title", &menu);
        QAction *jump_to = new QAction("Jump to image", &menu);
        menu.addAction(load_all_images);
        menu.addSeparator();
        menu.addAction(show_zip_info);
        menu.addSeparator();
        menu.addAction(copy_current_image);
        menu.addAction(copy_title);
        menu.addSeparator();
        menu.addAction(jump_to);

        QAction *clicked_action = menu.exec(event->globalPos());

        if (!clicked_action) {
            return;
        }

        if (clicked_action == load_all_images) {
            QByteArrayList images_list = Utils::getImagesFromZip(file_path, this);
            if (images_list.isEmpty()) {
                return;
            }
            this->image_item->setData(MyDataRoles::FilePath, QVariant::fromValue(file_path));
            this->loadImages(images_list);
        } else if (clicked_action == show_zip_info) {
            QString info = Utils::getArchiveInfo(file_path, "info.json");
            QMessageBox::information(this, "Zip archive info", info);
        } else if (clicked_action == copy_current_image) {
            QApplication::clipboard()->clear();
            QApplication::clipboard()->setImage(this->getCurrentImage());
        } else if (clicked_action == copy_title) {
            QApplication::clipboard()->clear();
            QApplication::clipboard()->setText(title);
        } else if (clicked_action == jump_to) {
            int jump_image = QInputDialog::getInt(this, "Jump to image",
                QString("Jump to image (%1, %2)").arg(QString::number(1), QString::number(this->total_images)),
                1, 1, this->total_images, 1) - 1;
            this->setCurrentImage(jump_image);
        }
    }
}

void ImageView::wheelEvent(QWheelEvent *event) {
    if (this->has_images && this->image_fit_option == ImageOption::FreeView) {
        this->setTransformationAnchor(QGraphicsView::NoAnchor);
        this->setResizeAnchor(QGraphicsView::NoAnchor);
        if (event->angleDelta().y() > 0) {
            this->scale(this->zoom_value, this->zoom_value);
            this->centerOn(this->mapToScene(event->position().toPoint()));
        } else if (event->angleDelta().y() < 0) {
            this->scale(1.0 / this->zoom_value, 1.0 / this->zoom_value);
        }
    } else {
        QGraphicsView::wheelEvent(event);
    }
}