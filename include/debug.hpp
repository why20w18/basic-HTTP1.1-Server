#ifdef DEBUG
    #define LOG(x) std::cout << "[DEBUG-MODE] " << x << "\n"

#else DEBUG
    #define LOG(x)

#endif