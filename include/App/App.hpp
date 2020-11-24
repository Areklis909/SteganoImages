#ifndef APP_HPP
#define APP_HPP

namespace NsApp {


class App {

    int lippincott();
    void _run(int argc, const char **argv);
public:
    enum ErrorCodes {
    NotStegano = 4,
    MessageTooBig = 5,
    General = 6
    };
    
    App() = default;
    ~App() = default;

    int run(int argc, const char **argv);
};

}

#endif