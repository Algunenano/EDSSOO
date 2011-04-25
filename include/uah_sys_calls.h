/* 
 * File:   uah_sys_calls.h
 * Author: Algunenano
 *
 * Created on April 21, 2011, 10:35 PM
 */

#ifndef UAH_SYS_CALLS_H
#define	UAH_SYS_CALLS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "uah_arch_ps.h"

    void uah_init_traps (void);

#define _NR_UAH_pause           0
#define _NR_UAH_exit            1
#define _NR_UAH_open            2
#define _NR_UAH_close           3
#define _NR_UAH_create_process  4


#define _UAH_API_sys_call0(type,name)\
type name(void){\
    type auxRET;\
    UAH_REG_D0=_NR_##name;\
    _EMU_TRAP(0);\
    auxRET=(type)UAH_REG_D0;\
    return (type)auxRET;\
}

#define _UAH_API_sys_call1(type,name,P1type,P1name)\
type name(P1type P1name){\
    type auxRET;\
    UAH_REG_D0=_NR_##name;\
    UAH_REG_D1=(long)P1name;\
    _EMU_TRAP(0);\
    auxRET=(type)UAH_REG_D0;\
    return (type)auxRET;\
}

#define _UAH_API_sys_call2(type,name,P1type,P1name,P2type,P2name)\
type name(P1type P1name, P2type P2name){\
    type auxRET;\
    UAH_REG_D0=_NR_##name;\
    UAH_REG_D1=(long)P1name;\
    UAH_REG_D2=(long)P2name;\
    _EMU_TRAP(0);\
    auxRET=(type)UAH_REG_D0;\
    return (type)auxRET;\
}

#define _UAH_API_sys_call3(type,name,P1type,P1name,P2type,P2name,P3type,P3name)\
type name(P1type P1name, P2type P2name, P3type P3name){\
    type auxRET;\
    UAH_REG_D0=_NR_##name;\
    UAH_REG_D1=(long)P1name;\
    UAH_REG_D2=(long)P2name;\
    UAH_REG_D3=(long)P3name;\
    _EMU_TRAP(0);\
    auxRET=(type)UAH_REG_D0;\
    return (type)auxRET;\
}


#ifdef	__cplusplus
}
#endif

#endif	/* UAH_SYS_CALLS_H */

