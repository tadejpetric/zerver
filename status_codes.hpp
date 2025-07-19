
#pragma once

#include <type_traits>
#include <utility>

enum class StatusCode : int {
    // Informational
    Continue_100 = 100,
    Switching_Protocols_101 = 101,
    Processing_102 = 102,
    Early_Hints_103 = 103,

    // Success
    OK_200 = 200,
    Created_201 = 201,
    Accepted_202 = 202,
    Non_Authoritative_Information_203 = 203,
    No_Content_204 = 204,
    Reset_Content_205 = 205,
    Partial_Content_206 = 206,
    Multi_Status_207 = 207,
    Already_Reported_208 = 208,
    IM_Used_226 = 226,

    // Redirection
    Multiple_Choices_300 = 300,
    Moved_Permanently_301 = 301,
    Found_302 = 302,
    See_Other_303 = 303,
    Not_Modified_304 = 304,
    Use_Proxy_305 = 305,
    Switch_Proxy_306 = 306,
    Temporary_Redirect_307 = 307,
    Permanent_Redirect_308 = 308,

    // ClientErrors
    Bad_Request_400 = 400,
    Unauthorized_401 = 401,
    Payment_Required_402 = 402,
    Forbidden_403 = 403,
    Not_Found_404 = 404,
    Method_Not_Allowed_405 = 405,
    Not_Acceptable_406 = 406,
    Proxy_Authentication_Required_407 = 407,
    Request_Timeout_408 = 408,
    Conflict_409 = 409,
    Gone_410 = 410,
    Length_Required_411 = 411,
    Precondition_Failed_412 = 412,
    Payload_Too_Large_413 = 413,
    URI_Too_Long_414 = 414,
    Unsupported_Media_Type_415 = 415,
    Range_Not_Satisfiable_416 = 416,
    Expectation_Failed_417 = 417,
    Im_a_Teapot_418 = 418,
    Misdirected_Request_421 = 421,
    Unprocessable_Content_422 = 422,
    Locked_423 = 423,
    Failed_Dependency_424 = 424,
    Too_Early_425 = 425,
    Upgrade_Required_426 = 426,
    Precondition_Required_428 = 428,
    Too_Many_Requests_429 = 429,
    Request_Header_Fields_Too_Large_431 = 431,
    Unavailable_For_Legal_Reasons_451 = 451,

    // ServerErrors
    Internal_Server_Error_500 = 500,
    Not_Implemented_501 = 501,
    Bad_Gateway_502 = 502,
    Service_Unavailable_503 = 503,
    Gateway_Timeout_504 = 504,
    HTTP_Version_Not_Supported_505 = 505,
    Variant_Also_Negotiates_506 = 506,
    Insufficient_Storage_507 = 507,
    Loop_Detected_508 = 508,
    Not_Extended_510 = 510,
    Network_Authentication_Required_511 = 511
};

enum class StatusType {
    Informational,
    Success,
    Redirection,
    ClientErrors,
    ServerErrors,
};

StatusType code_to_type(StatusCode code) {
    int code_number = std::to_underlying(code);

    int first_digit = code_number / 100;

    switch (first_digit) {
        case 1:
            return StatusType::Informational;
        case 2:
            return StatusType::Success;
        case 3:
            return StatusType::Redirection;
        case 4:
            return StatusType::ClientErrors;
        case 5:
            return StatusType::ServerErrors;
        default:
            std::unreachable();
    }
}