LDFLAGS=-lrt -pthread
SRCDIR=src
BINDIR=bin
evaluator: ${SRCDIR}/bin/evaluador.o ${SRCDIR}/bin/init.o ${SRCDIR}/bin/reg.o ${SRCDIR}/bin/ctrl.o ${SRCDIR}/bin/rep.o ${SRCDIR}/bin/parser.o ${SRCDIR}/bin/stop.o ${SRCDIR}/bin/elements.o ${SRCDIR}/bin/manejador_mem.o ${SRCDIR}/bin/manejador_sem.o ${SRCDIR}/bin/manejador_hil.o
	$(CXX) -o $@ $^ $(LDFLAGS)

${SRCDIR}/bin/evaluador.o: ${SRCDIR}/evaluador.cpp ${SRCDIR}/init.h ${SRCDIR}/reg.h ${SRCDIR}/ctrl.h ${SRCDIR}/rep.h ${SRCDIR}/elements.h ${SRCDIR}/stop.h

${SRCDIR}/bin/manejador_hil.o: ${SRCDIR}/manejador_hil.cpp ${SRCDIR}/manejador_hil.h

${SRCDIR}/bin/manejador_mem.o: ${SRCDIR}/manejador_mem.cpp ${SRCDIR}/manejador_mem.h

${SRCDIR}/bin/manejador_sem.o: ${SRCDIR}/manejador_sem.cpp ${SRCDIR}/manejador_sem.h

${SRCDIR}/bin/init.o: ${SRCDIR}/init.cpp ${SRCDIR}/init.h ${SRCDIR}/elements.h ${SRCDIR}/manejador_hil.h ${SRCDIR}/manejador_sem.h ${SRCDIR}/manejador_mem.h

${SRCDIR}/bin/reg.o: ${SRCDIR}/reg.cpp ${SRCDIR}/reg.h

${SRCDIR}/bin/ctrl.o: ${SRCDIR}/ctrl.cpp ${SRCDIR}/ctrl.h

${SRCDIR}/bin/rep.o: ${SRCDIR}/rep.cpp ${SRCDIR}/rep.h

${SRCDIR}/bin/parser.o: ${SRCDIR}/parser.cpp ${SRCDIR}/parser.h

${SRCDIR}/bin/stop.o: ${SRCDIR}/stop.cpp ${SRCDIR}/stop.h

${SRCDIR}/bin/elements.o: ${SRCDIR}/elements.cpp ${SRCDIR}/elements.h

clean:
	rm -f ${SRCDIR}/bin/*.o
	rm -f ${SRCDIR}/.~ *~
	rm -f ${SRCDIR}/evaluador
	rm -f ${SRCDIR}/evaluador.exe
	rm -f ./evaluador.exe

	