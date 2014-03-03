include ../thumb/Makedefs

#------------------------------------------------------------------------------

VIEWOBJS= view-load.o view-app.o

ORBOBJS= $(VIEWOBJS) orbiter.o
PANOBJS= $(VIEWOBJS) panoview.o

PANDEPS= $(PANOBJS:.o=.d)
ORBDEPS= $(ORBOBJS:.o=.d)

#------------------------------------------------------------------------------

CFLAGS += -I../thumb/include
LIBS   += -L../thumb/src -lthumb scm/libscm.a

#------------------------------------------------------------------------------

all : panoview orbiter

panoview: scm $(PANOBJS) $(THUMB)
	$(CXX) $(CFLAGS) -o $@ $(PANOBJS) $(LIBS)

orbiter: scm $(ORBOBJS) $(THUMB)
	$(CXX) $(CFLAGS) -o $@ $(ORBOBJS) $(LIBS)

clean:
	$(RM) $(PANOBJS) $(PANDEPS) panoview
	$(RM) $(ORBOBJS) $(ORBDEPS) orbiter

#------------------------------------------------------------------------------

scm : .FORCE
	$(MAKE) -C scm

.FORCE :

#------------------------------------------------------------------------------

ifneq ($(MAKECMDGOALS),clean)
-include $(PANDEPS) $(ORBDEPS)
endif

export CFLAGS


