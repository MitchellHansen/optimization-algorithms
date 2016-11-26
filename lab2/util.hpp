
struct timer{
    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;
    void start(){t1 = std::chrono::high_resolution_clock::now();}
    void end(){t2 = std::chrono::high_resolution_clock::now();}
    double duration(){ return std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();}
};