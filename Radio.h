#ifndef RADIO_H
#define RADIO_H

#include "ioCC1110.h"


// Global Variabels
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! PRÜFEN!!!!!!!!!!!!!!!!!!
extern const signed short RssiOffset; // 16 Bit 
extern unsigned char XtalCLK_Flag;
extern unsigned char pktRxFlag;
extern unsigned char pktTxFlag;
extern unsigned char RFmode;
extern unsigned char Rxdata[10];               // Received Data stored here
extern unsigned char Txdata[10];



// Declarations:
void InitRadio();
void transmit(unsigned char* Txdata, unsigned char length);
void receive();
signed short convertRssiByte();
void Rx();
void Tx_process(); 
//void Tx_process(unsigned char l)

#define Mode_Tx                           0x01
#define Mode_Rx                           0x02

/*******************************************************************************
 *Radio Registers
 */

// RFIF (0xE9) - RF Interrupt Flags
#define RFIF_IRQ_TXUNF                    0x80
#define RFIF_IRQ_RXOVF                    0x40
#define RFIF_IRQ_TIMEOUT                  0x20
#define RFIF_IRQ_DONE                     0x10
#define RFIF_IRQ_CS                       0x08
#define RFIF_IRQ_PQT                      0x04
#define RFIF_IRQ_CCA                      0x02
#define RFIF_IRQ_SFD                      0x01


// RFIM (0x91) - RF Interrupt Mask
#define RFIM_IM_TXUNF                     0x80
#define RFIM_IM_RXOVF                     0x40
#define RFIM_IM_TIMEOUT                   0x20
#define RFIM_IM_DONE                      0x10
#define RFIM_IM_CS                        0x08
#define RFIM_IM_PQT                       0x04
#define RFIM_IM_CCA                       0x02
#define RFIM_IM_SFD                       0x01


// 0xDF2F: IOCFG2 - Radio Test Signal Configuration (P1_7)
#define IOCFG2_GDO2_INV                   0x40
#define IOCFG2_GDO2_CFG                   0x3F


// 0xDF30: IOCFG1 - Radio Test Signal Configuration (P1_6)
#define IOCFG1_GDO_DS                     0x80
#define IOCFG1_GDO1_INV                   0x40
#define IOCFG1_GDO1_CFG                   0x3F


// 0xDF31: IOCFG0 - Radio Test Signal Configuration (P1_5)
#define IOCFG0_GDO0_INV                   0x40
#define IOCFG0_GDO0_CFG                   0x3F


// 0xDF03: PKTCTRL1 - Packet Automation Control
#define PKTCTRL1_PQT                      0xE0
#define PKTCTRL1_PQT0                     0x20
#define PKTCTRL1_PQT1                     0x40
#define PKTCTRL1_PQT2                     0x80
#define PKTCTRL1_APPEND_STATUS            0x04
#define PKTCTRL1_ADR_CHK                  0x03
#define PKTCTRL1_ADR_CHK0                 0x01
#define PKTCTRL1_ADR_CHK1                 0x02

#define ADR_CHK_NONE                      (0x00)
#define ADR_CHK_NO_BRDCST                 (0x01)
#define ADR_CHK_0_BRDCST                  (0x02)
#define ADR_CHK_0_255_BRDCST              (0x03)


// 0xDF04: PKTCTRL0 - Packet Automation Control
#define PKTCTRL0_WHITE_DATA               0x40
#define PKTCTRL0_PKT_FORMAT               0x30
#define PKTCTRL0_PKT_FORMAT0              0x10
#define PKTCTRL0_PKT_FORMAT1              0x20
#define PKTCTRL0_CC2400_EN                0x08
#define PKTCTRL0_CRC_EN                   0x04
#define PKTCTRL0_LENGTH_CONFIG            0x03
#define PKTCTRL0_LENGTH_CONFIG0           0x01

#define PKT_FORMAT_NORM                   (0x00)
#define PKT_FORMAT_RAND                   (0x02)

#define PKTCTRL0_LENGTH_CONFIG_FIX        (0x00)
#define PKTCTRL0_LENGTH_CONFIG_VAR        (0x01)


