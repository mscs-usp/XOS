//  Copyright (c) 2005-2007 Andre Merzky (andre@merzky.net)
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <saga.hpp>

std::string state_to_string (saga::job::state state)
{
  switch ( state )
  {
    case saga::job::New       : return ("New      ");
    case saga::job::Running   : return ("Running  ");
    case saga::job::Suspended : return ("Suspended");
    case saga::job::Done      : return ("Done     ");
    case saga::job::Failed    : return ("Failed   ");
    case saga::job::Canceled  : return ("Canceled ");
    default                   : 
        std::cout << "Unknown state: " << state << std::endl;
        return ("Unknown  ");
  }
}



///////////////////////////////////////////////////////////////////////////////
int main (int argc, char* argv[])
{
    namespace attribs = saga::attributes;
    
    saga::job_description jd_valid;
    jd_valid.set_attribute (attribs::job_description_executable,  "/bin/sleep");
    jd_valid.set_attribute (attribs::job_description_arguments,  "1");
    
    saga::job_service s1("any://localhost");
    
    saga::job j1 = s1.create_job(jd_valid);
    j1.run();
    std::cout << "JobID: " << j1.get_job_id() << std::endl;
    
    std::cout << "NOT DONE! Job state is: " << state_to_string(j1.get_state()) << std::endl;
    
    j1.wait();
    sleep(5);
    j1.del();
    std::cout << "DONE! Job state is: " << state_to_string(j1.get_state()) << std::endl;
    
    return 0;
}





