#include "gui/imageview.h"
#include "utils/utilfuncs.h"

#include <QDebug>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QClipboard>

ImageView::ImageView(QWidget *parent): QGraphicsView(parent) {
    this->current_image = -1;
    this->total_images = -1;
    this->has_images = false;
    this->image_item = nullptr;
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
    this->setMouseTracking(true);
    this->fitImage();
    this->showStatus();
}

void ImageView::loadImages(QByteArray image) {
    this->images = { image };
    this->has_images = true;
    this->current_image = 0;
    this->total_images = images.count();
    this->image_item = (QGraphicsPixmapItem *)this->scene()->items().at(0);
    this->setMouseTracking(true);
    this->fitImage();
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

void ImageView::setCurrentImage(const SetImageOption::SetImageOption option) {
    if (option == SetImageOption::NextImage && (0 <= this->current_image + 1 && this->current_image + 1 < this->total_images)) {
        this->current_image++;
    } else if (option == SetImageOption::PrevImage && (0 <= this->current_image - 1 && this->current_image - 1 < this->total_images)) {
        this->current_image--;
    }

    if (this->has_images && (0 <= current_image && current_image < this->total_images)) {
        this->current_image = current_image;
        QPixmap image;
        image.loadFromData(this->images[current_image]);
        this->image_item->setPixmap(image);
        this->fitImage();
        this->showStatus();
    }    
}

void ImageView::showStatus() {
    this->img_status->setHidden(false);
    this->img_status->setText(QString("Displaying image: [%1/%2]").arg(QString::number(this->current_image + 1), QString::number(this->total_images)));
}

void ImageView::hideStatus() {
    this->img_status->hide();
}

void ImageView::fitImage() {
    if (this->has_images) {
        this->setSceneRect(this->image_item->boundingRect());
        this->fitInView(this->image_item, Qt::KeepAspectRatio);
    }
}

void ImageView::clearImageView() {
    this->images = QByteArrayList();
    this->current_image = -1;
    this->total_images = -1;
    this->has_images = false;
    this->setCursor(Qt::ArrowCursor);
    this->setMouseTracking(false);
    this->hideStatus();
}

void ImageView::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    if (this->has_images) {
        this->fitInView(this->image_item, Qt::KeepAspectRatio);
    }
}

void ImageView::mouseReleaseEvent(QMouseEvent *event) {
    QGraphicsView::mouseReleaseEvent(event);
    if (this->has_images) {
        if (event->button() == Qt::LeftButton) {
            int mouse_x = event->localPos().x();
            int half_point = this->size().width() / 2;
            if (mouse_x > half_point) {
                this->setCurrentImage(SetImageOption::NextImage);
            } else {
                this->setCurrentImage(SetImageOption::PrevImage);
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

void ImageView::contextMenuEvent(QContextMenuEvent *event) {
    QGraphicsView::contextMenuEvent(event);
    if (this->has_images) {
        QMenu menu(this);
        QString file_path = this->image_item->data(MyDataRoles::FilePath).toString();
        QString title = this->image_item->data(MyDataRoles::Title).toString();

        QAction *load_all_images = new QAction("Load all images", &menu);
        QAction *copy_current_image = new QAction("Copy image", &menu);
        QAction *copy_title = new QAction("Copy title", &menu);
        menu.addAction(load_all_images);
        menu.addAction(copy_current_image);
        menu.addSeparator();
        menu.addAction(copy_title);
        
        QAction *clicked_action = menu.exec(event->globalPos());

        if (!clicked_action) {
            return;
        }

        if (clicked_action == load_all_images) {
            QByteArrayList images_list = Utils::getImagesFromZip(file_path, this);
            if (images_list.isEmpty()) {
                return;
            }
            QPixmap img;
            if (img.loadFromData(images_list[0])) {
                this->image_item->setPixmap(img);
                this->image_item->setData(MyDataRoles::FilePath, QVariant::fromValue(file_path));
                this->loadImages(images_list);
            }
        } else if (clicked_action == copy_current_image) {
            QApplication::clipboard()->clear();
            QApplication::clipboard()->setImage(this->getCurrentImage());
        } else if (clicked_action == copy_title) {
            QApplication::clipboard()->clear();
            QApplication::clipboard()->setText(title);
        }
    }
}

void ImageView::wheelEvent(QWheelEvent *event) {
    QGraphicsView::wheelEvent(event);
    if (this->has_images) {
        if (event->angleDelta().y() < 0) {
            this->setCurrentImage(SetImageOption::NextImage);
        } else if (event->angleDelta().y() > 0) {
            this->setCurrentImage(SetImageOption::PrevImage);
        }
    }
}