
#include "cmd.h"
#include "uart.h"
#include "GPS_config_io.h"

uint8_t Data_Rx = 0;
uint8_t msg[50];


uint8_t Send_cmd(char *str,char *Matched_str)
{
	int len = strlen(str);  
	  
	   // store value of first character
    int ans = (int)str[0];

    for (int i = 1; i < len; i++) {
        // Traverse string to find the XOR
        ans = (ans ^ (int)str[i]);
    } 
	
	sprintf(msg,"%c""%s*""%X\r\n",'$',str,ans);
	printk("TX : %s",msg);
	Data_Rx = 1;
	
	uart_tx(uart ,msg,sizeof(msg),RECEIVE_TIMEOUT);

	if(uart_rx_enable(uart ,Rxbuf,sizeof(Rxbuf),SYS_FOREVER_US)>0)
	{
		Data_Rx=0;
	}

	while(Data_Rx ==0)
	{
		k_msleep(1);
	}
	
	if(strcmp((char *)Rxbuf,Matched_str) && Data_Rx == 1 )
	{
		printk("RX1 : %s",Rxbuf);
		memset(Rxbuf,0,sizeof(Rxbuf));
		Data_Rx = 0;
		return 0;
	}
	else if(Data_Rx == 1)
	{
		printk("RX2 : %s",Rxbuf);
		Data_Rx=0;
		return 1;
	}
			
}
uint8_t gps_auto_start(void)
{

	gpio_pin_set_dt(&AUTO_START,LOW);
	k_msleep(100);
	gpio_pin_set_dt(&AUTO_START,HIGH);
}

uint8_t gps_start_cmd(char gpsmode,char profile)
{
	uint8_t st_buff[30];
	sprintf(st_buff, "%s,%c,%c","PEPSSTR",gpsmode,profile);
	Send_cmd(st_buff,",STR,");
	return 0;

}

uint8_t gps_check_version_cmd(char request){

	uint8_t version_buff[15];
	sprintf(version_buff, "%s,%c","PEPSIVE",request);
	Send_cmd(version_buff,"RVE");
	k_msleep(100);
	return 0;
 }

uint8_t gps_stop_cmd(char stopmode)
{
	uint8_t st_buff[30];
	sprintf(st_buff, "%s,%c","PEPSSTP",stopmode);
	Send_cmd(st_buff,"STP");
	k_msleep(100);
	return 0;
}

uint8_t gps_baudrate_cmd(const char* baudrate)
{
	uint8_t baud_buff[30];
	sprintf(baud_buff, "%s,%s","PEPSURT",baudrate);
	Send_cmd(baud_buff,"URT");
	return 0;
}


uint8_t gps_reset_cmd(const char resetmode)
{
	uint8_t stop_buff[10];
	sprintf(stop_buff, "%s,%c","PEPSRST",resetmode);
	Send_cmd(stop_buff,"RST");
	k_msleep(50);

	return 0;
}

uint8_t gps_gns_cmd(const char QZSS,const char GLONASSBDS){

	uint8_t gns_buff[30];
	sprintf(gns_buff, "%s,%c,%c","PEPSGNS",QZSS,GLONASSBDS);
	Send_cmd(gns_buff,"GNS");
	k_msleep(100);
	return 0;
}

uint8_t gps_pps_cmd(const char control,const char synctype ,const char* offset)
{
	uint8_t pps_buff[30];
	sprintf(pps_buff, "%s,%c,%c,%s","PEPSPPS",control,synctype,offset);
	Send_cmd(pps_buff,"PPS");
	k_msleep(100);
	return 0;
}

uint8_t  gps_msk_cmd(const char snr_mask,const char* elv_mask)
{
	uint8_t msk_buff[30];
	sprintf(msk_buff, "%s,%c,%s","PEPSMSK",snr_mask,elv_mask);
	Send_cmd(msk_buff,"MSK");
	k_msleep(100);
	return 0;

}


