#ifndef CMD_H
#define CMD_H

#include <zephyr/drivers/uart.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>


extern uint8_t Data_Rx;
extern uint8_t msg[50];

uint8_t Send_cmd(char *str,char *Matched_str);
/**
 * @brief auto start command
 *
 */
uint8_t gps_auto_start(void);
/**
 * @brief positioning start command(STR)
 
 * @param gpsmode - range: C-H
 * 					default : H
 * 					Start mode C: Cold start H: Hot start.
 * @param profile - range: 0~2
 * 					 default : 1 
					0: Normal
					1: LowPower(LowPowerProfile:LP) 
					2: LowPower(AccuracyProfile:AP) 

 */
uint8_t gps_start_cmd(char gpsmode,char profile);
/**
 * @brief Positioning stop command(STP) - BBData save setting at stop
 * @param stopmode  -range :0~2
 * 					default : -
					0: don’t save BBData
					1: Save BBData in RAM 
					2: Save BBData in RAM and Flash(*)

*/
uint8_t gps_stop_cmd(char stopmode);
/**
 * @brief Reset and reboot command
 * @param resetmode  - range :0
 * 						default : -
 * 					0: Delete BBDATA and setting data from Flash and RAM and restart Default

*/
uint8_t gps_reset_cmd(const char  resetmode);
/**
 * @brief Satellite system selection command(GNS)
 *
 * @param QZSS - range :0~1
 * 				default : 1
 * 				QZSS setting 
				0: don’t use QZSS(don’t search QZSS) 
				1: use QZSS(*1)
 * 
 * @param GLONASSBDS - range :0~2
 * 						default : 0
 * 						GLONASS,BDS setting
						0: don’t use GLONASS and BDS
						1: use GLONASS
						2: use BDS (*2)

 */
uint8_t gps_gns_cmd(const char QZSS,const char GLONASSBDS);
/**
 * @brief PPS(Pulse per Second) setting command
 *
 * @param control - range :0~1
 * 					default : 0
 * 					PPS mode
					0: Disable PPS
					1: Normal-PPS
 * 
 * @param synctype - range :0~1
 * 					default : 0
 * 					Synchronization time
					0: GPS-Time
					1: UTC
*				
* @param offset  - range :-1000000 ~ 1000000
					default : 0
					Cable offset [nsec]
				 + is late, - is early

 */
uint8_t gps_pps_cmd(const char control,const char synctype ,const char* offset);
/**
 * @brief Satellite mask setting command
 *
 * @param snr_mask - range :0~99
 * 					default : 0
 * 					Use SNR satellites above the specified threshold for positioning
 * 
 * @param elv_mask - range :0~99
 * 					default : 0
 * 					Use elevation satellites above the specified threshold for positioning.

 */
uint8_t  gps_msk_cmd(const char snr_mask,const char* elv_mask);
/**
 * @brief Standard NMEA sentence output setting command
 *
 * @param type - range : -
 * 				default : - 
 * 				Sentence name to change output
				GGA,GLL,GNS,GSA,GSV,RMC,VTG,ZDA,ALL
				※ALL is all standard NMEA sentences
 * 
 * @param status - range :0~1
 * 					default : -
 * 					Output on / off
					0: Output off
					1: Output on
					Output interval fixed at 1 second interval

 */
