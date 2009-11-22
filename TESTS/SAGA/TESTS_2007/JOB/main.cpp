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
    jd_valid.set_attribute (attribs::job_description_executable,  "/home/kortas/EX/ZEPHYR/SRC/zephyr");
    
    saga::job_service s1("any://localhost");
    
    saga::job j1 = s1.create_job(jd_valid);
    saga::job j2 = s1.create_job(jd_valid);

    std::cout << "NOT RUN! Job state is: " << state_to_string(j1.get_state()) << std::endl;

    j1.run();
    std::cout << "JobID: " << j1.get_job_id() << std::endl;
    std::cout << "Just RUN! Job state is: " << state_to_string(j1.get_state()) << std::endl;

    j1.suspend();
    std::cout << "SUSPENDED! Job state is: " << state_to_string(j1.get_state()) << std::endl;
    
    j1.resume();
    std::cout << "RESUMED! Job state is: " << state_to_string(j1.get_state()) << std::endl;
        
    
    std::cout << "NOT DONE! Job state is: " << state_to_string(j1.get_state()) << std::endl;
    
    j1.wait();

    std::cout << "AWAITED! Job state is: " << state_to_string(j1.get_state()) << std::endl;
    
    sleep(30);
    std::cout << "should be DONE by now! Job state is: " << state_to_string(j1.get_state()) << std::endl;

    //j1.cancel();
    


    j2.run();
    std::cout << "JobID: " << j2.get_job_id() << std::endl;
    std::cout << "Just RUN! Job state is: " << state_to_string(j2.get_state()) << std::endl;

    j2.cancel();
    std::cout << "CANCELED! Job state is: " << state_to_string(j2.get_state()) << std::endl;

    return 0;
}





