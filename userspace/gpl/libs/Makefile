#***********************************************************************
#
#  Copyright (c) 2006  Broadcom Corporation
#  All Rights Reserved
#
#***********************************************************************/


#
# You do not need to modify this Makefile to add an app.
# Simply create a .autodetect in the subdir and this Makefile will enter
# that directory during make and make clean.  (Auto detected directories
# are listed in the AUTODETECT_SUBDIRS variable.  Type make show_subdirs)
#
HARDCODED_SUBDIRS :=

SUBDIRS = $(HARDCODED_SUBDIRS) \
          $(AUTODETECT_SUBDIRS_BASE) \
          $(AUTODETECT_SUBDIRS_LAYER1)


# === this is the default target ===
# Need to add a level of indirection here so that the AUTODETECT_SUBDIRS_BASE
# and AUTODETECT_SUBDIRS_LAYER1 vars can be set in make.modsw before
# we build
#
all : make_all_subdirs

ifneq ($(strip $(AEI_EXFAT_SUPPORT)),)
HARDCODED_SUBDIRS += exfat-nofuse
endif

#
# Set our CommEngine directory (by splitting the pwd into two words
# at /userspace and taking the first word only).
# Then include the common defines under CommEngine.
# You do not need to modify this part.
#
CURR_DIR := $(shell pwd)
BUILD_DIR:=$(subst /userspace, /userspace,$(CURR_DIR))
BUILD_DIR:=$(word 1, $(BUILD_DIR))
export BUILD_DIR

include $(BUILD_DIR)/make.common

# include make.modsw for autodetect variables
include $(BUILD_DIR)/make.modsw


#
# We need to declare these directory names as phony targets,
# otherwise make will think the directories themselves are
# the targets and will never execute the cmds.
# See GNU Make, 4.6 
#
.PHONY : $(SUBDIRS)


#
# Create dependency chain so that HARDCODED_SUBDIRS and
# AUTODETECT_SUBDIRS_BASE are always built before 
# AUTODETECT_SUBDIRS_LAYER1.  The base and layer1 targets are
# used by userspace/Makefile to ensure all base libs in 
# userspace/gpl, userspace/public, and userspace/private are built
# before the layer1 libs are built in those directories.
#
base : $(AUTODETECT_SUBDIRS_BASE) $(HARDCODED_SUBDIRS)

$(AUTODETECT_SUBDIRS_LAYER1) : base

layer1 : $(AUTODETECT_SUBDIRS_LAYER1)

make_all_subdirs : layer1


clean: generic_subdir_clean



##############################################################
# 
# Rules for inidividual libs
# libs can be compiled or not depending on the profile (which
# is modified via make menuconfig)
#
##############################################################


$(AUTODETECT_SUBDIRS_BASE) $(AUTODETECT_SUBDIRS_LAYER1): 
	$(MAKE) -C $@

ifneq ($(strip $(AEI_EXFAT_SUPPORT)),)
exfat-nofuse:
	$(MAKE) -C $@ 
else
exfat-nofuse:
	@echo "skipping exfat-nofuse"
endif

ifneq ($(strip $(BUILD_DLNA)),)
sqlite: sanity_check
	$(MAKE) -C sqlite dynamic
libiconv: sanity_check
	(tar xkfj libiconv.tar.bz2 2> /dev/null || true)
	$(MAKE) -C libiconv dynamic -j 1
else
sqlite: sanity_check
	@echo "skipping SQLite (not configured)"
libiconv: sanity_check
	@echo "skipping Libiconv (not configured)"
endif

ifneq ($(strip $(BUILD_OSGI_JVM)),)
classpath-0.98:
	(tar xkfz classpath-0.98.tar.gz 2> /dev/null || true)
	cd classpath-0.98; ./configure --host=mips-linux-uclibc --target=mips-linux-uclibc --enable-local-sockets --disable-gconf-peer --disable-gtk-peer --disable-plugin --enable-jni --disable-alsa --disable-dssi --disable-gjdoc --disable-libtool-lock --disable-default_toolkit --disable-gmp --disable-examples --without-x --prefix=$(INSTALL_DIR)/usr/local/classpath
	cd classpath-0.98; cp native/jni/java-nio/Makefile.modified native/jni/java-nio/Makefile
	cd classpath-0.98; cp native/jni/native-lib/Makefile.modified native/jni/native-lib/Makefile
	cd classpath-0.98; $(MAKE) install
	cd $(INSTALL_DIR)/usr/local/classpath/share/classpath; unzip -o glibj.zip
	cd $(INSTALL_DIR)/usr/local/classpath/share/classpath; rm -rf glibj.zip
	cp -f $(INSTALL_DIR)/usr/local/classpath/lib/classpath/libjavanet.so $(INSTALL_DIR)/lib/libjavanet.so
else
classpath-0.98:
	@echo "skipping classpath-0.98 (not configured)"
endif