uint8_t gps_nmea_cmd(const char *type , const char status);
/**
 * @brief Epson original NMEA sentence output setting command
 * 
 * @param status - range : 0~1 
 * 					default : -
 * 					Output on / off
					0: Output off
					1: Output on
*/
uint8_t gps_enm_cmd(char status);
/**
 * @brief Initial position setting command
 * @param pos_status  - range 0~1
 * 						default : -
					0: The higher reliability is used as the position information in comparison with the reliability of the GNSS-IC holding position
					1: Force use of Input position information
 * 
 * @param latitude   - range : -90.00000 ~ 90.00000
 * 					default : -
					Latitude of initial position [degree]
					Positive values are north latitude,
					negative numbers are south latitude
 * 
 * @param longitude  - range : 180.00000 ~ 180.00000
 * 					default : -
 * 					Longitude of initial position [degree]
					Positive values are east longitude,
					negative numbers are west longitude
 * 	
 * @param  altitude - range : -1000.00 ～ 18000.00
 * 					default : -
 * 				 -Altitude above sea level in initial position [ｍ]
 * 
 * @param possigma - range : 0～300
 * 					default : -
 * 					Position reliability [km]
					Reliability of input initial position. In the case of position reliability within 150km, it will be hot start depending on the condition
 * 

*/
uint8_t gps_init_pos_cmd(const char pos_status,const char* latitude,const char* longitude,const char* altitude,const char* possigma);
/**
 * @brief Time setting command
 * @param time_status  - range 0~2
 * 						default : -
 * 						 State of specified time
						0: Low reliability time
						1: High reliability time (Less than
						10 seconds error)
						2: Forced time setting
							(*1)
 * 
 * @param hhmmss   - range - hh:00～23  mm:00～59  ss:00～59
 * 					default :  000000
					* UTC time
					hh: UTC hour
					mm: UTC minute
					ss: UTC sec
 * 
 * @param date  - range - 01～31
 * 					default :  01
 * 				   - UTC day
 * 	
 * @param  month - range - 01～12
 * 					default :  01
 * 				    - UTC month
 * 
 * @param year - range - 2000～2099
 * 					default :  2019
 * 				    - UTC year

*/
uint8_t gps_set_time_cmd(const char time_status,const char *hhmmss,const char *date,const char * month,const char * year);
/**
 * @brief Leap second setting command
 *
 * @param utc_offset - range :  -99～99
 * 						default :  18
 * 						Leap second
 * 
 * @param level - 	range : L,M,H
 * 					default :  L
 * 					Setting leap second level.

 */
uint8_t gps_sls_cmd(const char *utc_offset,const char level);
/**
 * @brief UART baudrate change command
 *
 * @param baudrate - range : 4800,9600,19200,38400,57600,115200,230400
 * 					default :  9600
 * 					UART baudrate[bps]
 */
uint8_t gps_baudrate_cmd(const char* baudrate);
/**
 * @brief GNSS-IC information clear command
 *
 * @param clear_status - range : 1~7
 * 						default :  -
 * 						Information to clear
						Bit0: Clear BBDATA(RAM and Flash)
						Bit1: Clear GNSS-IC setting(RAM
						and Flash)
						Bit2: Clear UART baudrate （*）
If clear_status = 7 is specified, the factory default settings (all values are default settings) will be set.
* 
 */
uint8_t  gps_clr_cmd(const char clear_status);
/**
 * @brief GNSS-IC information save command
 *
 * @param save_status - range : 1~3
 * 						default :  -
 * 						Information stored in Flash
						Bit0: Save BBDATA (*)
						Bit1: Save GNSS-IC setting
* 
 */
uint8_t  gps_sav_cmd(char save_status);
/**
 * @brief Hardware setting command
 *
 * @param lna_gain - range : 0~1
* 						default :  0
* 						Set Gain of internal LNA
						0: Internal LNA power on
						1: Internal LNA power off

 *@param extlna_ctrl - range : 0~1
						default :  0
						0: extLNA control (positioning synchronization)
						→ High during positioning operation,Low otherwise
						1: extLNA control (positioning operation + LowPower synchronization)
						→ Hi (Low Power interlocking) during
						positioning operation, Low otherwise


 *@param rtc_clk - range : 0~1
					default :  0
					Set the RTC clock type
					0: Use crystal unit for RTC clock input
					1: Use crystal oscillator for RTC clock
					input

* 
 */
