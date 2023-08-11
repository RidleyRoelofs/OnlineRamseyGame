class CustomView : public QGraphicsView {
public:
    CustomView(QGraphicsScene* scene, QGraphicsPixmapItem* playerImage, const std::vector<QGraphicsEllipseItem*>& nodes, QWidget* parent = nullptr)
        : QGraphicsView(scene, parent), playerImage_(playerImage), nodes_(nodes) {}

protected:
    void resizeEvent(QResizeEvent* event) override {
        QGraphicsView::resizeEvent(event);
        int viewWidth = viewport()->width();
        QPointF topRightScene = mapToScene(viewWidth - playerImage_->pixmap().width(), 0);
        playerImage_->setPos(topRightScene);

        QPointF center = viewport()->rect().center();
        const int node_radius = 120;
        const int label_offset = 20;
        for (int i = 0; i < nodes_.size(); i++) {
            double x = center.x() + node_radius * cos(i * M_PI / 3.0);
            double y = center.y() + node_radius * sin(i * M_PI / 3.0);
            nodes_[i]->setPos(x, y);
        }
    }

private:
    QGraphicsPixmapItem* playerImage_;
    std::vector<QGraphicsEllipseItem*> nodes_;
};