uint8_t gps_nmea_cmd(const char *type , const char status){

	uint8_t nmea_buff[30];
	sprintf(nmea_buff, "%s,%s,%c","PEPSNME",type,status);
	Send_cmd(nmea_buff,"NME");
	k_msleep(100);
	return 0;

}

uint8_t gps_enm_cmd(char status){

	uint8_t enm_buff[20];
	sprintf(enm_buff, "%s,%c","PEPSENM,RTI",status);
	Send_cmd(enm_buff,"ENM");
	k_msleep(100);
}

uint8_t gps_init_pos_cmd(const char pos_status,const char* latitude,const char* longitude,const char* altitude,const char* possigma){
uint8_t pos_buff[60];
	sprintf(pos_buff, "%s,%c,%s,%s,%s,%s","PEPSPOS",pos_status,latitude,longitude,altitude,possigma);
	Send_cmd(pos_buff,"POS");
	k_msleep(100);

return 0;
}

uint8_t gps_set_time_cmd(const char time_status,const char *hhmmss,const char *date,const char * month,const char * year){
	uint8_t time_buff[50];
	sprintf(time_buff, "%s,%c,%s,%s,%s,%s","PEPSTIM",time_status,hhmmss,date,month,year);
		Send_cmd(time_buff,"TIM");
		k_msleep(100);

	return 0;
}
uint8_t gps_sls_cmd(const char *utc_offset,const char level){
		uint8_t sls_buff[30];
		sprintf(sls_buff, "%s,%s,%c","PEPSSLS",utc_offset,level);
		Send_cmd(sls_buff,"SLS");
		k_msleep(100);

}

uint8_t gps_clr_cmd(const char clear_status){
		uint8_t clr_buff[15];
		sprintf(clr_buff, "%s,%c","PEPSCLR",clear_status);
		Send_cmd(clr_buff,"CLR");
		k_msleep(100);

}

uint8_t gps_sav_cmd(char save_status){
		uint8_t sav_buff[15];
		sprintf(sav_buff, "%s,%c","PEPSSAV",save_status);
		Send_cmd(sav_buff,"SAV");
		k_msleep(100);
return 0;
}

uint8_t gps_hwc_cmd(char lna_gain,char extlna_ctrl,const char rtc_clk){

	uint8_t hwc_buff[30];

		sprintf(hwc_buff, "%s,%c,%c,%c","PEPSHWC",lna_gain,extlna_ctrl,rtc_clk);
		Send_cmd(hwc_buff,"HWC");
		k_msleep(100);
}

uint8_t gps_icf_cmd(const char* type){

uint8_t icf_buff[20];

		sprintf(icf_buff, "%s,%s","PEPSICF",type);
		Send_cmd(icf_buff,",");
		k_msleep(100);

	return 0;
}

uint8_t gps_ibe_cmd(const char* hhmmss,const char* date,const char * month , const char* year, 
	const  char pos_setting,const char* elevation,const char* latitide,const char* longitude,const char* altitude){

uint8_t ibe_buff[100];

		sprintf(ibe_buff, "%s,%s,%s,%s,%s,%c,%s,%s,%s,%s","PEPSIBE",hhmmss,date,month,year,pos_setting,elevation,latitide,longitude,altitude);
		Send_cmd(ibe_buff,"IBE");
		k_msleep(100);

	}


uint8_t gps_qzs_cmd(const char* qzss_pattern){

uint8_t qzs_buff[20];

		sprintf(qzs_buff, "%s,%s","PEPSQZS",qzss_pattern);
		Send_cmd(qzs_buff,",");
		k_msleep(100);

	return 0;
}

uint8_t gps_psm_cmd(const char ttff_setting,const char sensitivity_setting,
								const char Reserved_1,const char Reserved_2,const char Reserved_3){
uint8_t psm_buff[20];

		sprintf(psm_buff, "%s,%c,%c,%c,%c,%c","PEPSPSM",ttff_setting,sensitivity_setting,Reserved_1,Reserved_2,Reserved_3);
		Send_cmd(psm_buff,"XXX");
		k_msleep(100);

	return 0;



}
