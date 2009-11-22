//  Copyright (c) 2005-2007 Andre Merzky (andre@merzky.net)
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <saga.hpp>

///////////////////////////////////////////////////////////////////////////////
int main (int argc, char* argv[])
{
    namespace attribs = saga::attributes;
    
    saga::job_description jd_valid;
    jd_valid.set_attribute (attribs::job_description_executable,  "/bin/sleep");
    jd_valid.set_attribute (attribs::job_description_arguments,  "10");
    
    saga::job_service s1("any://localhost");
    
    //for( int i=0; i <= 1; ++i )
    //{
        saga::job j1 = s1.create_job(jd_valid);
        j1.run();
        std::cout << "JobID: " << j1.get_job_id() << std::endl;
    //}
    
    std::cout << "NOT DONE! Job state is: " << j1.get_state() << std::endl;
    
    j1.wait();
    sleep(1);
    std::cout << "DONE! Job state is: " << j1.get_state() << std::endl;
    
    
    /*
    std::vector<std::string> joblist = s1.list();
    std::vector<std::string>::const_iterator it;
    
    while(1)
    {
        for (it = joblist.begin(); it != joblist.end(); ++it) {
            std::cout << "s1 owns: " << (*it) << std::flush;
            saga::job recon = s1.get_job ((*it));
            std::cout << " job state: " << recon.get_state() << std::endl;
        }
        sleep(1);
    }
    */
    return 0;
}

