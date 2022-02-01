//
// Created by jeditux on 20.10.2021.
//

#pragma once

#include <functional>

namespace Core {
    enum class EventType {
        resize,
        mouseMove,
        mouseButtonClick,
        mouseButtonRelease,
        eventCount
    };

    enum class MouseButton {
        left,
        right
    };

    struct BaseEvent {
        virtual EventType getType() = 0;
        virtual ~BaseEvent() = default;
    };

    struct ResizeEvent : public BaseEvent {
        ResizeEvent(unsigned int newWidth, unsigned int newHeight)
            : BaseEvent()
            , width(newWidth)
            , height(newHeight)
        {}

        EventType getType() override {
            return EventType::resize;
        }

        unsigned int width;
        unsigned int height;

        const static EventType type = EventType::resize;
    };

    struct MouseMoveEvent : public BaseEvent {
        MouseMoveEvent(unsigned int newX, unsigned int newY)
                : BaseEvent()
                , x(newX)
                , y(newY)
        {}

        EventType getType() override {
            return EventType::mouseMove;
        }

        unsigned int x;
        unsigned int y;

        const static EventType type = EventType::mouseMove;
    };

    struct MouseButtonPressEvent : public BaseEvent {
        MouseButtonPressEvent(unsigned int newX, unsigned int newY, MouseButton newButton)
                : BaseEvent()
                , x(newX)
                , y(newY)
                , button(newButton)
        {}

        EventType getType() override {
            return EventType::mouseButtonClick;
        }

        unsigned int x;
        unsigned int y;
        MouseButton button;

        const static EventType type = EventType::mouseButtonClick;
    };

    struct MouseButtonReleaseEvent : public BaseEvent {
        MouseButtonReleaseEvent(unsigned int newX, unsigned int newY, MouseButton newButton)
                : BaseEvent()
                , x(newX)
                , y(newY)
                , button(newButton)
        {}

        EventType getType() override {
            return EventType::mouseButtonRelease;
        }

        unsigned int x;
        unsigned int y;
        MouseButton button;

        const static EventType type = EventType::mouseButtonRelease;
    };

    class EventDispatcher {
    public:
        template <typename Event>
        void addEventHandler(std::function<void(Event& event)> callback) {
            auto baseCallback = [func = std::move(callback)](BaseEvent& e) {
                if (e.getType() == Event::type) {
                    func(static_cast<Event&>(e));
                }
            };
            m_eventHandlers[static_cast<size_t>(Event::type)] = std::move(baseCallback);
        }

        void dispatch(BaseEvent& event) {
            if (m_eventHandlers[static_cast<size_t>(event.getType())] != nullptr) {
                m_eventHandlers[static_cast<size_t>(event.getType())](event);
            }
        }

    private:
        std::array<std::function<void(BaseEvent&)>, static_cast<size_t>(EventType::eventCount)> m_eventHandlers;
    };
}
