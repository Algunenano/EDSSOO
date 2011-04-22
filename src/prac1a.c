/*
 * File:   prac1a.c
 * Author: Algunenano
 *
 * Created on April 22, 2011, 1:57 AM
 */

#include "prac1a.h"
#include "uah_arch_ps.h"
#include "uah_set_up.h"

#include <stdlib.h>

int main (void) {
    uah_set_up();
    _EMU_TRAP(0);
    _EMU_HW_IRQ(0);
    _EMU_TRAP(6);
    _EMU_HW_IRQ(100);

    return (EXIT_SUCCESS);
}
