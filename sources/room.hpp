#ifndef WEBSOCKET_APPLICATIONS_CHAT_ROOM_HPP
#define WEBSOCKET_APPLICATIONS_CHAT_ROOM_HPP

#include <string>
#include <algorithm>
#include <deque>
#include <set>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include "dataframe.hpp"
#include "participant.hpp"

namespace websocket {
    namespace applications {
        namespace chat {

            typedef std::deque<dataframe> message_queue;

            /// The chat room class.
            class room
            {
            public:
                /// Join the room.
                void join(participant_ptr participant);

                /// Leave the room.
                void leave(participant_ptr participant);

                /// Deliver a chat message to all participant in the room.
                void deliver(const dataframe& msg, participant_ptr source);

            private:
                /// Deliver a message to all participant in the room.
                void deliver(const dataframe& msg);

                /// Update a number of connected participants. 
                void update_participants();

                std::set<participant_ptr> participants_;
                enum { max_recent_msgs = 100 };
                message_queue recent_msgs_;
            };

        } // chat
    } // namespace applications
} // namespace websocket

#endif // WEBSOCKET_APPLICATIONS_CHAT_ROOM_HPP