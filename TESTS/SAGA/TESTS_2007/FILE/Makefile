#  Copyright (c) 2005-2006 Andre Merzky (andre@merzky.net)
# 
#  Use, modification and distribution is subject to the Boost Software
#  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt)

SAGA_ROOT=/home/kortas/SOFTS/BUILD/0.6

SAGA_SRC         = main.cpp
SAGA_BIN         = main

SAGA_ADD_BIN_OBJ = $(SAGA_SRC:%.cpp=%.o)

include $(SAGA_ROOT)/make/saga.application.mk

distclean::
	@$(RM) advert.db logicalfile.db counter.out

