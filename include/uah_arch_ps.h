/* 
 * File:   uah_arch_ps.h
 * Author: Algunenano
 *
 * Created on April 21, 2011, 5:49 PM
 */

#ifndef UAH_ARCH_PS_H
#define	UAH_ARCH_PS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define _EMU_IRQ_VECTOR_LENGHT 64
#define _EMU_IRQ_VECTOR_INVALID_INSTRUCTION 16
#define _EMU_IRQ_VECTOR_BUS_ERROR 17
#define _EMU_IRQ_VECTOR_TRAP0 24
#define _EMU_IRQ_VECTOR_INT0 0

    /* Definición del vector de interrupciones */
    typedef void (*_EMU_IRQ_VECTOR[_EMU_IRQ_VECTOR_LENGHT]) (void);

        /* Importar la tabla de interrupciones */
    extern _EMU_IRQ_VECTOR _EMU_IRQ_VECTOR_TABLE;


    void _EMU_TRAP (int trapNum);
    void _EMU_HW_IRQ (int vectorNum);


    /* REGISTERS */
    /* D0: Contiene el número que identifica las llamadas al sistema
     y retorna el valor devuelto por las llamadas al sistema*/
    extern long UAH_REG_D0;
    /* Di {i:1..7}: Registro que contiene el i-parámetro de la llamada*/
    extern long UAH_REG_D1;
    extern long UAH_REG_D2;
    extern long UAH_REG_D3;
    extern long UAH_REG_D4;
    extern long UAH_REG_D5;
    extern long UAH_REG_D6;
    extern long UAH_REG_D7;



#ifdef	__cplusplus
}
#endif

#endif	/* UAH_ARCH_PS_H */

