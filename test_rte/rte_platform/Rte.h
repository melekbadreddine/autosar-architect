/********************************************************************
 * RTE root header.
 * Provides the platform / RTE base definitions required by the
 * generated RTE headers (Rte_Type.h) and the SWC code.
 ********************************************************************/

#ifndef RTE_H
#define RTE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* AUTOSAR standard return type */
typedef unsigned char Std_ReturnType;

/* Standard return values */
#define E_OK       ((Std_ReturnType)0x00u)
#define E_NOT_OK   ((Std_ReturnType)0x01u)

/* RTE operational error values */
#define RTE_E_OK                        ((Std_ReturnType)0x00u)
#define RTE_E_NEVER_RECEIVED            ((Std_ReturnType)0x30u)
#define RTE_E_TRANSMIT_ACK              ((Std_ReturnType)0x31u)
#define RTE_E_NO_DATA                   ((Std_ReturnType)0x32u)
#define RTE_E_QUEUE_FULL                ((Std_ReturnType)0x33u)
#define RTE_E_OVERFLOW                  ((Std_ReturnType)0x34u)
#define RTE_E_LOST_DATA                 ((Std_ReturnType)0x35u)
#define RTE_E_LIMIT                     ((Std_ReturnType)0x36u)
#define RTE_E_MAX_AGE_EXCEEDED          ((Std_ReturnType)0x37u)
#define RTE_E_INVALID                   ((Std_ReturnType)0x38u)
#define RTE_E_COM_ALARM_EXPIRED         ((Std_ReturnType)0x39u)

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* RTE_H */