// 0xDF05: ADDR - Device Address

// 0xDF06: CHANNR - Channel Number

// 0xDF07: FSCTRL1 - Frequency Synthesizer Control (only bit 0-4 used)

// 0xDF08: FSCTRL0 - Frequency Synthesizer Control

// 0xDF09: FREQ2 - Frequency Control Word, High Byte

// 0xDF0A: FREQ1 - Frequency Control Word, Middle Byte

// 0xDF0B: FREQ0 - Frequency Control Word, Low Byte

// 0xDF0C: MDMCFG4 - Modem configuration

// 0xDF0D: MDMCFG3 - Modem Configuration

// 0xDF0E: MDMCFG2 - Modem Configuration
#define MDMCFG2_DEM_DCFILT_OFF            0x80
#define MDMCFG2_MOD_FORMAT                0x70
#define MDMCFG2_MOD_FORMAT0               0x10
#define MDMCFG2_MOD_FORMAT1               0x20
#define MDMCFG2_MOD_FORMAT2               0x40
#define MDMCFG2_MANCHESTER_EN             0x08
#define MDMCFG2_SYNC_MODE                 0x07
#define MDMCFG2_SYNC_MODE0                0x01
#define MDMCFG2_SYNC_MODE1                0x02
#define MDMCFG2_SYNC_MODE2                0x04

#define MOD_FORMAT_2_FSK                  (0x00 << 4)
#define MOD_FORMAT_GFSK                   (0x01 << 4)
#define MOD_FORMAT_MSK                    (0x07 << 4)

#define SYNC_MODE_NO_PRE                  (0x00)
#define SYNC_MODE_15_16                   (0x01)
#define SYNC_MODE_16_16                   (0x02)
#define SYNC_MODE_30_32                   (0x03)
#define SYNC_MODE_NO_PRE_CS               (0x04)    // CS = carrier-sense above threshold
#define SYNC_MODE_15_16_CS                (0x05)
#define SYNC_MODE_16_16_CS                (0x06)
#define SYNC_MODE_30_32_CS                (0x07)


// 0xDF0F: MDMCG1 - Modem Configuration
#define MDMCG1_FEC_EN                     0x80
#define MDMCG1_NUM_PREAMBLE               0x70
#define MDMCG1_NUM_PREAMBLE0              0x10
#define MDMCG1_NUM_PREAMBLE1              0x20
#define MDMCG1_NUM_PREAMBLE2              0x40
#define MDMCG1_CHANSPC_E                  0x03
#define MDMCG1_CHANSPC_E0                 0x01
#define MDMCG1_CHANSPC_E1                 0x02

#define MDMCG1_NUM_PREAMBLE_2             (0x00 << 4)
#define MDMCG1_NUM_PREAMBLE_3             (0x01 << 4)
#define MDMCG1_NUM_PREAMBLE_4             (0x02 << 4)
#define MDMCG1_NUM_PREAMBLE_6             (0x03 << 4)
#define MDMCG1_NUM_PREAMBLE_8             (0x04 << 4)
#define MDMCG1_NUM_PREAMBLE_12            (0x05 << 4)
#define MDMCG1_NUM_PREAMBLE_16            (0x06 << 4)
#define MDMCG1_NUM_PREAMBLE_24            (0x07 << 4)


// 0xDF10: MDMCFG0 - Modem Configuration

// 0xDF11: DEVIATN - Modem Deviation Setting
#define DEVIATN_DEVIATION_E               0x70
#define DEVIATN_DEVIATION_E0              0x10
#define DEVIATN_DEVIATION_E1              0x20
#define DEVIATN_DEVIATION_E2              0x40
#define DEVIATN_DEVIATION_M               0x07
#define DEVIATN_DEVIATION_M0              0x01
#define DEVIATN_DEVIATION_M1              0x02
#define DEVIATN_DEVIATION_M2              0x04


// 0xDF12: MCSM2 - Main Radio Control State Machine Configuration
#define MCSM2_RX_TIME_RSSI                0x10
#define MCSM2_RX_TIME_QUAL                0x08
#define MCSM2_RX_TIME                     0x07


