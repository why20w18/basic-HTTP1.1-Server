#ifdef __linux__
    #define SLOG(x) std::cout << "\033[0;32m\n[HTTP-SERVER-LOG] : \033[0m" << x << "\n";
    #define SLOGN(x) std::cout << "\033[0;32m\n[HTTP-SERVER-LOG] : \033[0m" << x;

    #define DEFAULT_DIRECTORY "src/http"
    #define DEFAULT_DELIMITER "/"
    #define DEFAULT_OPERATING_SYSTEM 1
    #define DEFAULT_REQUEST "/"
#else 
    #define SLOG(x) std::cout << "\n[HTTP-SERVER-LOG] : " << x << "\n";
    #define SLOGN(x) std::cout << "\n[HTTP-SERVER-LOG] : " << x;

    #define DEFAULT_DIRECTORY "src\\http"
    #define DEFAULT_DELIMITER "\\"
    #define DEFAULT_OPERATING_SYSTEM 2
    #define DEFAULT_REQUEST ""
#endif