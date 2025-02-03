#ifdef DEBUG
    #define LOG(x) std::cout << "[DEBUG-MODE] " << x << "\n"

#elif WIN32 //release modda burayi kaldir
    #define LOG(x) std::cout << "[DEBUG-MODE-WIN32] " << x << "\n"

#else DEBUG
    #define LOG(x)

#endif