// 0xDF13: MCSM1 - Main Radio Control State Machine Configuration
#define MCSM1_CCA_MODE                    0x30
#define MCSM1_CCA_MODE0                   0x10
#define MCSM1_CCA_MODE1                   0x20
#define MCSM1_RXOFF_MODE                  0x0C
#define MCSM1_RXOFF_MODE0                 0x04
#define MCSM1_RXOFF_MODE1                 0x08
#define MCSM1_TXOFF_MODE                  0x03
#define MCSM1_TXOFF_MODE0                 0x01
#define MCSM1_TXOFF_MODE1                 0x02

#define MCSM1_CCA_MODE_ALWAYS             (0x00 << 4)
#define MCSM1_CCA_MODE_RSSI0              (0x01 << 4)
#define MCSM1_CCA_MODE_PACKET             (0x02 << 4)
#define MCSM1_CCA_MODE_RSSI1              (0x03 << 4)

#define MCSM1_RXOFF_MODE_IDLE             (0x00 << 2)
#define MCSM1_RXOFF_MODE_FSTXON           (0x01 << 2)
#define MCSM1_RXOFF_MODE_TX               (0x02 << 2)
#define MCSM1_RXOFF_MODE_RX               (0x03 << 2)

#define MCSM1_TXOFF_MODE_IDLE             (0x00 << 0)
#define MCSM1_TXOFF_MODE_FSTXON           (0x01 << 0)
#define MCSM1_TXOFF_MODE_TX               (0x02 << 0)
#define MCSM1_TXOFF_MODE_RX               (0x03 << 0)


// 0xDF14: MCSM0 - Main Radio Control State Machine Configuration
#define MCSM0_FS_AUTOCAL                  0x30

#define FS_AUTOCAL_NEVER                  (0x00 << 4)
#define FS_AUTOCAL_FROM_IDLE              (0x01 << 4)
#define FS_AUTOCAL_TO_IDLE                (0x02 << 4)
#define FS_AUTOCAL_4TH_TO_IDLE            (0x03 << 4)


// 0xDF15: FOCCFG - Frequency Offset Compensation Configuration
#define FOCCFG_FOC_BS_CS_GATE             0x20
#define FOCCFG_FOC_PRE_K                  0x18
#define FOCCFG_FOC_PRE_K0                 0x08
#define FOCCFG_FOC_PRE_K1                 0x10
#define FOCCFG_FOC_POST_K                 0x04
#define FOCCFG_FOC_LIMIT                  0x03
#define FOCCFG_FOC_LIMIT0                 0x01
#define FOCCFG_FOC_LIMIT1                 0x02

#define FOC_PRE_K_1K                      (0x00 << 3)
#define FOC_PRE_K_2K                      (0x02 << 3)
#define FOC_PRE_K_3K                      (0x03 << 3)
#define FOC_PRE_K_4K                      (0x04 << 3)

#define FOC_LIMIT_0                       (0x00)
#define FOC_LIMIT_DIV8                    (0x01)
#define FOC_LIMIT_DIV4                    (0x02)
#define FOC_LIMIT_DIV2                    (0x03)


// 0xDF16: BSCFG - Bit Synchronization Configuration
#define BSCFG_BS_PRE_KI                   0xC0
#define BSCFG_BS_PRE_KI0                  0x40
#define BSCFG_BS_PRE_KI1                  0x80
#define BSCFG_BS_PRE_KP                   0x30
#define BSCFG_BS_PRE_KP0                  0x10
#define BSCFG_BS_PRE_KP1                  0x20
#define BSCFG_BS_POST_KI                  0x08
#define BSCFG_BS_POST_KP                  0x04
#define BSCFG_BS_LIMIT                    0x03
#define BSCFG_BS_LIMIT0                   0x01
#define BSCFG_BS_LIMIT1                   0x02

#define BSCFG_BS_PRE_KI_1K                (0x00 << 6)
#define BSCFG_BS_PRE_KI_2K                (0x01 << 6)
#define BSCFG_BS_PRE_KI_3K                (0x02 << 6)
#define BSCFG_BS_PRE_KI_4K                (0x03 << 6)

