#include "viewport_control.h"

#include "debug.h"
#include "scene.h"
#include "shape.h"
#include "utils.h"
#include "viewport.h"
#include "viewport_mouse_event.h"

ViewportControl::ViewportControl(Viewport* viewport) : viewport(viewport)
{
    viewport->addListener(this);
}

ViewportControl::~ViewportControl()
{
    viewport->removeListener(this);
}

void ViewportControl::mousePress(const ViewportMouseEvent& event)
{
    if (event.getButtons() == Qt::LeftButton && event.getModifiers() == Qt::ControlModifier)
    {
        moveRect = viewport->getScene()->getRoot()->create<Shape>("moveRect",
        {
            {"pen", QPen(Qt::green, 2)},
            {"brush", QBrush(QColor("#aa00aa00"))},
            {"rect", QRectF()},
            {"type", Shape::Rectangle}
        });
        pressPos = event.getScenePos();
    }
    else if (event.getButtons() == Qt::LeftButton)
    {
        moveRect = viewport->getScene()->getRoot()->create<Shape>("moveRect",
        {
            {"pen", QPen(Qt::green, 2)},
            {"brush", QBrush(QColor("#aa00aa00"))},
            {"rect", QRectF()},
            {"type", Shape::Rectangle}
        });
        pressPos = event.getScenePos();
    }
    else if (event.getButtons() == Qt::RightButton)
    {
        pressPos = event.getViewportPos();
        pressRect = viewport->getViewRect();
    }
    else if (event.getButtons() == Qt::MiddleButton)
    {
        const QRectF viewRect = viewport->getViewRect();
        viewport->setViewRectAnimated(makeRect(viewRect.center(), viewport->width(), viewport->height()), viewDuration);
    }
    viewport->update();
}

void ViewportControl::mouseMove(const ViewportMouseEvent& event)
{
    if (event.getButtons() == Qt::LeftButton && event.getModifiers() == Qt::ControlModifier)
    {
        moveRect->setRect({pressPos, event.getScenePos()});
    }
    else if (event.getButtons() == Qt::RightButton)
    {
        const QPointF diff = (pressPos - event.getViewportPos()) / viewport->getScale();
        QTransform transform;
        transform.translate(diff.x(), diff.y());
        viewport->setViewRect(transform.mapRect(pressRect));
    }

    viewport->update();
}

void ViewportControl::mouseRelease(const ViewportMouseEvent& event)
{
    Q_UNUSED(event);
    if (event.getButton() == Qt::LeftButton && event.getModifiers() == Qt::ControlModifier)
    {
        QRectF rect = moveRect->getRect();
        if (std::max(rect.width(), rect.height()) < 10)
        {
            rect = viewport->getViewRect();
            rect = makeRect(pressPos, rect.width(), rect.height());
        }
        viewport->pushLocation();
        viewport->setViewRectAnimated(rect, viewDuration);
        delete moveRect;
        moveRect = nullptr;
    }
    else if (event.getButton() == Qt::RightButton)
    {
        if (pressPos == event.getViewportPos())
        {
            viewport->popLocation(viewDuration);
        }
    }
    viewport->update();
}

void ViewportControl::keyPress(const int key, const int modifiers)
{
    Q_UNUSED(modifiers);
    keys.insert(key);

    if (key == Qt::Key_1)
    {
        viewport->setViewRectAnimated(QRectF(100, 150, 320, 320), viewDuration);
    }
    if (key == Qt::Key_2)
    {
        viewport->setViewRectAnimated(QRectF(500, 450, 600, 600), viewDuration);
    }
    if (key == Qt::Key_3)
    {
        viewport->setViewRectAnimated(QRectF(900, 600, 400, 400), viewDuration);
    }
    if (key == Qt::Key_4)
    {
        viewport->setViewRectAnimated(QRectF(1200, 500, 350, 350), viewDuration);
    }
}

void ViewportControl::keyRelease(const int key, const int modifiers)
{
    Q_UNUSED(modifiers);
    keys.remove(key);
}

void ViewportControl::wheel(const QPointF& scenePos, const int delta)
{
    const double factor = delta > 0 ? 0.8 : 1.2;
    viewport->zoomAnimated(factor, scenePos, zoomDuration);
}

void ViewportControl::update(const double time)
{
    QPointF vec;
    if (keys.contains(Qt::Key_W))
        vec.setY(-1);
    else if (keys.contains(Qt::Key_S))
        vec.setY(1);
    if (keys.contains(Qt::Key_A))
        vec.setX(-1);
    else if (keys.contains(Qt::Key_D))
        vec.setX(1);

    if (!vec.isNull())
    {
        DEBUG_LOCATION();
        const QPointF offset = vec * speed / viewport->getScale() * time;
        viewport->moveBy(offset);
    }
}
