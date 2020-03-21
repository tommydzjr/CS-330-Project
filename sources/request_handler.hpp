#ifndef WEBSOCKET_HTTP_REQUEST_HANDLER_HPP
#define WEBSOCKET_HTTP_REQUEST_HANDLER_HPP

#include <string>
#include <vector>
#include <boost/noncopyable.hpp>

namespace websocket {
    namespace http {

        struct reply;
        struct request;

        /// The handler for incoming http requests.
        class request_handler
            : private boost::noncopyable
        {
        public:
            /// Handle a request and produce a reply.
            static void handle_request(const request& req, reply& rep);

        private:
            /// Encode data using the SHA1 algorithm.
            static std::vector<unsigned char> to_sha1(const std::string& s);

            /// Encode data using the Base64 algorithm.
            static std::string to_base64(const std::vector<unsigned char>& data);
        };

    } // namespace http
} // namespace websocket

#endif // WEBSOCKET_HTTP_REQUEST_HANDLER_HPP