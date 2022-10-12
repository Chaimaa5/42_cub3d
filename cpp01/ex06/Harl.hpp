#include <iostream>

class   Harl{
    public:
        void    complain(std::string level);
    enum filterlevel{
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        noComplaint = -1
    };
        filterlevel    getLevel(std::string level);
    private:
        void debug( void );
        void info( void );
        void warning( void );
        void error( void );
        void    default_complain(void);
};