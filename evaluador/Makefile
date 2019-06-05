LDFLAGS=-lrt -pthread
SRCDIR=src
${SRCDIR}/evaluator: ${SRCDIR}/evaluador.o ${SRCDIR}/init.o ${SRCDIR}/reg.o ${SRCDIR}/ctrl.o ${SRCDIR}/rep.o ${SRCDIR}/parser.o ${SRCDIR}/stop.o ${SRCDIR}/memory_elements.o
	$(CXX) -o $@ $^ $(LDFLAGS)

${SRCDIR}/evaluador.o: ${SRCDIR}/evaluador.cpp ${SRCDIR}/init.h ${SRCDIR}/reg.h ${SRCDIR}/ctrl.h ${SRCDIR}/rep.h ${SRCDIR}/memory_elements.h ${SRCDIR}/stop.h

${SRCDIR}/init.o: ${SRCDIR}/init.cpp ${SRCDIR}/init.h ${SRCDIR}/memory_elements.h

${SRCDIR}/reg.o: ${SRCDIR}/reg.cpp ${SRCDIR}/reg.h

${SRCDIR}/ctrl.o: ${SRCDIR}/ctrl.cpp ${SRCDIR}/ctrl.h

${SRCDIR}/rep.o: ${SRCDIR}/rep.cpp ${SRCDIR}/rep.h

${SRCDIR}/parser.o: ${SRCDIR}/parser.cpp ${SRCDIR}/parser.h

${SRCDIR}/stop.o: ${SRCDIR}/stop.cpp ${SRCDIR}/stop.h

${SRCDIR}/memory_elements.o: ${SRCDIR}/memory_elements.cpp ${SRCDIR}/memory_elements.h

clean:
	rm -f ${SRCDIR}/*.o
	rm -f ${SRCDIR}/.~ *~
	rm -f ${SRCDIR}/evaluador
	