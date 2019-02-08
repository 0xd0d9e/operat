#include "input_event.h"

#include <QEvent>
#include <QHash>


InputEvent::InputEvent(const int type)
    : Event(type)
{

}

bool InputEvent::isInputEvent() const
{
    return true;
}
