LOCAL_OBJECT_DIR ?= $(OBJECT_DIR)/$(MODULE_NAME)
C_OBJECTS := $(C_SOURCES:src/%.c=$(LOCAL_OBJECT_DIR)/%.o)

ifdef OBJECTS
	OBJECTS += $(C_OBJECTS)
else
	OBJECTS := $(C_OBJECTS)
endif

ifdef INCLUDE_DIRECTORIES
	INCLUDE_DIRECTORIES += include
else
	INCLUDE_DIRECTORIES := include
endif

$(shell mkdir -p $(LOCAL_OBJECT_DIR))

$(OBJECT_DIR)/$(MODULE_NAME).o: $(OBJECTS)
	$(LINKER) -relocatable $^ -o $@

$(C_OBJECTS): $(OBJECT_DIR)/$(MODULE_NAME)/%.o : src/%.c
	mkdir -p $(@D)
	$(C_COMPILER) -c $^ -o $@ $(C_FLAGS) $(INCLUDE_DIRECTORIES:%=-I%)
