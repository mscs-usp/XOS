// -----------------------------------------------
// c++ example
std::list <std::string>    transfers;
saga::job_description jobdef;
saga::job_service     js;
transfers.push_back ("infile > infile");
transfers.push_back ("ftp://host.net/path/out << outfile");
jobdef.set_attribute        ("CandidateHost", "hostname");
jobdef.set_attribute        ("Executable",    "job.sh");
jobdef.set_attribute        ("TotalCPUCount", "16");
jobdef.set_vector_attribute ("FileTransfer",  transfers);
saga::job job = js.create_job (jobdef);
job.run ();
while ( 1 )
{
  // get job state
  saga::job::state state = job.get_state ();
  // get list of hosts the job is/where running on
  std::list <std::string> hostlist = job.get_attribute
                                     ("ExecutionHosts");
  if ( saga::job::Running == state )
  {
    std::cout << "Job is running." << std::endl;
  }
  else if ( saga::job::Suspended == state )
  {
    std::cout << "Job is suspended." << std::endl;
  }
  else if ( saga::job::Done == state )
  {
    std::cout << "Job completed successfully." << std::endl;
    exit (0);
  }
  else if ( saga::job::Canceled == state )
  {
    // this should never occur, as cancel is not called.
    std::cout << "Job canceled." << std::endl;
    exit (1);
  }
  else
  {
    // state can only be 'Failed'
    assert(saga::job::Failed == state);
    std::string exitcode = job.get_attribute ("ExitCode");
    std::cout << "Job failed with " << exitcode << std::endl;
    exit (exitcode);
  }
  sleep (1); // idle
}
