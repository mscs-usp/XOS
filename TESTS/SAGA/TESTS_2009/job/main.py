from time import sleep

from saga import url
from saga.job import (New, Running, Suspended, Done, Failed, Canceled,
                      description, service)

# EXEC_PATH = "/home/kortas/EX/ZEPHYR/SRC/zephyr"
EXEC_PATH = "/tmp/fake_zephyr.sh"

def state_to_string(state):
    if state == New:
        return "New      "
    elif state == Running :
        return "Running  "
    elif state == Suspended:
        return "Suspended"
    elif state == Done:
        return "Done     "
    elif state == Failed:
        return "Failed   "
    elif state == Canceled:
        return "Canceled "
    else:
        print "Unknown state:", state
        return "Unknown  "

if __name__ == "__main__":
    jd_valid = description()
    jd_valid.executable = EXEC_PATH

    s1 = service(url("xos://xos-core"))

    j1 = s1.create_job(jd_valid)
    j2 = s1.create_job(jd_valid)

    print "NOT RUN! Job state is:", state_to_string(j1.get_state())

    j1.run()
    print "JobID:", j1.get_job_id()
    print "Just RUN! Job state is:", state_to_string(j1.get_state())

    j1.suspend()
    print "SUSPENDED! Job state is:", state_to_string(j1.get_state())

    j1.resume()
    print "RESUMED! Job state is:", state_to_string(j1.get_state())

    print "NOT DONE! Job state is:", state_to_string(j1.get_state())

    j1.wait(3.0)

    print "AWAITED! Job state is:", state_to_string(j1.get_state())

    sleep(30)
    print "should be DONE by now! Job state is:", \
        state_to_string(j1.get_state())

    # j1.cancel()

    j2.run()
    print "JobID:", j2.get_job_id()
    print "Just RUN! Job state is:", state_to_string(j2.get_state())

    j2.cancel()
    print "CANCELED! Job state is:", state_to_string(j2.get_state())

    sleep(20)
    print "should be DONE by now! Job state is:", \
        state_to_string(j2.get_state())
