//
// Created by keanu on 8/2/2024.
//

#ifndef HIVE_CLEANINGEVENT_H
#define HIVE_CLEANINGEVENT_H

#include <memory>

namespace CoreLogic::EventManagement
{
    class CleaningEvent
    {
    public:
        CleaningEvent();
        ~CleaningEvent() = default;
        void update();
    protected:
        /**
         *  @Pseudo_Code: Rubble not yet existing
         */
        std::shared_ptr<Rubble> po_rubble_;
    };
}

#endif //HIVE_CLEANINGEVENT_H
