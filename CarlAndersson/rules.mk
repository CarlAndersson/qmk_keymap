SRC += CarlAndersson.c

ifeq ($(strip $(USERSPACE_ONESHOTS_ENABLE)), yes)
	SRC += $(USER_PATH)/oneshot.c
	OPT_DEFS += -DUSERSPACE_ONESHOTS_ENABLE
endif

ifeq ($(strip $(USERSPACE_CAPSWORD_ENABLE)), yes)
	SRC += $(USER_PATH)/capsword.c
	OPT_DEFS += -DUSERSPACE_CAPSWORD_ENABLE
endif

ifeq ($(strip $(USERSPACE_REPEATKEY_ENABLE)), yes)
	SRC += $(USER_PATH)/repeatkey.c
	OPT_DEFS += -DUSERSPACE_REPEATKEY_ENABLE
endif