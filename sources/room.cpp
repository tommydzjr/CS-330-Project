#include "room.hpp"

namespace websocket {
    namespace applications {
        namespace chat {

            void room::join(participant_ptr participant)
            {
                participants_.insert(participant);

                update_participants();

                std::for_each(recent_msgs_.begin(), recent_msgs_.end(),
                    boost::bind(&participant::deliver, participant, _1));
            }

            void room::leave(participant_ptr participant)
            {
                participants_.erase(participant);

                update_participants();
            }

            void room::deliver(const dataframe& msg, participant_ptr source)
            {
                std::string header = "log:" + source->get_id() + ": ";

                dataframe frm;
                std::copy(header.begin(), header.end(), std::back_inserter(frm.payload));
                std::copy(msg.payload.begin(), msg.payload.end(), std::back_inserter(frm.payload));

                deliver(frm);
            }

            void room::deliver(const dataframe& msg)
            {
                recent_msgs_.push_back(msg);
                while (recent_msgs_.size() > max_recent_msgs)
                    recent_msgs_.pop_front();

                std::for_each(participants_.begin(), participants_.end(),
                    boost::bind(&participant::deliver, _1, boost::ref(msg)));
            }

            void room::update_participants()
            {
                std::string header = "connected:" + boost::lexical_cast<std::string>(participants_.size());

                dataframe frm;
                std::copy(header.begin(), header.end(), std::back_inserter(frm.payload));

                std::for_each(participants_.begin(), participants_.end(),
                    boost::bind(&participant::deliver, _1, boost::ref(frm)));
            }

        } // chat
    } // namespace applications
} // namespace websocket