LDFLAGS=-lrt -pthread
SRCDIR=src
BINDIR=bin
evaluator: ${SRCDIR}/evaluador.o ${SRCDIR}/init.o ${SRCDIR}/reg.o ${SRCDIR}/ctrl.o ${SRCDIR}/rep.o ${SRCDIR}/parser.o ${SRCDIR}/stop.o ${SRCDIR}/elements.o ${SRCDIR}/manejador_mem.o ${BINDIR}/manejador_sem.o ${BINDIR}/manejador_hil.o
	$(CXX) -o $@ $^ $(LDFLAGS)

${SRCDIR}/evaluador.o: ${SRCDIR}/evaluador.cpp ${SRCDIR}/init.h ${SRCDIR}/reg.h ${SRCDIR}/ctrl.h ${SRCDIR}/rep.h ${SRCDIR}/elements.h ${SRCDIR}/stop.h

${SRCDIR}/manejador_hil.o: ${SRCDIR}/manejador_hil.cpp ${SRCDIR}/manejador_hil.h

${SRCDIR}/manejador_mem.o: ${SRCDIR}/manejador_mem.cpp ${SRCDIR}/manejador_mem.h

${SRCDIR}/manejador_sem.o: ${SRCDIR}/manejador_sem.cpp ${SRCDIR}/manejador_sem.h

${SRCDIR}/init.o: ${SRCDIR}/init.cpp ${SRCDIR}/init.h ${SRCDIR}/elements.h ${SRCDIR}/manejador_hil.h ${SRCDIR}/manejador_sem.h ${SRCDIR}/manejador_mem.h

${SRCDIR}/reg.o: ${SRCDIR}/reg.cpp ${SRCDIR}/reg.h

${SRCDIR}/ctrl.o: ${SRCDIR}/ctrl.cpp ${SRCDIR}/ctrl.h

${SRCDIR}/rep.o: ${SRCDIR}/rep.cpp ${SRCDIR}/rep.h

${SRCDIR}/parser.o: ${SRCDIR}/parser.cpp ${SRCDIR}/parser.h

${SRCDIR}/stop.o: ${SRCDIR}/stop.cpp ${SRCDIR}/stop.h

${SRCDIR}/elements.o: ${SRCDIR}/elements.cpp ${SRCDIR}/elements.h

clean:
	rm -f ${BINDIR}/*.o
	rm -f ${SRCDIR}/.~ *~
	rm -f ${SRCDIR}/evaluador
	rm -f ${SRCDIR}/evaluador.exe
	rm -f ./evaluador.exe

	