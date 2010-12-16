.SUFFIXES:
ifeq ($(strip $(PSL1GHT)),)
$(error "PSL1GHT must be set in the environment.")
endif

include $(PSL1GHT)/Makefile.base

NAME		:=	ps3mlib
TARGET		:=	lib$(NAME)
BUILD		:=	build
SOURCE		:=	source
INCLUDE		:=	include

CFLAGS		+= -O2 -Wall --std=gnu99
CXXFLAGS	+= -O2 -Wall

ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT	:=	$(CURDIR)/$(TARGET)
export VPATH	:=	$(foreach dir,$(SOURCE),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))
export BUILDDIR	:=	$(CURDIR)/$(BUILD)
export DEPSDIR	:=	$(BUILDDIR)

export INCDIR	:=	$(PSL1GHT)/include/$(NAME)
export LIBDIR	:=	$(PSL1GHT)/lib

CFILES		:= $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.c)))
CXXFILES	:= $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:= $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.S)))

export OFILES	:=	$(CFILES:.c=.o) \
					$(CXXFILES:.cpp=.o) \
					$(SFILES:.S=.o) \
					$(BINFILES:.bin=.bin.o)

export INCLUDES	:=	$(foreach dir,$(INCLUDE),-I$(CURDIR)/$(dir)) \
					-I$(CURDIR)/$(BUILD)

.PHONY: $(BUILD) install clean

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

install: $(OUTPUT).a
	@[ -d $(INCDIR) ] || mkdir -p $(INCDIR)
	@echo "[CP]  *.h"
	@cp -f $(INCLUDE)/*.h $(INCDIR)
	@echo "[CP]  $(notdir $<)"
	@cp -f $< $(LIBDIR)

clean:
	@echo Clean...
	@rm -rf $(BUILD) $(OUTPUT).a

else

DEPENDS	:= $(OFILES:.o=.d)

$(OUTPUT).a: $(OFILES)
$(OFILES): $(BINFILES)

-include $(DEPENDS)

endif
