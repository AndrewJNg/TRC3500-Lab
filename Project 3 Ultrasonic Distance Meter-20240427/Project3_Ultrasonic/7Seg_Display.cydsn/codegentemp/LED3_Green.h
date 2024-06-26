/*******************************************************************************
* File Name: LED3_Green.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LED3_Green_H) /* Pins LED3_Green_H */
#define CY_PINS_LED3_Green_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LED3_Green_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LED3_Green__PORT == 15 && ((LED3_Green__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LED3_Green_Write(uint8 value);
void    LED3_Green_SetDriveMode(uint8 mode);
uint8   LED3_Green_ReadDataReg(void);
uint8   LED3_Green_Read(void);
void    LED3_Green_SetInterruptMode(uint16 position, uint16 mode);
uint8   LED3_Green_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LED3_Green_SetDriveMode() function.
     *  @{
     */
        #define LED3_Green_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LED3_Green_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LED3_Green_DM_RES_UP          PIN_DM_RES_UP
        #define LED3_Green_DM_RES_DWN         PIN_DM_RES_DWN
        #define LED3_Green_DM_OD_LO           PIN_DM_OD_LO
        #define LED3_Green_DM_OD_HI           PIN_DM_OD_HI
        #define LED3_Green_DM_STRONG          PIN_DM_STRONG
        #define LED3_Green_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LED3_Green_MASK               LED3_Green__MASK
#define LED3_Green_SHIFT              LED3_Green__SHIFT
#define LED3_Green_WIDTH              1u

/* Interrupt constants */
#if defined(LED3_Green__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LED3_Green_SetInterruptMode() function.
     *  @{
     */
        #define LED3_Green_INTR_NONE      (uint16)(0x0000u)
        #define LED3_Green_INTR_RISING    (uint16)(0x0001u)
        #define LED3_Green_INTR_FALLING   (uint16)(0x0002u)
        #define LED3_Green_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LED3_Green_INTR_MASK      (0x01u) 
#endif /* (LED3_Green__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED3_Green_PS                     (* (reg8 *) LED3_Green__PS)
/* Data Register */
#define LED3_Green_DR                     (* (reg8 *) LED3_Green__DR)
/* Port Number */
#define LED3_Green_PRT_NUM                (* (reg8 *) LED3_Green__PRT) 
/* Connect to Analog Globals */                                                  
#define LED3_Green_AG                     (* (reg8 *) LED3_Green__AG)                       
/* Analog MUX bux enable */
#define LED3_Green_AMUX                   (* (reg8 *) LED3_Green__AMUX) 
/* Bidirectional Enable */                                                        
#define LED3_Green_BIE                    (* (reg8 *) LED3_Green__BIE)
/* Bit-mask for Aliased Register Access */
#define LED3_Green_BIT_MASK               (* (reg8 *) LED3_Green__BIT_MASK)
/* Bypass Enable */
#define LED3_Green_BYP                    (* (reg8 *) LED3_Green__BYP)
/* Port wide control signals */                                                   
#define LED3_Green_CTL                    (* (reg8 *) LED3_Green__CTL)
/* Drive Modes */
#define LED3_Green_DM0                    (* (reg8 *) LED3_Green__DM0) 
#define LED3_Green_DM1                    (* (reg8 *) LED3_Green__DM1)
#define LED3_Green_DM2                    (* (reg8 *) LED3_Green__DM2) 
/* Input Buffer Disable Override */
#define LED3_Green_INP_DIS                (* (reg8 *) LED3_Green__INP_DIS)
/* LCD Common or Segment Drive */
#define LED3_Green_LCD_COM_SEG            (* (reg8 *) LED3_Green__LCD_COM_SEG)
/* Enable Segment LCD */
#define LED3_Green_LCD_EN                 (* (reg8 *) LED3_Green__LCD_EN)
/* Slew Rate Control */
#define LED3_Green_SLW                    (* (reg8 *) LED3_Green__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LED3_Green_PRTDSI__CAPS_SEL       (* (reg8 *) LED3_Green__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LED3_Green_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LED3_Green__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LED3_Green_PRTDSI__OE_SEL0        (* (reg8 *) LED3_Green__PRTDSI__OE_SEL0) 
#define LED3_Green_PRTDSI__OE_SEL1        (* (reg8 *) LED3_Green__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LED3_Green_PRTDSI__OUT_SEL0       (* (reg8 *) LED3_Green__PRTDSI__OUT_SEL0) 
#define LED3_Green_PRTDSI__OUT_SEL1       (* (reg8 *) LED3_Green__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LED3_Green_PRTDSI__SYNC_OUT       (* (reg8 *) LED3_Green__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LED3_Green__SIO_CFG)
    #define LED3_Green_SIO_HYST_EN        (* (reg8 *) LED3_Green__SIO_HYST_EN)
    #define LED3_Green_SIO_REG_HIFREQ     (* (reg8 *) LED3_Green__SIO_REG_HIFREQ)
    #define LED3_Green_SIO_CFG            (* (reg8 *) LED3_Green__SIO_CFG)
    #define LED3_Green_SIO_DIFF           (* (reg8 *) LED3_Green__SIO_DIFF)
#endif /* (LED3_Green__SIO_CFG) */

/* Interrupt Registers */
#if defined(LED3_Green__INTSTAT)
    #define LED3_Green_INTSTAT            (* (reg8 *) LED3_Green__INTSTAT)
    #define LED3_Green_SNAP               (* (reg8 *) LED3_Green__SNAP)
    
	#define LED3_Green_0_INTTYPE_REG 		(* (reg8 *) LED3_Green__0__INTTYPE)
#endif /* (LED3_Green__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LED3_Green_H */


/* [] END OF FILE */
