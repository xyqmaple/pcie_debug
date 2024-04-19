#     Priority to include "Rules.mk" of the parent direcotry, then include
# "Rules.mk" of the current directory.
RULES_MK := $(addsuffix ../$(notdir $(RULES_MK)),$(dir $(RULES_MK)))
-include $(RULES_MK)
 
ifeq ($(RULES_LIST),)
RULES_LIST := $(MAKEFILE_LIST)
else
RULES_LIST := $(filter-out $(lastword $(RULES_LIST)),$(RULES_LIST))
endif

# --------------------------------------------------------------------------- #
# Directory
# --------------------------------------------------------------------------- #
 
# The directory path where the current file is located
CUR_DIR := $(shell dirname $(abspath $(lastword $(RULES_LIST))))
# The directory name where the current file is located
CUR_DIR_NAME := $(notdir $(CUR_DIR))

RELEASE_DIR := $(CUR_DIR)/release
SRC_DIR := $(CUR_DIR)
OBJ_DIR := $(RELEASE_DIR)/obj

# --------------------------------------------------------------------------- #
# Alias
# --------------------------------------------------------------------------- #

ECHO := echo
MKDIR := mkdir
Q := @
RM := rm
