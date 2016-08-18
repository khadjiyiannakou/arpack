############################################################################
#
#  Program:         ARPACK
#
#  Module:          ARmake.inc
#
#  Purpose:         Top-level Definitions
#
#  Creation date:   February 22, 1996
#
#  Modified:	    Decembe 30, 2013
#
#  Send bug reports, comments or suggestions to arpack@caam.rice.edu
#
############################################################################
#
#
#  *** If you are using a VENDOR SUPPLIED VERSION of MPI, you    ***
#  *** must replace the mpif.h in the following directories      ***
#  ***                                                           ***
#  ***            ARPACK/PARPACK/SRC/MPI/mpif.h                  ***
#  ***            ARPACK/PARPACK/UTIL/MPI/mpif.h                 ***
#  ***            ARPACK/PARPACK/EXAMPLES/MPI/mpif.h             ***
#  ***                                                           ***
#  *** with the one for the native implementation.               ***


###############################################################################
# load config
### include /global/homes/m/marcusp/tmp/build-20130110/sources-20130110/ARPACK/ARmake.config

# setup paths
PLAT	= MPI
prefix	= /home/hpc/pr84le/di72wec/install
home    = /home/hpc/pr84le/di72wec/build/ARPACK
export home prefix
###############################################################################

#
#  The platform identifier to suffix to the end of library names
#
#
#  The communication library ( need for parallel library only )
#  Current availible platforms are: BLACS or MPI
#
COMMLIB       	 = MPI
#
#  The directories to find the various pieces of ARPACK
#
BLASdir		 = $(home)/BLAS
LAPACKdir	 = $(home)/LAPACK
UTILdir      	 = $(home)/UTIL
SRCdir       	 = $(home)/SRC
PSRCdir      	 = $(home)/PARPACK/SRC/$(COMMLIB)
PUTILdir     	 = $(home)/PARPACK/UTIL/$(COMMLIB)
#
DIRS   = $(BLASdir) $(LAPACKdir) $(UTILdir) $(SRCdir)
# Comment out the previous line and uncomment the following
# if you already have the BLAS and LAPACK installed on your system.
# NOTE: ARPACK assumes the use of LAPACK version 2 codes.
#DIRS   = $(UTILdir) $(SRCdir)

#  The name of the libraries to be created/linked to
ARPACKLIB 	 = $(prefix)/lib/libarpack.a
PARPACKLIB 	 = $(prefix)/lib/libparpack.a
LAPACKLIB  	 = $(prefix)/lib/liblapack.a
BLASLIB    	 = $(prefix)/lib/libblas.a

ALIBS 		 =  $(ARPACKLIB) $(LAPACKLIB) $(BLASLIB) 

# Libraries needed for Parallel ARPACK - MPI 
PLIBS = $(PARPACKLIB) $(ALIBS) $(MPILIBS)



#  Make our own suffixes' list.
#
.SUFFIXES:
.SUFFIXES:	.f	.o
.SUFFIXES:	.F	.f

#
#  Default command.
#
.DEFAULT:
	@$(ECHO) "Unknown target $@, try:  make help"

#
#  Command to build .o files from .f files.
#
.f.o:
	@$(ECHO) Making $@ from $<
	@$(FC) -c $(FFLAGS) $<

.F.f:
	@$(ECHO) Making $*.f from $<
	@$(CPP) -P -DSINGLE $(CPPFLAGS) $< $*.f
	@$(ECHO) Making d$*.f from $<
	@$(CPP) -P -DDOUBLE $(CPPFLAGS) $< d$*.f



# SNS FC, FFLAGS, PFC, PFFLAGS are set in ARmake.config
FC	= ifort
FFLAGS	= -I/opt/ibmhpc/pe1308/mpich2/intel/include64/
PFC     = ifort
PFFLAGS	= -I/opt/ibmhpc/pe1308/mpich2/intel/include64/

LDFLAGS  =
CD	 = cd
AR       = /usr/bin/ar

CHMOD	 = chmod
CHFLAGS	 = -f

COMPRESS = compress

CP	 = cp

#  To find the path for cpp, try `man cpp', and it should list the path
#  at the top, under `Syntax'.  It is usually in /lib.
CPP	 = cpp
CPPFLAGS =

ECHO	 = echo

LN	 = ln
LNFLAGS	 = -s

MAKE	 = make

MKDIR	 = mkdir
MDFLAGS	 = -p

MV	 = mv
MVFLAGS	 = -f

RM	 = rm
RMFLAGS  = -f

SHELL	 = /bin/sh

TAR	 = tar

#  For System V based machine without ranlib, like Cray and SGI, 
#  use touch instead.
RANLIB  ?= touch

#
#  This is the general help target.
#
help:
	@$(ECHO) "usage: make ?"


# vim: syn=make
