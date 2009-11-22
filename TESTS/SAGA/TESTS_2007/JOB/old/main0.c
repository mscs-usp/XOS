#include <iostream>
#include <saga.hpp>

int main() {
  try{
    saga::session s;
    saga::context c (saga::context::X509);
    s.add_context (c);
    
    std::iostream in, out, err;
    saga::job_service js (s);
    saga::job job = js.runJob ("claui2t0", "/bin/date", &in, &out, &err);
       
    while ( job.getJobState() != saga::job::Done &&
            job.getJobState() != saga::job::Failed ) {
    std::cout << out;
    std::cerr << err;
  }
  catch (saga::exception e){
    std::cerr << e.what() << std::endl;
  }
}
