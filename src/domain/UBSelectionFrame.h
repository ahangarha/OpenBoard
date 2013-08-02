#ifndef UBSELECTIONFRAME_H
#define UBSELECTIONFRAME_H

#include <QGraphicsRectItem>
#include <QtGui>
#include <core/UB.h>

#include "domain/UBGraphicsScene.h"

class DelegateButton;
class UBGraphicsItemDelegate;

class UBSelectionFrame : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    enum {om_idle, om_moving, om_rotating} mOperationMode;
    enum { Type = UBGraphicsItemType::SelectionFrameType };

    UBSelectionFrame();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;

    void setLocalBrush(const QBrush &pBrush) {mLocalBrush = pBrush;}
    QBrush localBrush() const {return mLocalBrush;}
//    void setEnclosedItems(const QList<UBGraphicsItemDelegate*> pEncItems) {mEnclosedtems = pEncItems; updateRect();}
    void setEnclosedItems(const QList<QGraphicsItem*> pGraphicsItems);
    void updateRect();
    void updateScale();
    bool isEmpty() const {return this->rect().isEmpty();}
    virtual int type() const {return Type;}

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private slots:
    void setAntiScaleRatio(qreal pAntiscaleRatio) {mAntiscaleRatio = pAntiscaleRatio;}
    void onZoomChanged(qreal pZoom);
    void remove();
    void duplicate();
    void increaseZlevelUp();
    void increaseZlevelTop();
    void increaseZlevelDown();
    void increaseZlevelBottom();

private:
    void addSelectionUndo(QList<QGraphicsItem*> items, UBZLayerController::moveDestination dest);
    void translateItem(QGraphicsItem *item, const QPointF &translatePoint);
    void placeButtons();
    void placeExceptionButton(DelegateButton *pButton, QTransform pTransform);
    void clearButtons();
    inline int adjThickness() const {return mThickness * mAntiscaleRatio;}
    inline UBGraphicsScene* ubscene();
    void setCursorFromAngle(QString angle);

    QList<QGraphicsItem*> sortedByZ(const QList<QGraphicsItem*> &pItems);
    QList<DelegateButton*> buttonsForFlags(UBGraphicsFlags fls);


private:
    int mThickness;
    qreal mAntiscaleRatio;
    QList<UBGraphicsItemDelegate*> mEnclosedtems;
    QBrush mLocalBrush;

    QPointF mPressedPos;
    QPointF mLastMovedPos;
    QPointF mLastTranslateOffset;
    qreal mRotationAngle;

    QList<DelegateButton*> mButtons;

    DelegateButton *mDeleteButton;
    DelegateButton *mDuplicateButton;
    DelegateButton *mZOrderUpButton;
    DelegateButton *mZOrderDownButton;

    DelegateButton *mRotateButton;

};

#endif // UBSELECTIONFRAME_H
