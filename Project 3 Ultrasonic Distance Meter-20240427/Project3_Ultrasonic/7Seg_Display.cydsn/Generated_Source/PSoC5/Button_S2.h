/*******************************************************************************
* File Name: Button_S2.h  
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

#if !defined(CY_PINS_Button_S2_H) /* Pins Button_S2_H */
#define CY_PINS_Button_S2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Button_S2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Button_S2__PORT == 15 && ((Button_S2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Button_S2_Write(uint8 value);
void    Button_S2_SetDriveMode(uint8 mode);
uint8   Button_S2_ReadDataReg(void);
uint8   Button_S2_Read(void);
void    Button_S2_SetInterruptMode(uint16 position, uint16 mode);
uint8   Button_S2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Button_S2_SetDriveMode() function.
     *  @{
     */
        #define Button_S2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Button_S2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Button_S2_DM_RES_UP          PIN_DM_RES_UP
        #define Button_S2_DM_RES_DWN         PIN_DM_RES_DWN
        #define Button_S2_DM_OD_LO           PIN_DM_OD_LO
        #define Button_S2_DM_OD_HI           PIN_DM_OD_HI
        #define Button_S2_DM_STRONG          PIN_DM_STRONG
        #define Button_S2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Button_S2_MASK               Button_S2__MASK
#define Button_S2_SHIFT              Button_S2__SHIFT
#define Button_S2_WIDTH              1u

/* Interrupt constants */
#if defined(Button_S2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Button_S2_SetInterruptMode() function.
     *  @{
     */
        #define Button_S2_INTR_NONE      (uint16)(0x0000u)
        #define Button_S2_INTR_RISING    (uint16)(0x0001u)
        #define Button_S2_INTR_FALLING   (uint16)(0x0002u)
        #define Button_S2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Button_S2_INTR_MASK      (0x01u) 
#endif /* (Button_S2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Button_S2_PS                     (* (reg8 *) Button_S2__PS)
/* Data Register */
#define Button_S2_DR                     (* (reg8 *) Button_S2__DR)
/* Port Number */
#define Button_S2_PRT_NUM                (* (reg8 *) Button_S2__PRT) 
/* Connect to Analog Globals */                                                  
#define Button_S2_AG                     (* (reg8 *) Button_S2__AG)                       
/* Analog MUX bux enable */
#define Button_S2_AMUX                   (* (reg8 *) Button_S2__AMUX) 
/* Bidirectional Enable */                                                        
#define Button_S2_BIE                    (* (reg8 *) Button_S2__BIE)
/* Bit-mask for Aliased Register Access */
#define Button_S2_BIT_MASK               (* (reg8 *) Button_S2__BIT_MASK)
/* Bypass Enable */
#define Button_S2_BYP                    (* (reg8 *) Button_S2__BYP)
/* Port wide control signals */                                                   
#define Button_S2_CTL                    (* (reg8 *) Button_S2__CTL)
/* Drive Modes */
#define Button_S2_DM0                    (* (reg8 *) Button_S2__DM0) 
#define Button_S2_DM1                    (* (reg8 *) Button_S2__DM1)
#define Button_S2_DM2                    (* (reg8 *) Button_S2__DM2) 
/* Input Buffer Disable Override */
#define Button_S2_INP_DIS                (* (reg8 *) Button_S2__INP_DIS)
/* LCD Common or Segment Drive */
#define Button_S2_LCD_COM_SEG            (* (reg8 *) Button_S2__LCD_COM_SEG)
/* Enable Segment LCD */
#define Button_S2_LCD_EN                 (* (reg8 *) Button_S2__LCD_EN)
/* Slew Rate Control */
#define Button_S2_SLW                    (* (reg8 *) Button_S2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Button_S2_PRTDSI__CAPS_SEL       (* (reg8 *) Button_S2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Button_S2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Button_S2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Button_S2_PRTDSI__OE_SEL0        (* (reg8 *) Button_S2__PRTDSI__OE_SEL0) 
#define Button_S2_PRTDSI__OE_SEL1        (* (reg8 *) Button_S2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Button_S2_PRTDSI__OUT_SEL0       (* (reg8 *) Button_S2__PRTDSI__OUT_SEL0) 
#define Button_S2_PRTDSI__OUT_SEL1       (* (reg8 *) Button_S2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Button_S2_PRTDSI__SYNC_OUT       (* (reg8 *) Button_S2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Button_S2__SIO_CFG)
    #define Button_S2_SIO_HYST_EN        (* (reg8 *) Button_S2__SIO_HYST_EN)
    #define Button_S2_SIO_REG_HIFREQ     (* (reg8 *) Button_S2__SIO_REG_HIFREQ)
    #define Button_S2_SIO_CFG            (* (reg8 *) Button_S2__SIO_CFG)
    #define Button_S2_SIO_DIFF           (* (reg8 *) Button_S2__SIO_DIFF)
#endif /* (Button_S2__SIO_CFG) */

/* Interrupt Registers */
#if defined(Button_S2__INTSTAT)
    #define Button_S2_INTSTAT            (* (reg8 *) Button_S2__INTSTAT)
    #define Button_S2_SNAP               (* (reg8 *) Button_S2__SNAP)
    
	#define Button_S2_0_INTTYPE_REG 		(* (reg8 *) Button_S2__0__INTTYPE)
#endif /* (Button_S2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Button_S2_H */


/* [] END OF FILE */
