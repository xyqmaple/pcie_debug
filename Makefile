RULES_MK := $(addsuffix Rules.mk,$(dir $(abspath $(firstword $(MAKEFILE_LIST)))))
-include $(RULES_MK)

.DEFAULT_GOAL := build

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET := $(RELEASE_DIR)/pci_debug

CFLAGS := -O0 -g3 -Wall -fmessage-length=0
LDFLAGS :=
LDLIBS := -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(Q)$(ECHO) "  CC \t $@"
	$(Q)$(CC) $(CFLAGS) -c $^ -o $@

$(TARGET): $(OBJS)
	$(Q)$(ECHO) "  CC \t $@"
	$(Q)$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

prepare:
	$(Q)$(MKDIR) -p $(RELEASE_DIR)
	$(Q)$(MKDIR) -p $(OBJ_DIR)

build: prepare $(TARGET)

clean:
	$(Q)$(RM) -rf $(RELEASE_DIR)

.PHONY: build clean
