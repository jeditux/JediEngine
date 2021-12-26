//
// Created by jeditux on 20.10.2021.
//

#pragma once

#include <functional>

namespace Core {
    enum class EventType {
        resizeEvent,
        eventCount
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
            return EventType::resizeEvent;
        }

        unsigned int width;
        unsigned int height;

        const static EventType type = EventType::resizeEvent;
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
