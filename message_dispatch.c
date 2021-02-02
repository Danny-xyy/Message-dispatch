//=============================================================================
// FILE: message_dispatch.c
//
// DESCRIPTION:
// Code assignment of applying 2021 Summer Intern - Embedded Software Engineer at braincorp
//
// AUTHORS:
//   Yiyang Xu yx2082@nyu.edu 2021,02
//
// Copyright 2021, Yiyang Xu, All rights reserved.
//=============================================================================

#include<stdio.h>
#include<stdint.h>

/*

	Defines the display and motor functions
	"Write function declarations for these functions but empty function bodies are fine"
	
*/
void display_message()
{
	printf("You've received a display message!!!\n\n");
 } 
 
void update_motor()
{
	printf("Updating motor message!!!\n\n");
}

/*

	Defines the data structure of display and motor message
	
	The packet format uses little-endian data
	
	message_data for display messages is a ASCII string of length message_length
	message_data for motor messages is composed of the following data structure:
	forward_back (float32, positions 0 to 3)
	left_right (float32, positions 4 to 7)
	
	Since the length of the display message is two bytes, the maximum length of data is 2^16 which is 65536
	
*/

#if __BYTE_ORDER != __LITTLE_ENDIAN
   #error(__BIG_ENDIAN is not supported)
#endif

typedef struct {
   uint8_t id;
   uint8_t type;
   uint16_t len;
   uint8_t data[65535];
} display;

// motor message type
typedef struct {
   uint8_t id;
   uint8_t type;
   uint16_t len;
   float forward_back;
   float left_right;
} motor;

/*

	Defines Global variables
	
	message_type values:
	0x34: display message
	0x80: motor message
	
*/

#define TYPE_DISPLAY 0x34
#define TYPE_MOTOR 0x80

uint8_t display_packet[] = {0x1, 0x34, 0x05, 0x0, 0x48, 0x65, 0x6c, 0x6c, 0x6f};

uint8_t motor_packet[] = {0x2, 0x80, 0x08, 0x0, 0x0, 0x0, 0x80, 0x3f, 0x0, 0x0, 0x0, 0xbf};

uint8_t span_packet[] = {0x3, 0x99, 0x08, 0x0, 0x0, 0x0, 0x80, 0x3f, 0x0, 0x0, 0x0, 0xbf};

uint8_t display_packet2[] = {0x4, 0x34, 0x05, 0x0, 0x48, 0x65, 0x6c, 0x6c, 0x6f};

uint8_t motor_packet2[] = {0x5, 0x80, 0x08, 0x0, 0x0, 0x0, 0x80, 0x3f, 0x0, 0x0, 0x0, 0xbf};
/*
	
	FUNCTION: main
	
	DESCRIPTION:
	Simulation of dispatching a mixed packet containing display and motor messages.
	Add a span packet.
	
*/
int main(){
	printf("Dispatching messages......\n\n");
	
	unsigned char* mixed_packet[] = {display_packet,motor_packet,span_packet,display_packet2,motor_packet2};
   
   // printf("Testing display data %x\n", mixed_packet[0][1]);

 	int i=0,display_count = 0, motor_count=0 ,span_count = 0;
	
	int message_length = sizeof(mixed_packet)/sizeof(mixed_packet[0]);
	
	printf("Size of mixed packet: %d\n\n", message_length);
	
 	while(message_length>0)
	{
 		display* message =(display*) mixed_packet[i]; 

		if(message->type == TYPE_DISPLAY)
		{
			display_count++;
		 	display_message();	
		} 
		else if(message->type  == TYPE_MOTOR)
		{
			motor_count++;
		 	update_motor();		 				
		}
		else
		{
			span_count++;
			printf("Wrong message type 0x%x Counld not dispatch!!! \n\n",message->type);
		}
		i++;	
		message_length = message_length-1;
	}
	
	printf("Dispatching summary: %d display messages, %d motor messages, %d span messages\n\n",display_count ,motor_count,span_count);	 
 	printf("Done!\n");
 	return 0;

 }
 
 
