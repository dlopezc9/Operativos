LDFLAGS=-lrt -pthread
SRCDIR=src
BINDIR=bin
evaluator: ${BINDIR}/evaluador.o ${BINDIR}/init.o ${BINDIR}/reg.o ${BINDIR}/ctrl.o ${BINDIR}/rep.o ${BINDIR}/parser.o ${BINDIR}/stop.o ${BINDIR}/elements.o ${BINDIR}/manejador_mem.o ${BINDIR}/manejador_sem.o ${BINDIR}/manejador_hil.o
	$(CXX) -o $@ $^ $(LDFLAGS)

${BINDIR}/evaluador.o: ${SRCDIR}/evaluador.cpp ${SRCDIR}/init.h ${SRCDIR}/reg.h ${SRCDIR}/ctrl.h ${SRCDIR}/rep.h ${SRCDIR}/elements.h ${SRCDIR}/stop.h

${BINDIR}/manejador_hil.o: ${SRCDIR}/manejador_hil.cpp ${SRCDIR}/manejador_hil.h

${BINDIR}/manejador_mem.o: ${SRCDIR}/manejador_mem.cpp ${SRCDIR}/manejador_mem.h

${BINDIR}/manejador_sem.o: ${SRCDIR}/manejador_sem.cpp ${SRCDIR}/manejador_sem.h

${BINDIR}/init.o: ${SRCDIR}/init.cpp ${SRCDIR}/init.h ${SRCDIR}/elements.h ${SRCDIR}/manejador_hil.h ${SRCDIR}/manejador_sem.h ${SRCDIR}/manejador_mem.h

${BINDIR}/reg.o: ${SRCDIR}/reg.cpp ${SRCDIR}/reg.h

${BINDIR}/ctrl.o: ${SRCDIR}/ctrl.cpp ${SRCDIR}/ctrl.h

${BINDIR}/rep.o: ${SRCDIR}/rep.cpp ${SRCDIR}/rep.h

${BINDIR}/parser.o: ${SRCDIR}/parser.cpp ${SRCDIR}/parser.h

${BINDIR}/stop.o: ${SRCDIR}/stop.cpp ${SRCDIR}/stop.h

${BINDIR}/elements.o: ${SRCDIR}/elements.cpp ${SRCDIR}/elements.h

clean:
	rm -f ${BINDIR}/*.o
	rm -f ${SRCDIR}/.~ *~
	rm -f ${SRCDIR}/evaluador
	rm -f ${SRCDIR}/evaluador.exe
	rm -f ./evaluador.exe

	