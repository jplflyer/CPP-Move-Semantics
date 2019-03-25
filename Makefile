CXXFLAGS := -I/usr/local/include -I./src/includes -std=c++14 -g -Wno-unused-local-typedefs
LDFLAGS := -lstdc++
COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -Isrc $(TARGET_ARCH) -c

OBJDIR=obj

PROGRAMS=Test_Simple Test_Simple2 Test_Final JustMove

.PHONY: all
all: directories ${PROGRAMS}

.PHONY: directories
directories: ${OBJDIR}

${OBJDIR}:
	mkdir -p ${OBJDIR}

${OBJDIR}/%.o : %.cpp
	$(COMPILE.cc) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)


clean:
	rm -rf ${OBJDIR} ${PROGRAMS}

Test_Simple: ${OBJDIR}/MyString_Simple.o ${OBJDIR}/Test_Simple.o
	$(CXX) ${OBJDIR}/MyString_Simple.o ${OBJDIR}/Test_Simple.o ${LDFLAGS} $(OUTPUT_OPTION)

Test_Simple2: ${OBJDIR}/MyString_Simple.o ${OBJDIR}/Test_Simple2.o
	$(CXX) ${OBJDIR}/MyString_Simple.o ${OBJDIR}/Test_Simple2.o ${LDFLAGS} $(OUTPUT_OPTION)

Test_Final: ${OBJDIR}/MyString_Final.o ${OBJDIR}/Test_Final.o
	$(CXX) ${OBJDIR}/MyString_Final.o ${OBJDIR}/Test_Final.o ${LDFLAGS} $(OUTPUT_OPTION)

JustMove: ${OBJDIR}/JustMove.o
	$(CXX) ${OBJDIR}/JustMove.o ${LDFLAGS} $(OUTPUT_OPTION)
