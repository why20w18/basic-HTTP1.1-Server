#ifdef DEBUG
    #define LOG(x) std::cout << "[DEBUG-MODE] : " << x << "\n"
    #define FOLOG(x)  std::cout << "\033[0;33m[FILE-OPEN] : \033[0m" << x << "\n"
    #define COLOG(x) std::cout << "\033[0;34m[SERVER-COMMAND] : \033[0m\033[0;35m" << x << "\033[0m\n\n"

#elif WIN32 
    #define LOG(x) std::cout << "[DEBUG-MODE-WIN32] : " << x << "\n" //release modda burayi kaldir ve derle
    #define FOLOG(x)  std::cout << "[FILE-OPEN] : " << x << "\n"
    #define COLOG(x) std::cout << "[SERVER-COMMAND] : " << x << "\n\n"


#else DEBUG
    #define LOG(x)
    #define FOLOG(x)  std::cout << "\033[0;33m[FILE-OPEN] : \033[0m" << x << "\n"
    #define COLOG(x) std::cout << "\033[0;34m[SERVER-COMMAND] : \033[0m\033[0;35m" << x << "\033[0m\n\n"

#endif