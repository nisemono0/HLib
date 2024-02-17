#pragma once
#include "utils/utildefs.h"

#include <QGraphicsView>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QStatusBar>
#include <QLabel>

class ImageView : public QGraphicsView {
    Q_OBJECT
public:
    ImageView(QWidget *parent = nullptr);
    void clearImageView();
    void loadImages(QByteArrayList images);
    void loadImages(QByteArray image);
    void addStatusLabel(QLabel *img_status);
    void setCurrentImage(const SetImage::SetImage option);
    void setCurrentImage(const int image_number);
    void toggleScaleImage(bool checked);
    void setScaleValue(int value);
    void setViewFit(const ImageOption::ImageOption option);
private:
    QByteArrayList images;
    int current_image;
    int total_images;
    bool has_images;
    bool scale_images;
    float scale_value;
    float zoom_value;
    bool is_loaded_images;
    ImageOption::ImageOption image_fit_option;
    QGraphicsPixmapItem *image_item;
    QLabel *img_status;
    QImage getCurrentImage();
    QCursor cursor_next;
    QCursor cursor_prev;
    QPixmap current_pixmap;
    QSize current_image_size;
    void showStatus();
    void hideStatus();
    void fitImage();
    void scaleDisplayImage();
    void scaleAndFit();
protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    void wheelEvent(QWheelEvent *event);
};