uint8_t gps_hwc_cmd(char lna_gain,char extlna_ctrl,const char rtc_clk);
/**
 * @brief Version request command
 * @param request   - range :0
 * 					default :  0   
 * 					0: Version request

*/
uint8_t gps_check_version_cmd(char request);
/**
 * @brief GNSS-IC setting information request command
 * @param type   - range :RGN,RPP,RMK,RPS,RQS,ALL
 * 					default :  -    
 * 				Specify one of RGN, RPP, RMK,RPS,RQS,ALL. When ALL is specified, all setting information is read and output

*/
uint8_t gps_icf_cmd(const char* type);
/**
 * @brief Positioning operation setting command
 * @param ttff_setting   - range :0~1 
 * 							default :  0 
 * 							TTFF priority positioning setting
							0: Disable
							1: Enable
 *
 * @param sensitivity_setting - range :0~1
 * 								default :  0
 * 								sensitivity_setting※1
								0:High
								1:Low

 * @param Reserved_1  - range :0
						default :  -
 * 						0:Reserved
 
 * @param Reserved_2 - range :0
						default :  -
 * 						0:Reserved
 * 
 * @param Reserved_3 - range :0
 * 						default :  -
 * 						0:Reserved
*/
uint8_t gps_psm_cmd(const char ttff_setting,const char sensitivity_setting,
								const char Reserved_1,const char Reserved_2,const char Reserved_3);
/**
 * @brief Valid ephemeris number request Command

 * @param hhmmss   - range : hh:00～23  mm:00～59  ss:00～59 
                    default :  -
 * 
					* UTC time
					hh: UTC hour
					mm: UTC minute
					ss: UTC sec
 * 
 * @param date  - range : 01～31
 * 				 default :  -
 * 				- UTC day
 * 	
 * @param  month - range : 01～12
 * 				 default :  -
 * 				 - UTC month
 * 
 *@param year - range : 2000～2099
 * 				default :  -
 * 				- UTC year
 * 
 * @param pos_setting  - range : 0~2
 * 						default :  -
					reference position setting for calculating the elevation angle of the satellite (*3)
					0:use position in BBData
					1:input with IBE command
					2:not use elevation mask
					(Only ephemeris validity)
 * 
 *@param elevation - range : 0~90
 * 					default :  -
					Elevation mask value [degree]※3
 * 
 * @param latitude   - range : -90.00000 ~ 90.00000
 * 					default :  -
 * 					Latitude of reference position [degree]
					Positive values are north latitude,
					negative numbers are south latitude
 * 
 * @param longitude  - range : 180.00000 ~ 180.00000
 * 						default :  -
 * 					Longitude of reference position [degree]
					Positive values are east longitude,
					negative numbers are west longitude
 * 	
 * @param  altitude - range : -1000.00 ～ 18000.00
 * 					default :  -
 * 				 -Altitude above sea level in reference position [ｍ]

*/

uint8_t gps_ibe_cmd(const char* hhmmss,const char* date,const char * month , const char* year, 
	char pos_setting,const char* elevation,const char* latitide,const char* longitude,const char* altitude);
/**
 * @brief QZSS search setting command
 * @param qzss_pattern   - range :0-03ff    default :0047
 * 					Bit0:
					0:Disable PRN193 for positioning
					1:Enable PRN193 for positioning

					Bit1:
					0:Disable PRN194 for positioning
					1:Enable PRN194 for positioning

					Bit2:
					0:Disable PRN195 for positioning
					1:Enable PRN195 for positioning

					Bit3:
					0:Disable PRN196 for positioning
					1:Enable PRN196 for positioning

					Bit4:
					0:Reserved

					Bit5:
					0:Reserved

					Bit6:
					0:Disable PRN199 for positioning
					1:Enable PRN199 for positioning

					Bit7:
					0:Reserved

					Bit8:
					0:Reserved

					Bit9:
					0:Reserved

*/
uint8_t gps_qzs_cmd(const char* qzss_pattern);



#endif  // CONFIG_H
