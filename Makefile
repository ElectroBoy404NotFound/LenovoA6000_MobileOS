PROJECT_NAME = LinuxFB

SRCDIR := src
INCDIR := inc
OBJDIR := bin
BUILDDIR = out

INSTALL_DIR ?= install

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
# DIRS = $(wildcard $(SRCDIR)/*)

CROSS_COMPILE ?= arm-linux-gnueabi-

CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)gcc

CFLAGS = -I$(INCDIR) -c -Os -fdata-sections -ffunction-sections
LDFLAGS = -Wl,--gc-sections -dead-strip -s -Os -fdata-sections -ffunction-sections --static

# CFLAGS = -I$(INCDIR) -static -c -Os -fdata-sections -ffunction-sections
# LDFLAGS = -lc -dead-strip -fdata-sections -ffunction-sections


all: build
	@echo "$(BUILDDIR)/$(PROJECT_NAME) is ready"

build: clean $(OBJS) link

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "[CC]\t$@"
	@$(CC) $(CFLAGS) $^ -o $@
link:
	@echo "[LD]\t$(BUILDDIR)/$(PROJECT_NAME)"
	@$(LD) $(OBJS) -o $(BUILDDIR)/$(PROJECT_NAME) $(LDFLAGS) 
clean:
	@echo "Cleaning project $(PROJECT_NAME)..."
	@rm -rf bin/*
	@rm -rf out/*
	@echo "Clean complete!"
