TOOLCHAIN := $(OO_PS4_TOOLCHAIN)

CCX := clang++
LD := ld.lld

INTDIR := build
CPPFILES := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,$(INTDIR)/%.o,$(CPPFILES))

CXXFLAGS := --target=x86_64-pc-freebsd12-elf \
	-fPIC -funwind-tables -c \
	-isysroot $(TOOLCHAIN) \
	-isystem $(TOOLCHAIN)/include \
	-isystem $(TOOLCHAIN)/include/c++/v1

LDFLAGS := -m elf_x86_64 -pie \
	--script $(TOOLCHAIN)/link.x \
	--eh-frame-hdr \
	-L$(TOOLCHAIN)/lib \
	-lc -lkernel -lc++ \
	$(TOOLCHAIN)/lib/crt1.o

all: eboot.bin

$(INTDIR):
	mkdir -p $(INTDIR)

$(INTDIR)/%.o: src/%.cpp | $(INTDIR)
	$(CCX) $(CXXFLAGS) -o $@ $<

eboot.bin: $(OBJS)
	$(LD) $(OBJS) -o $(INTDIR)/SAMIX-GAMES.elf $(LDFLAGS)
	$(TOOLCHAIN)/bin/linux/create-fself \
		-in=$(INTDIR)/SAMIX-GAMES.elf \
		-out=$(INTDIR)/SAMIX-GAMES.oelf \
		--eboot "eboot.bin" \
		--paid 0x3800000000000011

clean:
	rm -rf $(INTDIR) eboot.bin

.PHONY: all clean