#define BSCFG_BS_PRE_KP_1K                (0x00 << 4)
#define BSCFG_BS_PRE_KP_2K                (0x01 << 4)
#define BSCFG_BS_PRE_KP_3K                (0x02 << 4)
#define BSCFG_BS_PRE_KP_4K                (0x03 << 4)

#define BSCFG_BS_LIMIT_0                  (0x00)
#define BSCFG_BS_LIMIT_3                  (0x01)
#define BSCFG_BS_LIMIT_6                  (0x02)
#define BSCFG_BS_LIMIT_12                 (0x03)


// 0xDF17: AGCCTRL2 - AGC Control
#define AGCCTRL2_MAX_DVGA_GAIN            0xC0
#define AGCCTRL2_MAX_LNA_GAIN             0x38
#define AGCCTRL2_MAGN_TARGET              0x07


// 0xDF18: AGCCTRL1 - AGC Control
#define AGCCTRL1_AGC_LNA_PRIORITY         0x40
#define AGCCTRL1_CARRIER_SENSE_REL_THR    0x30
#define AGCCTRL1_CARRIER_SENSE_ABS_THR    0x0F


// 0xDF19: AGCCTRL0 - AGC Control
#define AGCCTRL0_HYST_LEVEL               0xC0
#define AGCCTRL0_WAIT_TIME                0x30
#define AGCCTRL0_AGC_FREEZE               0x0C
#define AGCCTRL0_FILTER_LENGTH            0x03


// 0xDF1A: FREND1 - Front End RX Configuration
#define FREND1_LNA_CURRENT                0xC0
#define FREND1_LNA2MIX_CURRENT            0x30
#define FREND1_LODIV_BUF_CURRENT_RX       0x0C
#define FREND1_MIX_CURRENT                0x03


// 0xDF1B: FREND0 - Front End TX Configuration
#define FREND0_LODIV_BUF_CURRENT_TX       0x30


// 0xDF1C: FSCAL3 - Frequency Synthesizer Calibration
#define FSCAL3_FSCAL3                     0xC0
#define FSCAL3_CHP_CURR_CAL_EN            0x30


// 0xDF1D: FSCAL2 - Frequency Synthesizer Calibration
#define FSCAL2_VCO_CORE_H_EN              0x20
#define FSCAL2_FSCAL2                     0x1F


// 0xDF1E: FSCAL1 - Frequency Synthesizer Calibration

// 0xDF1F: FSCAL0 - Frequency Synthesizer Calibration

// 0xDF25: TEST0 - Various Test Settings


// RFST (0xE1) - RF Strobe Commands
#define RFST_SFSTXON                      0x00
#define RFST_SCAL                         0x01
#define RFST_SRX                          0x02
#define RFST_STX                          0x03
#define RFST_SIDLE                        0x04
#define RFST_SNOP                         0x05
// 0xDF3B: MARCSTATE - Main Radio Control State Machine State
#define MARCSTATE_MARC_STATE              0x1F
#define MARC_STATE_SLEEP                  0x00
#define MARC_STATE_IDLE                   0x01
#define MARC_STATE_VCOON_MC               0x03
#define MARC_STATE_REGON_MC               0x04
#define MARC_STATE_MANCAL                 0x05
#define MARC_STATE_VCOON                  0x06
#define MARC_STATE_REGON                  0x07
#define MARC_STATE_STARTCAL               0x08
#define MARC_STATE_BWBOOST                0x09
#define MARC_STATE_FS_LOCK                0x0A
#define MARC_STATE_IFADCON                0x0B
#define MARC_STATE_ENDCAL                 0x0C
#define MARC_STATE_RX                     0x0D
#define MARC_STATE_RX_END                 0x0E
#define MARC_STATE_RX_RST                 0x0F
#define MARC_STATE_TXRX_SWITCH            0x10
#define MARC_STATE_RX_OVERFLOW            0x11
#define MARC_STATE_FSTXON                 0x12
#define MARC_STATE_TX                     0x13
#define MARC_STATE_TX_END                 0x14
#define MARC_STATE_RXTX_SWITCH            0x15
#define MARC_STATE_TX_UNDERFLOW           0x16



/***********************************************************************/


#endif