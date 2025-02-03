#ifdef DEBUG
    #define LOG(x) std::cout << "[DEBUG-MODE] : " << x << "\n"
    #define FOLOG(x)  std::cout << "\033[0;33m[FILE-OPEN] : \033[0m" << x << "\n"

#elif WIN32 
    #define LOG(x) std::cout << "[DEBUG-MODE-WIN32] : " << x << "\n" //release modda burayi kaldir ve derle
    #define FOLOG(x)  std::cout << "[FILE-OPEN] : " << x << "\n"

#else DEBUG
    #define LOG(x)
    #define FOLOG(x)  std::cout << "\033[0;33m[FILE-OPEN] : \033[0m" << x << "\n"

#endif