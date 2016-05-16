#include "Logging.h"

void logf( const std::string &text )
{
   std::ofstream log_file(
       "log_file.txt", std::ios_base::out | std::ios_base::app );
   log_file << text << std::endl;
}
