#include <unistd.h>

#include <optional>
#include <string>
#include <variant>
#include <cassert>

#pragma once

enum class HTTP_Method {
    // https://http.dev/methods
    GET,
    HEAD,
    OPTIONS,
    TRACE,
    DELETE,
    PUT,
    POST,
    PATCH,
    CONNECT,
};

enum class HTTP_Version {
    v09,
    v10,
    v11,
    v2,
    v3,
};

typedef std::optional<std::string> optstr;

enum class RequestErrors {
    Bad_Request_400,
    Payload_Too_Large_413,
    URI_Too_Long_414,

    Internal_Server_Error_500,
    Not_Implemented_501,
};

struct Request {
    // Request start line
    HTTP_Method method;
    std::string request_target;
    HTTP_Version version;

    // https://http.dev/headers
    // Authentication
    optstr WWW_Authenticate;
    optstr Authorization;
    optstr Proxy_Authenticate;
    optstr Proxy_Authorization;

    // Caching
    optstr Age;
    optstr Cache_Control;
    optstr Clear_Site_Data;
    optstr Expires;
    optstr Pragma;
    optstr Warning;

    // Client Hints
    optstr Accept_CH;

    // Network client hints
    optstr Save_Data;

    // Conditionals
    optstr Last_Modified;
    optstr ETag;
    optstr If_Match;
    optstr If_None_Match;
    optstr If_Modified_Since;
    optstr If_Unmodified_Since;
    optstr Vary;
    optstr Delta_Base;

    // Connection management
    optstr Connection;
    optstr Keep_Alive;

    // Content negotiation
    optstr Accept;
    optstr Accept_Encoding;
    optstr Accept_Language;
    optstr A_IM;
    optstr IM;

    // Controls
    optstr Expect;
    optstr Max_Forwards;

    // Cookies
    optstr Cookie;
    optstr Set_Cookie;

    // CORS
    optstr Access_Control_Allow_Origin;
    optstr Access_Control_Allow_Credentials;
    optstr Access_Control_Allow_Headers;
    optstr Access_Control_Expose_Headers;
    optstr Access_Control_Max_Age;
    optstr Access_Control_Request_Headers;
    optstr Access_Control_Request_Method;
    optstr Timing_Allow_Origin;

    // Downloads
    optstr Content_Disposition;

    // Message body information
    optstr Content_Length;
    optstr Content_Type;
    optstr Content_Encoding;
    optstr Content_Language;
    optstr Content_Location;

    // Proxies
    optstr Forwarded;
    optstr X_Forwarded_For;
    optstr X_Forwarded_Host;
    optstr X_Forwarded_Proto;
    optstr Via;

    // Redirects
    optstr Location;

    // Request context
    optstr From;
    optstr Host;
    optstr Referer;  // intentional typo
    optstr Referrer_Policy;
    optstr User_Agent;

    // Response context
    optstr Allow;
    optstr Server;

    // Range requests
    optstr Accept_Ranges;
    optstr Range;
    optstr If_Range;
    optstr Content_Range;

    // Security
    optstr Cross_Origin_Embedder_Policy;  // (COEP)
    optstr Cross_Origin_Opener_Policy;    // (COOP)
    optstr Cross_Origin_Resource_Policy;  // (CORP)
    optstr Content_Security_Policy;       // (CSP)
    optstr Content_Security_Policy_Report_Only;
    optstr Expect_CT;
    optstr Strict_Transport_Security;  // (HSTS)
    optstr Upgrade_Insecure_Requests;
    optstr X_Content_Type_Options;
    optstr X_Frame_Options;
    optstr X_Powered_By;
    optstr X_XSS_Protection;

    // Fetch metadata request headers
    optstr Sec_Fetch_Site;
    optstr Sec_Fetch_Mode;
    optstr Sec_Fetch_User;
    optstr Sec_Fetch_Dest;

    // Server_Sent events
    optstr NEL;

    // Transfer coding
    optstr Transfer_Encoding;
    optstr TE;
    optstr Trailer;

    // WebSockets
    optstr Sec_Websocket_Accept;

    // Other
    optstr Alt_Svc;
    optstr Date;
    optstr Link;
    optstr Retry_After;
    optstr Server_Timing;
    optstr Sourcemap;
    optstr Upgrade;
    optstr X_DNS_Prefetch_Control;
    optstr X_Request_ID;
    optstr X_Robots_Tag;
    optstr X_UA_Compatible;
};

namespace {
inline constexpr std::size_t BUFFER_LEN = 1024;
inline constexpr std::size_t MAX_START_LINE_LEN = 2048;
inline constexpr std::size_t MAX_HEADER_LEN = 32768;
}

std::variant<Request, RequestErrors> read_request(int client_fd) {
    // Read message iteratively
    char buffer[BUFFER_LEN];

    // First read the start line
    // Start line has <method> <URI> <version>\r\n
    ssize_t n = read(client_fd, buffer, sizeof(buffer));
    if (n < 0) {
        // error happened while reading from the socket
        return RequestErrors::Internal_Server_Error_500;
    }

    assert(n <= BUFFER_LEN);
    assert(BUFFER_LEN > 8);
    if (!memcmp(buffer, "GET ", 4)) {

    } elif (!memcmp(buffer, ""))


    


    do {
        if (n < 0) {
            // error happened while reading from the socket
            return RequestErrors::Internal_Server_Error_500;
        } else
            buffer[n] = '\0';
        std::cout << "Received: " << buffer << "\n";
    } while (n > 0);
}